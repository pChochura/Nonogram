#pragma once
#include "Screens/Screen.h"

class Game {
public:
	Game(Screen* firstScreen, std::string title, int width = 1080, int height = 720);
	void changeScreen(Screen*);
	void show();

private:
	int width, height;
	Screen* screen;
	Context* context;
};