#include <SFML/Graphics.hpp>
#include "../Stages/StageBackground.h"
#include "../../Utils/ResourceIdentifier.h"

void StageBackground::init(Context* context) {
	context->textures.load(Textures::Background, "data/Textures/image_background.jpg");
}

void StageBackground::draw(Context* context) {
	sf::Sprite sprite;
	sprite.setTexture(context->textures.get(Textures::Background));
	context->window->draw(sprite);
}

bool StageBackground::onEvent(Context* context, sf::Event event) {
	return false;
}