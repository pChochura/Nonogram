#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "../Board.h"
#include "../Enums/Difficulty.h"
#include "../Stages/StageBoard.h"
#include "../../Utils/Utils.h"
#include "../../Utils/ResourceIdentifier.h"

void StageBoard::init(Context* context) {
	context->fonts.load(Fonts::Arcon, "data/Fonts/Arcon.otf");

	this->board = new Board;
	this->padding.x = 150;
	this->padding.y = 200;

	this->board->random(Difficulty::BabyStyle);

	float width = (float) (context->window->getSize().x - this->padding.x) / this->board->width;
	float height = (float) (context->window->getSize().y - this->padding.y) / this->board->height;

	this->tileSize = std::min(width, height);
	this->scale = { 1.0f, 1.0f };

	auto windowSize = context->window->getSize();
	this->offset.x = (int)(windowSize.x - this->board->width * this->tileSize * this->scale.y + padding.x / 2) / 2;
	this->offset.y = (int)(windowSize.y - this->board->height * this->tileSize * this->scale.y + padding.y / 2) / 2;
}

void StageBoard::draw(Context* context) {
	drawBoard(context);
	drawValues(context);
}

bool StageBoard::onEvent(Context* context, sf::Event event) {
	switch (event.type) {
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (isInRange(context)) {
				markTile(getSelectedTile(context));
				return true;
			}
		} else if (event.mouseButton.button == sf::Mouse::Right) {
			this->startPos = sf::Mouse::getPosition(*context->window);
		}
		break;
	case sf::Event::MouseMoved:
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (isInRange(context)) {
				markTile(getSelectedTile(context));
				return true;
			}
		} else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			this->offset -= this->startPos - sf::Mouse::getPosition(*context->window);
			this->startPos = sf::Mouse::getPosition(*context->window);
		}
		break;
	case sf::Event::MouseWheelScrolled:
		//TODO: fix scaling
		std::cout << event.mouseWheelScroll.delta;
		sf::Vector2i pos = sf::Mouse::getPosition(*context->window);
		sf::Vector2f initial = { pos.x - context->window->getSize().x / 2.0f + this->offset.x, pos.y - context->window->getSize().y / 2.0f + this->offset.y };

		sf::Vector2f before = { initial.x * this->scale.x, initial.y * this->scale.y };

		if (event.mouseWheelScroll.delta < 0) {
			this->scale *= 0.97f;
		} else {
			this->scale *= 1.07f;
		}

		sf::Vector2f after = { initial.x * this->scale.x, initial.y * this->scale.y };

		sf::Vector2f diff = before - after;
		this->offset.x += diff.x;
		this->offset.y += diff.y;

		break;
	}
	return false;
}

void StageBoard::drawBoard(Context* context) const {
	sf::RectangleShape rect({ this->tileSize * this->scale.x, this->tileSize * this->scale.y });

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

			rect.setPosition(i * (this->tileSize * this->scale.x + 1) + this->offset.x, j * (this->tileSize * this->scale.y + 1) + this->offset.y);
			context->window->draw(rect);
		}
	}
}

void StageBoard::drawValues(Context* context) const {
	sf::Text text("", context->fonts.get(Fonts::Arcon), 15U);
	text.setFillColor(sf::Color(255, 255, 255));

	for (int i = 0; i < this->board->width; i++) {
		auto values = this->board->getVerticalValuesFor(i);
		int j = 0;
		for (auto it = values.rbegin(); it != values.rend(); it++, j++) {
			text.setString(std::to_string(*it));
			text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
			text.setPosition(
				i * (this->tileSize * this->scale.x + 1) + this->tileSize * this->scale.x / 2.0f + this->offset.x, 
				this->offset.y - (text.getLocalBounds().height + 10) * (j + 1)
			);
			context->window->draw(text);
		}
	}

	for (int i = 0; i < this->board->height; i++) {
		auto values = this->board->getHorizontalValuesFor(i);
		int j = 0;
		for (auto it = values.rbegin(); it != values.rend(); it++, j++) {
			text.setString(std::to_string(*it));
			text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
			text.setPosition(
				this->offset.x - (text.getLocalBounds().height / 2 + 10) * (j + 1),
				i * (this->tileSize * this->scale.y + 1) + this->tileSize * this->scale.y / 2.0f + this->offset.y
			);
			context->window->draw(text);
		}
	}
}

bool StageBoard::isInRange(Context* context) const {
	return sf::Mouse::getPosition(*context->window).x > this->offset.x &&
		sf::Mouse::getPosition(*context->window).x < this->offset.x + this->board->width * this->tileSize * this->scale.x &&
		sf::Mouse::getPosition(*context->window).y > this->offset.y &&
		sf::Mouse::getPosition(*context->window).y < this->offset.y + this->board->height * this->tileSize * this->scale.y;
}

sf::Vector2i StageBoard::getSelectedTile(Context* context) const {
	return {
		(int)((sf::Mouse::getPosition(*context->window).x - this->offset.x) / this->tileSize * this->scale.x),
		(int)((sf::Mouse::getPosition(*context->window).y - this->offset.y) / this->tileSize * this->scale.y)
	};
}

void StageBoard::markTile(sf::Vector2i pos) const {
	if (pos.x < 0 || pos.x >= this->board->width || pos.y < 0 || pos.y >= this->board->height) {
		throw std::runtime_error(Utils::format("Cannot mark tile at (%d, %d)", pos.x, pos.y).c_str());
	}
	State state = this->board->getAt(pos.x, pos.y) | ((this->board->getAt(pos.x, pos.y) & State::Filled) == State::Filled ? State::Correct : State::Wrong);
	this->board->setAt(pos.x, pos.y, state);
}