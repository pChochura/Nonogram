#pragma once
#include "SFML/Graphics.hpp"

class Stage {
public:
	virtual void draw(sf::RenderWindow*) = 0;
};