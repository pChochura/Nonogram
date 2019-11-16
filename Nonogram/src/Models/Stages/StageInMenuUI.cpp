#include "StageInMenuUI.h"
#include "../Actors/Button.h"

void StageInMenuUI::init(Context* context) {
	context->textures.load(Textures::ButtonExit, "data/Textures/button_exit.png");

	context->textures.get(Textures::ButtonExit).setSmooth(true);

	context->fonts.load(Fonts::Arcon, "data/Fonts/Arcon.otf");

	context->sounds.load(Sounds::ButtonTap, "data/Sounds/tap_sound.wav");

	this->tapSound = context->sounds.get(Sounds::ButtonTap);

	this->view = context->window->getDefaultView();

	this->buttons.push_back((new Button(ID::ButtonExit, { 150.0f, ButtonSize::WrapContent }))
		->withPosition({ context->window->getSize().x - 200.0f, context->window->getSize().y - 75.0f })
		->withPadding({ 50, 30 })
		->withTexture(context->textures.get(Textures::ButtonExit))
		->withText("Exit")
		->withTextFont(context->fonts.get(Fonts::Arcon))
		->withTextColor(sf::Color(255, 255, 255))
		->withTextSize(20)
		->build()
	);

	initClickListeners(context);
}

void StageInMenuUI::initClickListeners(Context* context) {
	for (auto& button : this->buttons) {
		button->setOnClickListener([&, context](Clickable* b, bool inside) {
			this->sound.setBuffer(this->tapSound);
			this->sound.play();
			if (b->getId() == ID::ButtonExit) {
				context->window->close();
			}
		});
	}
}

void StageInMenuUI::draw(Context* context) {
	context->window->setView(this->view);

	for (auto& button : this->buttons) {
		button->draw(context);
	}
}

bool StageInMenuUI::onEvent(Context* context, sf::Event event) {
	context->window->setView(this->view);

	for (auto& button : this->buttons) {
		if (button->onEvent(context, event)) {
			return true;
		}
	}

	return false;
}