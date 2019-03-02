#pragma once
#include "entity.h"
// класс врага 1
class Enemy :public Entity
{
public:
	virtual ~Enemy() = default;

	Enemy(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H)
	{
		obj = lvl.GetAllObjects();
		if (name == "enemy")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dx = 0.1;
		}
		if (name == "enemy1")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dx = 0.1;
		}
		if (name == "enemy2")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dx = 0.1;
		}
		if (name == "enemy3")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dy = 0.1;
		}
		if (name == "enemy4")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dy = 0.1;
		}
		if (name == "enemy5")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dy = 0.1;
		}
		if (name == "enemy6")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dy = 0.1;
		}
		if (name == "enemyUp")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dx = 0.09;
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
		if (name == "enemy")
		{
			moveTimer += time; if (moveTimer>2000) { dx *= -1; moveTimer = 0; }
			x += dx*time;
			checkCollisionWithMap(dx, 0);
			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
		}
		if (name == "enemy1")
		{
			moveTimer += time; if (moveTimer>2000) { dx *= -1; moveTimer = 0; }
			x += dx*time;
			checkCollisionWithMap(dx, 0);
			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
		}
		if (name == "enemy2")
		{
			moveTimer += time; if (moveTimer>2000) { dx *= -1; moveTimer = 0; }
			x += dx*time;
			checkCollisionWithMap(dx, 0);
			sprite.setPosition(x + w / 2, y + h / 2); 
			if (health <= 0) { life = false; }
		}
		if (name == "enemy3")
		{
			moveTimer += time; if (moveTimer>2000) { dy *= -1; moveTimer = 0; }
			y += dy*time;
			checkCollisionWithMap(dx, 0);
			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
		}
		if (name == "enemy4")
		{
			moveTimer += time; if (moveTimer>2000) { dx *= -1; moveTimer = 0; }
			x += dx*time;
			checkCollisionWithMap(dx, 0);
			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
		}
		if (name == "enemy5")
		{
			moveTimer += time; if (moveTimer>1000) { dy *= -1; moveTimer = 0; }
			y += dy*time;
			checkCollisionWithMap(dx, 0);
			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
		}
		if (name == "enemy6")
		{
			moveTimer += time; if (moveTimer>1000) { dy *= -1; moveTimer = 0; }
			y += dy*time;
			checkCollisionWithMap(dx, 0);
			sprite.setPosition(x + w / 2, y + h / 2); 
			if (health <= 0) { life = false; }
		}
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