#include "Actor.h"

void Actor::act(float deltaTime) {
	for (auto& anim : this->animations) {
		//anim->act(this, deltaTime);
	}
}

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
