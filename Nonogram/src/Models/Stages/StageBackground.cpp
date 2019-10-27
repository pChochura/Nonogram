#include <SFML/Graphics.hpp>
#include "../Stages/StageBackground.h"
#include "../../Utils/ResourceIdentifier.h"

void StageBackground::init(Context* context) {
	context->textures.load(Textures::Background, "data/Images/image_background.jpg");
}

void StageBackground::draw(Context* context) {
	sf::RectangleShape rect({ context->window->getSize().x + 1.0f, context->window->getSize().y + 1.0f });
	rect.setFillColor(sf::Color(0, 0, 0));
	context->window->draw(rect);
}

bool StageBackground::mousePressedEvent(Context* context, sf::Event event) {
	return false;
}
