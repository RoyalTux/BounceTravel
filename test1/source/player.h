#pragma once
#include "entity.h"
#include "SFML/Audio.hpp"
#include "view.h"
// ����� ������

class Player :public Entity
{
public:
	enum { left, right, up, down, jump, stay } state;//��������� ��� ������������ - ��������� �������
	int playerScore;//��� ���������� ����� ���� ������ � ������
	bool endlevel;
	Font font;//����� 
	Text text_gameover;
	SoundBuffer bounceBuffer, looseBuffer, scoreBuffer;//������ ����� ��� �����
	float CurrentFrame;
	Music music;
	Sound bounce_sound, loose_sound, score_sound;//������� ���� � ��������� � ���� ���� �� ������
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
		bounceBuffer.loadFromFile("music/bounce_sound.wav");//��������� � ���� ����
		looseBuffer.loadFromFile("music/loose.wav");
		scoreBuffer.loadFromFile("music/score_sound.wav");
		score_sound.setBuffer(scoreBuffer);
		loose_sound.setBuffer(looseBuffer);
		//score_sound.setVolume(100);
		//loose_sound.setVolume(100);
		bounce_sound.setBuffer(bounceBuffer);//������� ���� � ��������� � ���� ���� �� ������
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
				//���� ������ �������
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					//� ������ �����
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
					//���� ������ ������� ����� � �� �� �����, �� ����� �������
					state = jump; dy = -0.36; onGround = false;//�������� ������ ������
					//bounce_sound.play();
				}
				if (Keyboard::isKeyPressed(Keyboard::Down))
				{
					state = down;
				}
			}
		}
	}
	void checkCollisionWithMap(float Dx, float Dy)//� ��� �������� ������������ � ������
	{
		for (auto i = 0; i<obj.size(); i++)//���������� �� ��������
			if (getRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
			{
				if (obj[i].name == "endlevel")
				{
					if(playerScore >= 400)
						endlevel = true;
				}
				if (obj[i].name == "solid")//���� ��������� �����������
				{
					if (Dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
					if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
					if (Dx>0) { x = obj[i].rect.left - w; }
					if (Dx<0) { x = obj[i].rect.left + obj[i].rect.width; }
				}
				if (obj[i].name == "stop")//���� ��������� �����������
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
		control(time);//������� ���������� ����������
		switch (state)//��� �������� ��������� �������� � ����������� �� ���������
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
		//��������� ���� �����
		case up: break;//����� ��������� �������� ������ (�������� �� ��������)
		case down: dx = 0; break;//����� ��������� �� ����� ������ ��������� (�������� �� ��������)
		case stay: break;//� ����� ����		
		}
		x += dx*time;
		checkCollisionWithMap(dx, 0);//������������ ������������ �� �
		y += dy*time;
		checkCollisionWithMap(0, dy);//������������ ������������ �� Y
		sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
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
				text_gameover.setPosition(view.getCenter().x - 200, view.getCenter().y - 100);//������ ������� ������, ����� ������
			}
		}
		if (!isMove) { speed = 0; }
		if (life) { setPlayerCoordinateForView(x, y); }
		dy = dy + 0.0005*time;//��������� ������������� � �����
	}

};

