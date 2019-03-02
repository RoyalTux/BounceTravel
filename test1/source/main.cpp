#include "game.h"

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	RenderWindow window(VideoMode(900, 480), "Bounce Travel");
	window.setVerticalSyncEnabled(true);
	menu(window);
	auto numberLevel = 1;
	gameRunning(window, numberLevel);
	return 0;
}