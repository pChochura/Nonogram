#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"

class Actor {
public:
	void act(float deltaTime);

protected:
	float alpha;
	float rotation;
	sf::Vector2f pos;
	sf::Vector2f size;
	std::vector<Animation*> animations;
};