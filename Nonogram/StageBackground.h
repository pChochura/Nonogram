#pragma once
#include "Stage.h"

class StageBackground : public Stage {
public:
	StageBackground();
	void draw(sf::RenderWindow* window) const;
private:
	sf::Sprite spriteBackground;
	sf::Texture textureBackground;
};