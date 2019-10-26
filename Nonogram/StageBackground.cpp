#include "StageBackground.h"
#include <iostream>

StageBackground::StageBackground() {
	this->textureBackground.loadFromFile("image.jpg");
	this->spriteBackground.setTexture(this->textureBackground);
	this->spriteBackground.setPosition(0, 0);
}

void StageBackground::draw(sf::RenderWindow* window) {
	sf::Texture texture;
	texture.loadFromFile("image.jpg");
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(0, 0);
	window->draw(sprite);
	std::cout << "shoulda drawn";
}