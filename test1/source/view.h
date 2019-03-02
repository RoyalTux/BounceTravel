#pragma once
#include <SFML/Graphics.hpp>
#include "Header.h"

View view;

inline void setPlayerCoordinateForView(float x, float y) 
{ 
	auto tempX = x;
	auto tempY = y;
	if (x < 450) tempX = 450;//левая сторона
	if (x > 3390) tempX = 3390;//правая сторона
	if (y > 600) tempY = 600;//нижнюю стороню
	if (y < 600) tempY = 600;//верхнюю стороню
	view.setCenter(tempX, tempY);
}