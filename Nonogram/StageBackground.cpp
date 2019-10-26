#include "StageBackground.h"

StageBackground::StageBackground() {
	textureBackground.loadFromFile("image_background.jpg");
	spriteBackground.setTexture(textureBackground);
}

void StageBackground::draw(sf::RenderWindow* window) const {
	window->draw(spriteBackground);
}