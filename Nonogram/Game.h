#pragma once
#include <vector>
#include "Screen.h"

class Game {
public:
	Game(std::string title, int width = 480, int height = 640);
	void changeScreen(Screen);
	void show() const;

private:
	int width, height;
	std::string title;
	Screen screen;
};