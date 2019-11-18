#include <SFML/Graphics.hpp>
#include "../Stages/StageBackground.h"
#include "../../Utils/ResourceIdentifier.h"

void StageBackground::init(Context* context) {
	context->textures.load(Textures::Background, "data/Textures/background.png");

	this->view = context->window->getDefaultView();

	float max = (float) std::max(context->window->getSize().x, context->window->getSize().y);
	float ratio = 16.0f / 9.0f;
	this->size = { max * ratio, max };
}

void StageBackground::draw(Context* context) {
	context->window->setView(this->view);

	sf::Sprite sprite;
	sprite.setTexture(context->textures.get(Textures::Background));
	sprite.setScale(this->size.x / sprite.getLocalBounds().width, this->size.y / sprite.getLocalBounds().height);
	context->window->draw(sprite);
}

bool StageBackground::onEvent(Context* context, sf::Event event) {
	context->window->setView(this->view);

	return false;
}