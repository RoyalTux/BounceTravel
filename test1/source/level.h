﻿#pragma once
#include "Header.h"
#include <SFML/Graphics.hpp>
#include "tinyxml.h"

struct Object
{
	int GetPropertyInt(string name);//номер свойства объекта в нашем списке
	float GetPropertyFloat(string name);
	string GetPropertyString(string name);
	string name;//объявили переменную name типа string
	string type;//а здесь переменную type типа string
	Rect<float> rect;//тип Rect с нецелыми значениями
	map<string, string> properties;//создаём ассоциатиный массив. ключ - строковый тип, значение - строковый
	Sprite sprite;//объявили спрайт
};

struct Layer//слои
{
	int opacity;//непрозрачность слоя
	vector<Sprite> tiles;//закидываем в вектор тайлы
};

class Level//главный класс - уровень
{
public:
	bool LoadFromFile(string filename);//возвращает false если не получилось загрузить
	Object GetObject(string name);
	vector<Object> GetObjects(string name);//выдаем объект в наш уровень
	vector<Object> GetAllObjects() const;//выдаем все объекты в наш уровень
	void Draw(RenderWindow &window);//рисуем в окно
	Vector2i GetTileSize() const;//получаем размер тайла
private:
	int width, height, tileWidth, tileHeight;//в tmx файле width height в начале,затем размер тайла
	int firstTileID;//получаем айди первого тайла
	Rect<float> drawingBounds;//размер части карты которую рисуем
	Texture tilesetImage;//текстура карты
	vector<Object> objects;//массив типа Объекты, который мы создали
	vector<Layer> layers; // слои
};

inline int Object::GetPropertyInt(string name)//возвращаем номер свойства в нашем списке
{
	return atoi(properties[name].c_str());
}

inline float Object::GetPropertyFloat(string name)
{
	return strtod(properties[name].c_str(), nullptr);
}

inline string Object::GetPropertyString(string name)//получить имя в виде строки.вроде понятно
{
	return properties[name];
}

