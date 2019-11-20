#include "StageMessage.h"
#include "../Actors/Button.h"

void StageMessage::init(Context* context) {
	context->textures.load(Textures::ButtonPlayAgain, "data/Textures/button_play_again.png");
	context->textures.load(Textures::WinMenu, "data/Textures/win_menu.png");

	context->textures.get(Textures::ButtonPlayAgain).setSmooth(true);

	context->fonts.load(Fonts::Arcon, "data/Fonts/Arcon.otf");

	context->sounds.load(Sounds::ButtonTap, "data/Sounds/tap_sound.wav");

	this->tapSound = context->sounds.get(Sounds::ButtonTap);

	this->view = context->window->getDefaultView();

	this->messageMenuSize = { 500, 300 };
	this->messageMenuPos = { (context->window->getSize().x - this->messageMenuSize.x) / 2.0f, (context->window->getSize().y - this->messageMenuSize.y) / 2.0f };

	this->buttons.push_back((new Button(ID::ButtonOk, { 150.0f, ButtonSize::WrapContent }))
		->withPosition({ context->window->getSize().x / 2.0f - 75.0f, this->messageMenuPos.y + this->messageMenuSize.y - 75.0f })
		->withPadding({ 50, 30 })
		->withTexture(context->textures.get(Textures::ButtonPlayAgain))
		->withText("OK")
		->withTextFont(context->fonts.get(Fonts::Arcon))
		->withTextColor(sf::Color(255, 255, 255))
		->withTextSize(20)
		->build()
	);

	initClickListeners(context);
}

void StageMessage::initClickListeners(Context* context) {
	for (auto& button : this->buttons) {
		button->setOnClickListener([&](Clickable* b, bool inside) {
			this->sound.setBuffer(this->tapSound);
			this->sound.play();
			if (b->getId() == ID::ButtonOk) {
				this->onOkClickListener();
			}
		});
	}
}

void StageMessage::draw(Context* context) {
	context->window->setView(this->view);

	sf::Sprite sprite(context->textures.get(Textures::WinMenu));
	sprite.setPosition(this->messageMenuPos);
	sprite.setScale(this->messageMenuSize.x / sprite.getLocalBounds().width, this->messageMenuSize.y / sprite.getLocalBounds().height);
	context->window->draw(sprite);

	sf::Text text(this->message, context->fonts.get(Fonts::Arcon), 25);
	text.setFillColor(sf::Color(20, 37, 70));
	text.setOrigin(text.getLocalBounds().width / 2.0f, 0);
	text.setPosition({ context->window->getSize().x / 2.0f, messageMenuPos.y + 50.0f });
	context->window->draw(text);

	for (auto& button : this->buttons) {
		button->draw(context);
	}
}

bool StageMessage::onEvent(Context* context, sf::Event event) {
	context->window->setView(this->view);

	for (auto& button : this->buttons) {
		if (button->onEvent(context, event)) {
			return true;
		}
	}

	return true;
}

void StageMessage::setMessage(std::string message) {
	this->message = message;
}

void StageMessage::setOnOkClickListner(std::function<void(void)> onOkClickListener) {
	this->onOkClickListener = onOkClickListener;
}
