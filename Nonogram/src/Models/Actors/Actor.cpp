#include "Actor.h"

sf::Vector2f Actor::getPos() {
	return this->pos;
}

sf::Vector2f Actor::getSize() {
	return this->size;
}

float Actor::getAlpha() {
	return this->alpha;
}

float Actor::getRotation() {
	return this->rotation;
}

bool Actor::isVisible() {
	return this->visible;
}

void Actor::setVsibility(bool visibility) {
	this->visible = visibility;
}
