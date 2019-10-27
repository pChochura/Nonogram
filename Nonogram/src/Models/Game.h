#pragma once
#include "Screens/Screen.h"

class Game {
public:
	Game(Screen& firstScreen, std::string title, int width = 480, int height = 640);
	void changeScreen(Screen&);
	void show();

private:
	int width, height;
	std::string title;
	Screen& screen;
	Context* context;
};