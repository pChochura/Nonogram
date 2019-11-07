#include "StageDifficultyMenu.h"

void StageDifficultyMenu::init(Context* context) {
	context->fonts.load(Fonts::Arcon, "data/Fonts/Arcon.otf");

	Button *button = new Button(0, "Start", context->fonts.get(Fonts::Arcon), 30, { 300, 100 }, { 50, 20 });
	button->setBackgroundColor(sf::Color(0, 150, 136));
	this->buttons.push_back(button);
}

void StageDifficultyMenu::draw(Context* context) {
	context->window->setView(this->view);

	for (auto& button : this->buttons) {
		context->window->draw(*button);
	}
}

bool StageDifficultyMenu::onEvent(Context* context, sf::Event) {
	context->window->setView(this->view);

	return false;
}