#pragma once

#include <vector>
#include "Stage.h"

class Screen {
public:
	void show(sf::RenderWindow* window) const {
		for (auto& stage : this->stages) {
			stage->draw(window);
		}
	}

protected:
	std::vector<Stage*> stages;
};