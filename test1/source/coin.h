#pragma once
#include "entity.h"
// класс монетки
class Coin : public Entity
{
public:
	virtual ~Coin() = default;
	Coin(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H)
	{
		obj = lvl.GetAllObjects();
		if (name == "coin")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
		if (name == "gold")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
		if (name == "crystal")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
		if (name == "health")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
		if (name == "end")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
		if (name == "endd")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
		if (name == "NO")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
	}
	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (auto i = 0; i<obj.size(); i++)
		{
			if (getRect().intersects(obj[i].rect))
			{
				if (obj[i].name == "solid")
				{
					if (Dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
					if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
					if (Dx>0) { x = obj[i].rect.left - w;  dx = -0.1; sprite.scale(-1, 1); }
					if (Dx<0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1, 1); }
				}
			}
		}
	}
	void update(float time)
	{
		if (name == "coin")
		{
			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
		}
		if (name == "gold")
		{
			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
		}
		if (name == "crystal")
		{
			sprite.setPosition(x + w / 2, y + h / 2); 
			if (health <= 0) { life = false; }
		}
		if (name == "health")
		{
			sprite.setPosition(x + w / 2, y + h / 2); 
			if (health <= 0) { life = false; }
		}
		if (name == "end")
		{
			sprite.setPosition(x + w / 2, y + h / 2); 
		}
		if (name == "endd")
		{
			sprite.setPosition(x + w / 2, y + h / 2); 
		}
		if (name == "NO")
		{
			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
		}
	}
};
