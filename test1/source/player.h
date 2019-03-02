#pragma once
#include "entity.h"
#include "SFML/Audio.hpp"
#include "view.h"
// класс игрока

class Player :public Entity
{
public:
	enum { left, right, up, down, jump, stay } state;//добавл€ем тип перечислени€ - состо€ние объекта
	int playerScore;//эта переменна€ может быть только у игрока
	bool endlevel;
	Font font;//шрифт 
	Text text_gameover;
	SoundBuffer bounceBuffer, looseBuffer, scoreBuffer;//создаЄм буфер дл€ звука
	float CurrentFrame;
	Music music;
	Sound bounce_sound, loose_sound, score_sound;//создаем звук и загружаем в него звук из буфера
	Player(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H)
	{
		endlevel = false;
		music.openFromFile("music/fon.wav");
		music.setVolume(30);
		//music.play();
		//music.setLoop(true);
		font.loadFromFile("fonts/QueenEmpress.ttf");
		text_gameover.setFont(font);
		text_gameover.setString("Game Over");
		text_gameover.setCharacterSize(80);
		// ReSharper disable CppDeprecatedEntity
		text_gameover.setFillColor(Color::Red);
		// ReSharper restore CppDeprecatedEntity
		playerScore = 0;
		//score = playerScore;
		state = stay;
		obj = lvl.GetAllObjects();
		CurrentFrame = 0;
		firstdie = true;
		health = 100;
		bounceBuffer.loadFromFile("music/bounce_sound.wav");//загружаем в него звук
		looseBuffer.loadFromFile("music/loose.wav");
		scoreBuffer.loadFromFile("music/score_sound.wav");
		score_sound.setBuffer(scoreBuffer);
		loose_sound.setBuffer(looseBuffer);
		//score_sound.setVolume(100);
		//loose_sound.setVolume(100);
		bounce_sound.setBuffer(bounceBuffer);//создаем звук и загружаем в него звук из буфера
		if (name == "Player1")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
	}
	void control(float time)
	{
		if (life)
		{
			if (Keyboard::isKeyPressed)
			{
				//если нажата клавиша
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					//а именно лева€
					state = left; speed = 0.1;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 8) CurrentFrame -= 8;
					sprite.setTextureRect(IntRect(224 - 32 * int(CurrentFrame), 0, 32, 32));
				}
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					state = right; speed = 0.1;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 8) CurrentFrame -= 8;
					sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 0, 32, 32));
				}
				if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::RShift))
				{
					state = left; speed = 0.3;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 8) CurrentFrame -= 8;
					sprite.setTextureRect(IntRect(224 - 32 * int(CurrentFrame), 0, 32, 32));
				}
				if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::RShift))
				{
					state = right; speed = 0.3;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 8) CurrentFrame -= 8;
					sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 0, 32, 32));
				}
				if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround))
				{
					//если нажата клавиша вверх и мы на земле, то можем прыгать
					state = jump; dy = -0.36; onGround = false;//увеличил высоту прыжка
					//bounce_sound.play();
				}
				if (Keyboard::isKeyPressed(Keyboard::Down))
				{
					state = down;
				}
			}
		}
	}
	void checkCollisionWithMap(float Dx, float Dy)//ф ци€ проверки столкновений с картой
	{
		for (auto i = 0; i<obj.size(); i++)//проходимс€ по объектам
			if (getRect().intersects(obj[i].rect))//провер€ем пересечение игрока с объектом
			{
				if (obj[i].name == "endlevel")
				{
					if(playerScore >= 400)
						endlevel = true;
				}
				if (obj[i].name == "solid")//если встретили преп€тствие
				{
					if (Dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
					if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
					if (Dx>0) { x = obj[i].rect.left - w; }
					if (Dx<0) { x = obj[i].rect.left + obj[i].rect.width; }
				}
				if (obj[i].name == "stop")//если встретили преп€тствие
				{
					if (playerScore <= 150)
					{
						if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; onGround = true;}
						if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
						if (Dx > 0) { x = obj[i].rect.left - w; }
						if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
					}
				}
				if (obj[i].name == "SlopeLeft")
				{
					FloatRect r = obj[i].rect;
					int y0 = (x + w / 2 - r.left) * r.height / r.width + r.top - h;
					if (y>y0)
						if (x + w / 2>r.left)
						{
							onGround = true;
							y = y0; dy = 0;
						}
				}
				if (obj[i].name == "SlopeRight")
				{
					FloatRect r = obj[i].rect;
					int y0 = -(x + w / 2 - r.left) * r.height / r.width + r.top + r.height - h;
					if (y > y0)
						if (x + w / 2<r.left + r.width)
						{
							onGround = true;
							y = y0; dy = 0;
						}
				}
			}
	}
	void update(float time)
	{
		control(time);//функци€ управлени€ персонажем
		switch (state)//тут делаютс€ различные действи€ в зависимости от состо€ни€
		{
		case right:
		{
			dx = speed;
			break;
		}
		case left:
		{
			dx = -speed;
			break;
		}
		//состо€ние идти влево
		case up: break;//будет состо€ние подн€ти€ наверх (например по лестнице)
		case down: dx = 0; break;//будет состо€ние во врем€ спуска персонажа (например по лестнице)
		case stay: break;//и здесь тоже		
		}
		x += dx*time;
		checkCollisionWithMap(dx, 0);//обрабатываем столкновение по ’
		y += dy*time;
		checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
		if (health <= 0)
		{
			health = 0;
			life = false;
			if (firstdie)
			{
				music.setVolume(0);
				firstdie = false;
				//loose_sound.play();
				text_gameover.setString("Game Over");
				text_gameover.setPosition(view.getCenter().x - 200, view.getCenter().y - 100);//задаем позицию текста, центр камеры
			}
		}
		if (!isMove) { speed = 0; }
		if (life) { setPlayerCoordinateForView(x, y); }
		dy = dy + 0.0005*time;//посто€нно прит€гиваемс€ к земле
	}

};

