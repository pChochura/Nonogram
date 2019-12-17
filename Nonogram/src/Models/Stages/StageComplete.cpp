#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "StageComplete.h"
#include "../Actors/Button.h"
#include "../../Utils/Utils.h"

void StageComplete::init(Context* context) {
	context->textures.load(Textures::WinMenu, "data/Textures/win_menu.png");
	context->textures.load(Textures::ButtonExit, "data/Textures/button_exit.png");
	context->textures.load(Textures::ButtonPlayAgain, "data/Textures/button_play_again.png");

	context->textures.get(Textures::WinMenu).setSmooth(true);
	context->textures.get(Textures::ButtonExit).setSmooth(true);
	context->textures.get(Textures::ButtonPlayAgain).setSmooth(true);

	context->sounds.load(Sounds::ButtonTap, "data/Sounds/tap_sound.wav");

	this->tapSound = context->sounds.get(Sounds::ButtonTap);

	this->view = context->window->getDefaultView();

	this->winMenuSize = { 600, 500 };
	this->winMenuPos = { (context->window->getSize().x - this->winMenuSize.x) / 2.0f, (context->window->getSize().y - this->winMenuSize.y) / 2.0f };

	this->buttons.push_back(
		(new Button(ID::ButtonExit, { 200, ButtonSize::WrapContent }))
		->withPosition({ context->window->getSize().x / 2.0f - 225.0f, winMenuPos.y + winMenuSize.y - 120.0f })
		->withPadding({ 50, 50 })
		->withTexture(context->textures.get(Textures::ButtonExit))
		->withText("EXIT")
		->withTextFont(context->fonts.get(Fonts::Arcon))
		->withTextColor(sf::Color(255, 255, 255))
		->withTextSize(25)
		->build()
	);

	this->buttons.push_back(
		(new Button(ID::ButtonPlayAgain, { 200, ButtonSize::WrapContent }))
		->withPosition({ context->window->getSize().x / 2.0f + 25.0f, winMenuPos.y + winMenuSize.y - 120.0f })
		->withPadding({ 50, 50 })
		->withTexture(context->textures.get(Textures::ButtonPlayAgain))
		->withText("PLAY AGAIN")
		->withTextFont(context->fonts.get(Fonts::Arcon))
		->withTextColor(sf::Color(255, 255, 255))
		->withTextSize(25)
		->build()
	);

	initClickListeners(context);
}

void StageComplete::initClickListeners(Context* context) {
	for (auto& button : this->buttons) {
		button->setOnClickListener([&](Clickable* b, bool inside) {
			this->sound.setBuffer(this->tapSound);
			this->sound.play();
			switch (b->getId()) {
			case ID::ButtonPlayAgain:
				this->onPlayAgainClickListener();
				break;
			case ID::ButtonExit:
				this->onExitClickListener();
				break;
			}
		});
	}
}

void StageComplete::draw(Context* context) {
	context->window->setView(this->view);

	sf::Sprite sprite(context->textures.get(Textures::WinMenu));
	sprite.setPosition(this->winMenuPos);
	sprite.setScale(this->winMenuSize.x / sprite.getLocalBounds().width, this->winMenuSize.y / sprite.getLocalBounds().height);
	context->window->draw(sprite);

	sf::Text text("Congratulations!", context->fonts.get(Fonts::Arcon), 50);
	text.setFillColor(sf::Color(81, 191, 189));
	text.setStyle(sf::Text::Bold);
	text.setOrigin(text.getLocalBounds().width / 2.0f, 0);
	text.setPosition({ context->window->getSize().x / 2.0f + 3.0f, winMenuPos.y + 53.0f });
	context->window->draw(text);

	text.setPosition({ context->window->getSize().x / 2.0f, winMenuPos.y + 50.0f });
	text.setFillColor(sf::Color(20, 37, 70));
	context->window->draw(text);

	const char* diff;
	switch (this->difficulty) {
	case Difficulty::BabyStyle:
		diff = "Baby Style";
		break;
	case Difficulty::Decent:
		diff = "Decent";
		break;
	case Difficulty::Impresive:
		diff = "Impresive";
		break;
	case Difficulty::WorldClass:
		diff = "World Class";
		break;
	default:
		diff = "a";
		break;
	}

	char buffer[50];
	sprintf_s(buffer, "You solved %s nonogram in", diff);
	text.setString(buffer);
	text.setCharacterSize(25);
	text.setStyle(sf::Text::Regular);
	text.setOrigin(text.getLocalBounds().width / 2.0f, 0);
	text.setPosition({ context->window->getSize().x / 2.0f, winMenuPos.y + 150.0f });
	context->window->draw(text);

	text.setString(Utils::formatTime(elapsedTime));
	text.setCharacterSize(65);
	text.setStyle(sf::Text::Bold);
	text.setOrigin(text.getLocalBounds().width / 2.0f, 0);
	text.setPosition({ context->window->getSize().x / 2.0f, winMenuPos.y + 250.0f });
	context->window->draw(text);

	for (auto& button : this->buttons) {
		button->draw(context);
	}
}

bool StageComplete::onEvent(Context* context, sf::Event event) {
	context->window->setView(this->view);

	for (auto& button : this->buttons) {
		if (button->onEvent(context, event)) {
			return true;
		}
	}

	return true;
}

void StageComplete::setElapsedTime(sf::Time elapsedTime) {
	this->elapsedTime = elapsedTime;
}

void StageComplete::setDifficulty(Difficulty difficulty) {
	this->difficulty = difficulty;
}

void StageComplete::setOnPlayAgainClickListener(std::function<void(void)> onPlayAgainClickListener) {
	this->onPlayAgainClickListener = onPlayAgainClickListener;
}

void StageComplete::setOnExitClickListner(std::function<void(void)> onExitClickListener) {
	this->onExitClickListener = onExitClickListener;
}
