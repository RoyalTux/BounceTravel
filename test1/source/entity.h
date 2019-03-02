#pragma once
#include "level.h"
#include "Header.h"
//Общий класс родитель
class Entity
{
public:
	virtual ~Entity() = default;
	vector<Object> obj;
	float dx, dy, x, y, speed, moveTimer;
	int w, h, health;
	bool life, isMove, onGround, firstdie;
	Texture texture;
	Sprite sprite;
	String name;
	Entity(Image &image, String Name, float X, float Y, int W, int H): firstdie(false)
	{
		x = X;
		y = Y;
		w = W;
		h = H;
		name = Name;
		moveTimer = 0;
		speed = 0;
		health = 100;
		dx = 0;
		dy = 0;
		life = true;
		onGround = false;
		isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}

	FloatRect getRect() const
	{
		return FloatRect(x, y, w, h);
	}
	virtual void update(float time) = 0;
};