inline bool Level::LoadFromFile(string filename)//двоеточия-обращение к методам класса вне класса 
{
	TiXmlDocument levelFile(filename.c_str());//загружаем файл в TiXmlDocument
	// загружаем XML-карту
	if (!levelFile.LoadFile())//если не удалось загрузить карту
	{
		cout << "Loading level \"" << filename << "\" failed." << endl;//выдаем ошибку
		return false;
	}
	// работаем с контейнером map
	TiXmlElement *map;
	map = levelFile.FirstChildElement("map");
	// пример карты: <map version="1.0" orientation="orthogonal"
	// width="10" height="10" tilewidth="34" tileheight="34">
	width = atoi(map->Attribute("width"));//извлекаем из нашей карты ее свойства
	height = atoi(map->Attribute("height"));//те свойства, которые задавали при работе в 
	tileWidth = atoi(map->Attribute("tilewidth"));//тайлмап редакторе
	tileHeight = atoi(map->Attribute("tileheight"));
	// Берем описание тайлсета и идентификатор первого тайла
	TiXmlElement *tilesetElement;
	tilesetElement = map->FirstChildElement("tileset");
	firstTileID = atoi(tilesetElement->Attribute("firstgid"));
	// source - путь до картинки в контейнере image
	TiXmlElement *image;
	image = tilesetElement->FirstChildElement("image");
	string imagepath = image->Attribute("source");
	// пытаемся загрузить тайлсет
	Image img;
	if (!img.loadFromFile(imagepath))
	{
		cout << "Failed to load tile sheet." << endl;//если не удалось загрузить тайлсет-выводим ошибку в консоль
		return false;
	}
	img.createMaskFromColor(Color(255, 255, 255));//для маски цвета.сейчас нет маски
	tilesetImage.loadFromImage(img);
	tilesetImage.setSmooth(false);//сглаживание
	// получаем количество столбцов и строк тайлсета
	int columns = tilesetImage.getSize().x / tileWidth;
	int rows = tilesetImage.getSize().y / tileHeight;
	// вектор из прямоугольников изображений (TextureRect)
	vector<Rect<int>> subRects;
	for (int y = 0; y < rows; y++)
	for (int x = 0; x < columns; x++)
	{
		Rect<int> rect;
		rect.top = y * tileHeight;
		rect.height = tileHeight;
		rect.left = x * tileWidth;
		rect.width = tileWidth;
		subRects.push_back(rect);
	}
	// работа со слоями
	TiXmlElement *layerElement;
	layerElement = map->FirstChildElement("layer");
	while (layerElement)
	{
		Layer layer;
		// если присутствует opacity, то задаем прозрачность слоя, иначе он полностью непрозрачен
		if (layerElement->Attribute("opacity") != NULL)
		{
			float opacity = strtod(layerElement->Attribute("opacity"), NULL);
			layer.opacity = 255 * opacity;
		}
		else
		{
			layer.opacity = 255;
		}
		//  контейнер <data> 
		TiXmlElement *layerDataElement;
		layerDataElement = layerElement->FirstChildElement("data");
		if (layerDataElement == NULL)
		{
			cout << "Bad map. No layer information found." << endl;
		}
		//  контейнер <tile> - описание тайлов каждого слоя
		TiXmlElement *tileElement;
		tileElement = layerDataElement->FirstChildElement("tile");
		if (tileElement == NULL)
		{
			cout << "Bad map. No tile information found." << endl;
			return false;
		}
		int x = 0;
		int y = 0;
		while (tileElement)
		{
			int tileGID = atoi(tileElement->Attribute("gid"));
			int subRectToUse = tileGID - firstTileID;
			// Устанавливаем TextureRect каждого тайла
			if (subRectToUse >= 0)
			{
				Sprite sprite;
				sprite.setTexture(tilesetImage);
				sprite.setTextureRect(subRects[subRectToUse]);
				sprite.setPosition(x * tileWidth, y * tileHeight);
				sprite.setColor(Color(255, 255, 255, layer.opacity));
				layer.tiles.push_back(sprite);//закидываем в слой спрайты тайлов
			}
			tileElement = tileElement->NextSiblingElement("tile");
			x++;
			if (x >= width)
			{
				x = 0;
				y++;
				if (y >= height)
					y = 0;
			}
		}
		layers.push_back(layer);
		layerElement = layerElement->NextSiblingElement("layer");
	}
	// работа с объектами
	TiXmlElement *objectGroupElement;
	// если есть слои объектов
	if (map->FirstChildElement("objectgroup") != NULL)
	{
		objectGroupElement = map->FirstChildElement("objectgroup");
		while (objectGroupElement)
		{
			//  контейнер <object>
			TiXmlElement *objectElement;
			objectElement = objectGroupElement->FirstChildElement("object");
			while (objectElement)
			{
				// получаем все данные - тип, имя, позиция, и тд
				string objectType;
				if (objectElement->Attribute("type") != NULL)
				{
					objectType = objectElement->Attribute("type");
				}
				string objectName;
				if (objectElement->Attribute("name") != NULL)
				{
					objectName = objectElement->Attribute("name");
				}
				int x = atoi(objectElement->Attribute("x"));
				int y = atoi(objectElement->Attribute("y"));
				int width, height;
				Sprite sprite;
				sprite.setTexture(tilesetImage);
				sprite.setTextureRect(Rect<int>(0, 0, 0, 0));
				sprite.setPosition(x, y);
				if (objectElement->Attribute("width") != NULL)
				{
					width = atoi(objectElement->Attribute("width"));
					height = atoi(objectElement->Attribute("height"));
				}
				else
				{
					width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
					height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
					sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
				}
				// экземпляр объекта
				Object object;
				object.name = objectName;
				object.type = objectType;
				object.sprite = sprite;
				Rect <float> objectRect;
				objectRect.top = y;
				objectRect.left = x;
				objectRect.height = height;
				objectRect.width = width;
				object.rect = objectRect;
				// "переменные" объекта
				TiXmlElement *properties;
				properties = objectElement->FirstChildElement("properties");
				if (properties != NULL)
				{
					TiXmlElement *prop;
					prop = properties->FirstChildElement("property");
					if (prop != NULL)
					{
						while (prop)
						{
							string propertyName = prop->Attribute("name");
							string propertyValue = prop->Attribute("value");
							object.properties[propertyName] = propertyValue;
							prop = prop->NextSiblingElement("property");
						}
					}
				}
				objects.push_back(object);
				objectElement = objectElement->NextSiblingElement("object");
			}
			objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
		}
	}
	else
	{
		cout << "No object layers found..." << std::endl;
	}
	return true;
}

inline Object Level::GetObject(string name)
{
	// только первый объект с заданным именем
	for (int i = 0; i < objects.size(); i++)
	if (objects[i].name == name)
		return objects[i];
	return {};
}

inline vector<Object> Level::GetObjects(string name)
{
	// все объекты с заданным именем
	vector<Object> vec;
	for (int i = 0; i < objects.size(); i++)
	if (objects[i].name == name)
		vec.push_back(objects[i]);
	return vec;
}


inline vector<Object> Level::GetAllObjects() const
{
	return objects;
};


inline Vector2i Level::GetTileSize() const
{
	return Vector2i(tileWidth, tileHeight);
}

inline void Level::Draw(RenderWindow &window)
{
	// рисуем все тайлы (объекты не рисуем!)
	for (int layer = 0; layer < layers.size(); layer++)
	for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
		window.draw(layers[layer].tiles[tile]);
}

