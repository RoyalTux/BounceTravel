#pragma once
#include <SFML/Graphics.hpp>
#include "Header.h"

View view;

inline void setPlayerCoordinateForView(float x, float y) 
{ 
	auto tempX = x;
	auto tempY = y;
	if (x < 450) tempX = 450;//����� �������
	if (x > 3390) tempX = 3390;//������ �������
	if (y > 600) tempY = 600;//������ �������
	if (y < 600) tempY = 600;//������� �������
	view.setCenter(tempX, tempY);
}