#include <SFML/Graphics.hpp>
#include "../Stages/StageBackground.h"
#include "../../Utils/ResourceIdentifier.h"

void StageBackground::init(Context* context) {
	context->textures.load(Textures::Background, "data/Textures/background.png");

	this->view = context->window->getDefaultView();
}

void StageBackground::draw(Context* context) {
	context->window->setView(this->view);

	sf::Sprite sprite;
	sprite.setTexture(context->textures.get(Textures::Background));
	context->window->draw(sprite);
}

bool StageBackground::onEvent(Context* context, sf::Event event) {
	context->window->setView(this->view);

	return false;
}