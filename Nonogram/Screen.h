#pragma once

#include <vector>
#include <string>
#include "Stage.h"

class Screen {
public:
	Screen(std::vector<Stage*> stages, std::string title, int width = 480, int height = 640);
	void show() const;

private:
	int width, height;
	std::string title;
	std::vector<Stage*> stages;
};