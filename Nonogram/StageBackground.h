#pragma once
#include "Stage.h"

class StageBackground : public Stage {
public:
	StageBackground();
	virtual void draw(sf::RenderWindow* window) override;
private:
	sf::Sprite spriteBackground;
	sf::Texture textureBackground;
};