#include "StageDifficultyMenu.h"
#include "../Actors/ButtonGroup.h"

void StageDifficultyMenu::init(Context* context) {
	context->fonts.load(Fonts::Arcon, "data/Fonts/Arcon.otf");

	this->view = context->window->getDefaultView();

	Button *button = new Button(
		ID::ButtonBabyStyle, "Baby Style", 
		context->fonts.get(Fonts::Arcon), 20, 
		{ context->window->getSize().x / 2.0f, context->window->getSize().y - 250.0f },
		{ 50, 10 }
	);
	button->setBackgroundColor(sf::Color(0, 150, 136));
	this->buttons.push_back(button);
	button = new Button(
		ID::ButtonDecent, "Decent",
		context->fonts.get(Fonts::Arcon), 20,
		{ context->window->getSize().x / 2.0f, context->window->getSize().y - 200.0f },
		{ 50, 10 }
	);
	button->setBackgroundColor(sf::Color(255, 87, 34));
	this->buttons.push_back(button);
	button = new Button(
		ID::ButtonImpresive, "Impresive",
		context->fonts.get(Fonts::Arcon), 20,
		{ context->window->getSize().x / 2.0f, context->window->getSize().y - 150.0f },
		{ 50, 10 }
	);
	button->setBackgroundColor(sf::Color(63, 81, 181));
	this->buttons.push_back(button);
	button = new Button(
		ID::ButtonWorldClass, "World Class",
		context->fonts.get(Fonts::Arcon), 20,
		{ context->window->getSize().x / 2.0f, context->window->getSize().y - 100.0f },
		{ 50, 10 }
	);
	button->setBackgroundColor(sf::Color(233, 30, 99));
	this->buttons.push_back(button);

	initClickListeners(context);
}

void StageDifficultyMenu::initClickListeners(Context* context) {
	for (auto& button : this->buttons) {
		button->setOnClickListener([&](Clickable* b, bool inside) {
			switch (b->getId()) {
			case ID::ButtonBabyStyle:
				this->onClickListener(Difficulty::BabyStyle);
				break;
			case ID::ButtonDecent:
				this->onClickListener(Difficulty::Decent);
				break;
			case ID::ButtonImpresive:
				this->onClickListener(Difficulty::Impresive);
				break;
			case ID::ButtonWorldClass:
				this->onClickListener(Difficulty::WorldClass);
				break;
			}
		});
	}
}

void StageDifficultyMenu::draw(Context* context) {
	context->window->setView(this->view);

	for (auto& button : this->buttons) {
		button->draw(context);
	}
}

bool StageDifficultyMenu::onEvent(Context* context, sf::Event event) {
	context->window->setView(this->view);

	for (auto& button : this->buttons) {
		if (button->onEvent(context, event)) {
			return true;
		}
	}

	return false;
}

void StageDifficultyMenu::setOnClickListener(std::function<void(Difficulty)> onClickListener) {
	this->onClickListener = onClickListener;
}