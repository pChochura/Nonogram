#include <SFML/Graphics.hpp>
#include <math.h>
#include "../Board.h"
#include "../Enums/Difficulty.h"
#include "../Stages/StageBoard.h"
#include "../../Utils/ResourceIdentifier.h"

void StageBoard::init(Context* context) {
	context->fonts.load(Fonts::Arcon, "data/Fonts/Arcon.otf");

	this->board = new Board;
	this->paddingHorizontal = 150;
	this->paddingVertical = 200;

	this->board->random(Difficulty::BabyStyle);

	float width = (context->window->getSize().x - this->paddingHorizontal) / this->board->width;
	float height = (context->window->getSize().y - this->paddingVertical) / this->board->height;

	this->tileSize = std::min(width, height);
}

void StageBoard::draw(Context* context) {
	drawBoard(context);
	drawValues(context);
}

bool StageBoard::mousePressedEvent(Context* context, sf::Event event) {
	sf::Vector2u windowSize = context->window->getSize();
	float offsetX = (windowSize.x - this->board->width * this->tileSize) / 2;
	float offsetY = (windowSize.y - this->board->height * this->tileSize) / 2;

	if (event.mouseButton.button == sf::Mouse::Left) {
		if (event.mouseButton.x > offsetX && event.mouseButton.x < windowSize.x - offsetX &&
			event.mouseButton.y > offsetY && event.mouseButton.y < windowSize.y - offsetY) {
			int x = (event.mouseButton.x - offsetX) / this->tileSize;
			int y = (event.mouseButton.y - offsetY) / this->tileSize;
			State state = this->board->getAt(x, y) | ((this->board->getAt(x, y) & State::Filled) == State::Filled ? State::Correct : State::Wrong);
			this->board->setAt(x, y, state);
			return true;
		}
	}
	return false;
}

void StageBoard::drawBoard(Context* context) const {
	sf::RectangleShape rect({ this->tileSize, this->tileSize });
	rect.setOrigin(0, 0);

	float offsetX = (context->window->getSize().x - this->board->width * this->tileSize) / 2;
	float offsetY = (context->window->getSize().y - this->board->height * this->tileSize) / 2;

	for (int i = 0; i < this->board->width; i++) {
		for (int j = 0; j < this->board->height; j++) {
			State value = this->board->getAt(i, j);

			if ((value & State::Empty) == State::Empty) {
				rect.setFillColor(sf::Color(175, 175, 175));
			}
			if ((value & State::Correct) == State::Correct) {
				rect.setFillColor(sf::Color(51, 151, 51));
			}
			if ((value & State::Wrong) == State::Wrong) {
				rect.setFillColor(sf::Color(151, 51, 51));
			}
			if ((value & State::Mark) == State::Mark) {
				rect.setFillColor(sf::Color(51, 51, 51));
			}

			rect.setPosition(i * (this->tileSize + 1) + offsetX, j * (this->tileSize + 1) + offsetY);
			context->window->draw(rect);
		}
	}
}

void StageBoard::drawValues(Context* context) const {
	sf::Text text("", context->fonts.get(Fonts::Arcon), 15U);
	text.setFillColor(sf::Color(255, 255, 255));

	float offsetX = (context->window->getSize().x - this->board->width * this->tileSize) / 2;
	float offsetY = (context->window->getSize().y - this->board->height * this->tileSize) / 2;

	for (int i = 0; i < this->board->width; i++) {
		auto values = this->board->getVerticalValuesFor(i);
		int j = 0;
		for (auto it = values.rbegin(); it != values.rend(); it++, j++) {
			text.setString(std::to_string(*it));
			text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
			text.setPosition(i * (this->tileSize + 1) + this->tileSize / 2.0f + offsetX, offsetY - (text.getLocalBounds().height + 10) * (j + 1));
			context->window->draw(text);
		}
	}

	for (int i = 0; i < this->board->height; i++) {
		auto values = this->board->getHorizontalValuesFor(i);
		int j = 0;
		for (auto it = values.rbegin(); it != values.rend(); it++, j++) {
			text.setString(std::to_string(*it));
			text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
			text.setPosition(offsetX - (text.getLocalBounds().width + 10) * (j + 1), i * (this->tileSize + 1) + this->tileSize / 2.0f + offsetY);
			context->window->draw(text);
		}
	}
}