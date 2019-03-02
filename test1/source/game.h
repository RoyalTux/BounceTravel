#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Header.h"
#include "level.h"
#include "tinyxml.h"
#include "entity.h"
#include "player.h"
#include "enemyUnder.h"
#include "coin.h"
#include "boss.h"

int score = 0;
bool flag = false;

inline void menu(RenderWindow & window)
{
		Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground, menuBackground2, menuBackground3;
		aboutTexture.loadFromFile("images/about1.png");
		menuBackground.loadFromFile("images/Bounce.png");
		menuTexture1.loadFromFile("images/1/111.png");
		menuTexture2.loadFromFile("images/1/222.png");
		menuTexture3.loadFromFile("images/1/333.png");
		menuBackground2.loadFromFile("images/1.png");
		Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground), menuBg2(menuBackground2);
		auto isMenu = true;
		int menuNum;
		menu1.setPosition(50, 30);
		menu2.setPosition(50, 90);
		menu3.setPosition(50, 150);
		menuBg2.setPosition(200,20);
		while (isMenu & window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}
			menu1.setColor(Color::Blue);
			menu2.setColor(Color::Blue);
			menu3.setColor(Color::Blue);
			menuNum = 0;
			window.clear(Color(0, 200, 100));
			if (IntRect(50, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Red); menuNum = 1; }
			if (IntRect(50, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Red); menuNum = 2; }
			if (IntRect(50, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Red); menuNum = 3; }
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (menuNum == 1) isMenu = false;
				if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
				if (menuNum == 3) { window.close(); exit(EXIT_SUCCESS); }
			}
			window.draw(menuBg2);
			window.draw(menu1);
			window.draw(menu2);
			window.draw(menu3);
			window.display();
		}
}

inline void changeLevel(Level &lvl, int &numberLevel)
{
		switch (numberLevel)
		{
		case 1:	lvl.LoadFromFile("2.tmx");
			break;
		case 2:  lvl.LoadFromFile("3.tmx");
			break;
		case 3:  lvl.LoadFromFile("4.tmx");
			break;
		case 4:  
		{
			if(flag == false) 
			lvl.LoadFromFile("5.tmx");
			else lvl.LoadFromFile("6.tmx");
		}
			break;
		case 5: lvl.LoadFromFile("6.tmx");
		break;
		}
}

