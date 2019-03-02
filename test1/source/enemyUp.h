#pragma once
#include "entity.h"
// класс врага 2
class EnemyUp :public Entity
{
public:
	EnemyUp(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H)
	{
		obj = lvl.GetAllObjects();
		if (name == "enemyUp")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dx = 0.09;
		}
	}
	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = 0; i<obj.size(); i++)
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
		if (name == "enemyUp")
		{
			moveTimer += time; if (moveTimer>1000) { dx *= 1; moveTimer = 0; }
			x += dx*time;
			checkCollisionWithMap(dx, 0);
			sprite.setPosition(x + w, y + h);
			if (health <= 0) { life = false; }
		}
	}
};