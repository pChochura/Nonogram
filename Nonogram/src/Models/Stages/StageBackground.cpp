#include "../Stages/StageBackground.h"
#include "../../Utils/ResourceIdentifier.h"

void StageBackground::load(Context* context) {
	context->textures.load(Textures::Background, "data/images/image_background.jpg");
}

void StageBackground::draw(Context* context) {
	sf::Sprite sprite;
	sprite.setTexture(context->textures.get(Textures::Background));
	context->window->draw(sprite);
}