inline bool startGame(RenderWindow &window, int &numberLevel)
{
	view.reset(FloatRect(0, 0, 900, 480));
	auto sound_switch = true;

	Font font;//шрифт 
	Text health_text, score_text, level_text;

	font.loadFromFile("fonts/QueenEmpress.ttf");
	health_text.setFont(font);
	health_text.setString("");
	health_text.setCharacterSize(20);
	health_text.setFillColor(Color::Red);
	score_text.setFont(font);
	score_text.setString("");
	score_text.setCharacterSize(20);
	score_text.setFillColor(Color::Yellow);
	font.loadFromFile("fonts/QueenEmpress.ttf");
	level_text.setFont(font);
	level_text.setString("");
	level_text.setCharacterSize(20);
	level_text.setFillColor(Color::Blue);
	Level lvl;
	changeLevel(lvl, numberLevel); 
	Image heroImage;
	heroImage.loadFromFile("images/balls.png");
	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/EnemySpriteSheet1.png");
	Image easyEnemyImageUp;
	easyEnemyImageUp.loadFromFile("images/enemyy.png");
	Image boss;
	boss.loadFromFile("images/boss.png");
	Image boss2;
	boss2.loadFromFile("images/bosss.png");
	Image enemy1;
	enemy1.loadFromFile("images/enemy1.png");
	Image enemy2;
	enemy2.loadFromFile("images/enemy2.png");
	Image coin;
	coin.loadFromFile("images/coin.png");
	Image gold;
	gold.loadFromFile("images/gold.png");
	Image crystal;
	crystal.loadFromFile("images/crystal.png");
	Image health;
	health.loadFromFile("images/health.png");
	Image enemy3;
	enemy3.loadFromFile("images/enemy3.png");
	Image enemy4;
	enemy4.loadFromFile("images/enemy4.png");
	Image enemy5;
	enemy5.loadFromFile("images/enemy5.png");
	Image enemy6;
	enemy6.loadFromFile("images/enemy6.png");
	Image end;
	end.loadFromFile("images/endMoney.png");
	Image endd;
	endd.loadFromFile("images/endNoMoney.png");
	Image NO;
	NO.loadFromFile("images/stop.png");

	list<Entity*> entities;
	list<Entity*>::iterator it;

	vector<Object> e = lvl.GetObjects("enemy");
	vector<Object> q = lvl.GetObjects("coin");
	vector<Object> gold_a = lvl.GetObjects("gold");
	vector<Object> crystal_c = lvl.GetObjects("crystal");
	vector<Object> eUp = lvl.GetObjects("enemyUp");
	vector<Object> boss1 = lvl.GetObjects("boss");
	vector<Object> boss_2 = lvl.GetObjects("boss2");
	vector<Object> enemy_1 = lvl.GetObjects("enemy1");
	vector<Object> enemy_2 = lvl.GetObjects("enemy2");
	vector<Object> health_mas = lvl.GetObjects("health");
	vector<Object> enemy_3 = lvl.GetObjects("enemy3");
	vector<Object> enemy_4 = lvl.GetObjects("enemy4");
	vector<Object> enemy_5 = lvl.GetObjects("enemy5");
	vector<Object> enemy_6 = lvl.GetObjects("enemy6");
	vector<Object> end_game = lvl.GetObjects("end");
	vector<Object> endd_game = lvl.GetObjects("endd");
	vector<Object> N_O = lvl.GetObjects("NO");

	for (auto i = 0; i < N_O.size(); i++)
		entities.push_back(new Coin(NO, "NO", lvl, N_O[i].rect.left, N_O[i].rect.top, 30, 30));

	for (auto i = 0; i < endd_game.size(); i++)
		entities.push_back(new Coin(endd, "endd", lvl, endd_game[i].rect.left, endd_game[i].rect.top, 910, 562));

	for (auto i = 0; i < end_game.size(); i++)
		entities.push_back(new Coin(end, "end", lvl, end_game[i].rect.left, end_game[i].rect.top, 910, 562));

	for (auto i = 0; i < health_mas.size(); i++)
		entities.push_back(new Coin(health, "health", lvl, health_mas[i].rect.left, health_mas[i].rect.top, 30, 30));

	for (auto i = 0; i < enemy_6.size(); i++)
		entities.push_back(new Enemy(enemy6, "enemy6", lvl, enemy_6[i].rect.left, enemy_6[i].rect.top, 80, 70));

	for (auto i = 0; i < enemy_5.size(); i++)
		entities.push_back(new Enemy(enemy5, "enemy5", lvl, enemy_5[i].rect.left, enemy_5[i].rect.top, 80, 70));

	for (auto i = 0; i < enemy_4.size(); i++)
		entities.push_back(new Enemy(enemy4, "enemy4", lvl, enemy_4[i].rect.left, enemy_4[i].rect.top, 80, 80));

	for (auto i = 0; i < enemy_3.size(); i++)
		entities.push_back(new Enemy(enemy3, "enemy3", lvl, enemy_3[i].rect.left, enemy_3[i].rect.top, 80, 70));

	for (auto i = 0; i < enemy_2.size(); i++)
		entities.push_back(new Enemy(enemy2, "enemy2", lvl, enemy_2[i].rect.left, enemy_2[i].rect.top, 100, 100));

	for (auto i = 0; i < enemy_1.size(); i++)
		entities.push_back(new Enemy(enemy1, "enemy1", lvl, enemy_1[i].rect.left, enemy_1[i].rect.top, 100, 59));

	for (auto i = 0; i < boss_2.size(); i++)
		entities.push_back(new Boss(boss2, "boss2", lvl, boss_2[i].rect.left, boss_2[i].rect.top, 125, 100));

	for (auto i = 0; i < boss1.size(); i++)
		entities.push_back(new Boss(boss, "boss", lvl, boss1[i].rect.left, boss1[i].rect.top, 80, 60));

	for (auto i = 0; i < eUp.size(); i++)
		entities.push_back(new Enemy(easyEnemyImageUp, "enemyUp", lvl, eUp[i].rect.left, eUp[i].rect.top, 32, 32));

	for (auto i = 0; i < q.size(); i++)
		entities.push_back(new Coin(coin, "coin", lvl, q[i].rect.left, q[i].rect.top, 20, 20));

	for (auto i = 0; i < gold_a.size(); i++)
		entities.push_back(new Coin(gold, "gold", lvl, gold_a[i].rect.left, gold_a[i].rect.top, 50, 50));

	for (auto i = 0; i < crystal_c.size(); i++)
		entities.push_back(new Coin(crystal, "crystal", lvl, crystal_c[i].rect.left, crystal_c[i].rect.top, 100, 100));

	for (auto i = 0; i < e.size(); i++)//проходимся по элементам этого вектора(а именно по врагам)
		entities.push_back(new Enemy(easyEnemyImage, "enemy", lvl, e[i].rect.left, e[i].rect.top, 32, 32));//32

	Object player = lvl.GetObject("player");

	Player p(heroImage, "Player1", lvl, player.rect.left, player.rect.top, 32, 32);//объект класса игрока

	Clock clock;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 600;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}	
		p.moveTimer += time;//наращиваем таймер
		if (Keyboard::isKeyPressed(Keyboard::R)) { numberLevel = 0; flag = false; return true; }//если r, то перезагружаем игру
		if (Keyboard::isKeyPressed(Keyboard::LControl)) { numberLevel = 3; return true; }
		if (Keyboard::isKeyPressed(Keyboard::LAlt)) { numberLevel = 4; return true; }
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }//если эскейп, то выходим из игры
		if (Keyboard::isKeyPressed(Keyboard::S)) if (p.moveTimer >1000) { if (sound_switch) { p.music.setVolume(0); sound_switch = false; } else { p.music.setVolume(30); sound_switch = true; } p.moveTimer = 0; }
		p.update(time);	
		if (p.endlevel)
		{
			p.endlevel = false;
			return true;
		}
		for (it = entities.begin(); it != entities.end();)//говорим что проходимся от начала до конца
		{
			Entity *b = *it;//для удобства, чтобы не писать (*it)->
			b->update(time);//вызываем ф-цию update для всех объектов (по сути для тех, кто жив)
			if (b->life == false) { it = entities.erase(it); delete b; p.playerScore++; /*p.score_sound.play();*/ }// если этот объект мертв, то удаляем его
			else ++it;//и идем курсором (итератором) к след объекту. так делаем со всеми объектами списка
		}
		for (it = entities.begin(); it != entities.end(); ++it)
		{
			if ((*it)->name == "NO")
			{
				if (p.playerScore >= 150)
				{
					(*it)->sprite.setColor(Color::Green);
				}
			}
			if ((*it)->getRect().intersects(p.getRect()))
			{
				if ((*it)->name == "enemy")
				{
					if ((p.dy>0) && (p.onGround == false))
					{
						(*it)->dx = 0;
						p.dy = -0.2;
						(*it)->health = 0;
						p.playerScore+=10;
					}
				}
				else if ((*it)->name == "enemy1")
				{
					if ((p.dy>0) && (p.onGround == false))
					{
						p.dy = -0.2;
						(*it)->health -= 50;
						p.playerScore+=40;
						if ((*it)->health == 0) 	(*it)->dx = 0;
					}
				}
				if ((*it)->name == "enemy2")
				{
					if ((p.dy>0) && (p.onGround == false))
					{
						p.dy = -0.2;
						(*it)->health -= 50;
						p.playerScore+=40;
						if ((*it)->health == 0) 	(*it)->dx = 0;
					}
				}
				if ((*it)->name == "enemy3")
				{
					if ((p.dx>0) && (p.onGround == false))
					{
						(*it)->dy = 0;
						p.dy = -0.2;
						(*it)->health = 0;
						p.playerScore += 40;
					}
				}
				if ((*it)->name == "enemy4")
				{
					{
						(*it)->health = 0;
							p.health += 50;
					}
				}
				if ((*it)->name == "enemy5")
				{
					if ((p.dx>0) && (p.onGround == false))
					{
						(*it)->dy = 0;
						p.dy = -0.2;
						(*it)->health = 0;
						p.playerScore+=10;
					}
				}
				if ((*it)->name == "enemy6")
				{
					if ((p.dx>0) && (p.onGround == false))
					{
						(*it)->dy = 0;
						p.dy = -0.2;
						(*it)->health = 0;
						p.playerScore+=10;
					}
				}
				if ((*it)->name == "enemyUp")
				{
					if ((p.dy>0) && (p.onGround == false))
					{
						(*it)->dx = 0;
						p.dy = -0.2;
						(*it)->health = 0;
						p.playerScore+=10;
					}
				}
				if ((*it)->name == "boss")
				{
					if ((p.dy>0) && (p.onGround == false))
					{
						p.dy = -0.2;
						(*it)->health -= 20;
						p.playerScore+=50;
						if((*it)->health == 0) 	(*it)->dx = 0;
					}
				}
				if ((*it)->name == "boss2")
				{
					if ((p.dy>0) && (p.onGround == false))
					{
						p.dy = -0.2;
						(*it)->health -= 20;
						p.playerScore+=70;
						if ((*it)->health == 0) 	(*it)->dx = 0;
					}
				}
				if ((*it)->name == "coin")
				{
					(*it)->health = 0;
						p.playerScore+=4;
				}
				if ((*it)->name == "gold")
				{
					(*it)->health = 0;
						p.playerScore+=49;
				}
				if ((*it)->name == "crystal")
				{
					(*it)->health = 0;
					p.playerScore += 29;
					flag = true;
				}
				if ((*it)->name == "health")
				{
					(*it)->health = 0;
						p.health+=10;
				}
			}
		}
		p.moveTimer += time;//наращиваем таймер
		for (it = entities.begin(); it != entities.end(); ++it)//проходимся по эл-там списка
		{
			if ((*it)->getRect().intersects(p.getRect()))//если прямоугольник спрайта объекта пересекается с игроком
			{
				if (p.moveTimer > 1200)
				{
					if ((*it)->name == "enemy")
					{
						if ((*it)->dx > 0)
						{
							p.health -= 2;
							p.dy = -0.2;
							p.moveTimer = 0;							
						}
						if ((*it)->dx < 0)
						{
							p.health -= 2;
							p.dy = -0.2;
							p.moveTimer = 0;
						}
					}
					if ((*it)->name == "enemy1")
					{
						if ((*it)->dx > 0)
						{
							p.health -= 5;
							p.dy = -0.2;
							p.moveTimer = 0;
						}
						if ((*it)->dx < 0)
						{
							p.health -= 5;
							p.dy = -0.2;
							p.moveTimer = 0;
						}
					}
					if ((*it)->name == "enemy2")
					{
						if ((*it)->dx > 0)
						{
							p.health -= 5;
							p.dy = -0.2;
							p.moveTimer = 0;
						}
						if ((*it)->dx < 0)
						{
							p.health -= 5;
							p.dy = -0.2;
							p.moveTimer = 0;
						}
					}
					if ((*it)->name == "enemy3")
					{
						if ((*it)->dy > 0)
						{
							p.health -= 5;
							p.dx = -0.2;
							p.moveTimer = 0;
						}
						if ((*it)->dy < 0)
						{
							p.health -= 5;
							p.dx = -0.2;
							p.moveTimer = 0;
						}
					}
					if ((*it)->name == "enemy5")
					{
						if ((*it)->dy > 0)
						{
							p.health -= 2;
							p.dx = -0.2;
							p.moveTimer = 0;
						}
						if ((*it)->dy < 0)
						{
							p.health -= 2;
							p.dx = -0.2;
							p.moveTimer = 0;
						}
					}
					if ((*it)->name == "enemy6")
					{
						if ((*it)->dy > 0)
						{
							p.health -= 2;
							p.dx = -0.2;
							p.moveTimer = 0;
						}
						if ((*it)->dy < 0)
						{
							p.health -= 2;
							p.dx = -0.2;
							p.moveTimer = 0;
						}
					}
					if ((*it)->name == "enemyUp")
					{
						if ((*it)->dx > 0)
						{
							p.health -= 2;
							p.dy = -0.2;
							p.moveTimer = 0;
						}
						if ((*it)->dx < 0)
						{
							p.health -= 2;
							p.dy = -0.2;
							p.moveTimer = 0;
						}
					}
					if ((*it)->name == "boss")
					{
						if ((*it)->dx > 0)
						{
							p.health -= 10;
							p.dy = -0.4;
							p.moveTimer = 0;
						}
						if ((*it)->dx < 0)
						{
							p.health -= 10;
							p.dy = -0.4;
							p.moveTimer = 0;
						}
					}
					if ((*it)->name == "boss2")
					{
						if ((*it)->dx > 0)
						{
							p.health -= 10;
							p.dy = -0.4;
							p.moveTimer = 0;
						}
						if ((*it)->dx < 0)
						{
							p.health -= 10;
							p.dy = -0.4;
							p.moveTimer = 0;
						}
					}
				}
			}
		}
		score = p.playerScore;
		window.setView(view);
		window.clear(Color(255, 255, 255));
		lvl.Draw(window);
		for (it = entities.begin(); it != entities.end(); ++it)
		{
			window.draw((*it)->sprite); 
		}
		window.draw(p.sprite);
		if (numberLevel < 4)
		{
			ostringstream healthString; 
			healthString << p.health;
			health_text.setString("Health :" + healthString.str());
			health_text.setPosition(view.getCenter().x - 440, view.getCenter().y - 230);
			window.draw(health_text);
			ostringstream playerScoreString; 
			playerScoreString << p.playerScore;
			score_text.setString("Score :" + playerScoreString.str());
			score_text.setPosition(view.getCenter().x - 440, view.getCenter().y - 190);
			window.draw(score_text);
			ostringstream levelString; 
			levelString << numberLevel;
			level_text.setString("Level :" + levelString.str());
			level_text.setPosition(view.getCenter().x + 350, view.getCenter().y - 230);
			window.draw(level_text);
		}
		window.draw(p.text_gameover);
		window.display();
	}
	return false;
}

inline void gameRunning(RenderWindow & window, int & numberLevel)
{
	if (startGame(window, numberLevel))
	{
		numberLevel++;
		gameRunning(window, numberLevel);
	}
}

