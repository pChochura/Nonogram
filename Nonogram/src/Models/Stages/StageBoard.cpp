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

	this->view = context->window->getDefaultView();

	this->board = new Board;
	this->boardPadding = { 150, 200 };
	this->tileMargin = { 2, 2 };

	this->board->random(Difficulty::BabyStyle);

	float width = (float) (context->window->getSize().x - this->boardPadding.x) / this->board->width;
	float height = (float) (context->window->getSize().y - this->boardPadding.y) / this->board->height;

	this->tileSize = std::min(width, height);
	this->scaleAmount = 1.1f;
	this->scale = 1.0f;

	auto windowSize = context->window->getSize();
	this->boardOffset.x = (int)(windowSize.x - this->board->width * this->tileSize + boardPadding.x / 2) / 2;
	this->boardOffset.y = (int)(windowSize.y - this->board->height * this->tileSize + boardPadding.y / 2) / 2;
}

void StageBoard::draw(Context* context) {
	context->window->setView(this->view);

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
		} else if (event.mouseButton.button == sf::Mouse::Middle) {
			this->startPos = sf::Mouse::getPosition(*context->window);
			this->isPanning = true;
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (event.mouseButton.button == sf::Mouse::Middle) {
			this->isPanning = false;
		}
		break;
	case sf::Event::MouseMoved:
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (isInRange(context)) {
				markTile(getSelectedTile(context));
				return true;
			}
		} else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && isPanning) {
			sf::Vector2f offset = sf::Vector2f(this->startPos - sf::Mouse::getPosition(*context->window));
			Utils::moveView(context, offset * this->scale);

			this->startPos = sf::Mouse::getPosition(*context->window);
		}
		break;
	case sf::Event::MouseWheelScrolled:
		if (event.mouseWheelScroll.delta > 0) {
			this->scale /= this->scaleAmount;
			Utils::scaleView(context, (1.f / this->scaleAmount), { event.mouseWheelScroll.x, event.mouseWheelScroll.y });
		} else if (event.mouseWheelScroll.delta < 0) {
			this->scale *= this->scaleAmount;
			Utils::scaleView(context, this->scaleAmount, { event.mouseWheelScroll.x, event.mouseWheelScroll.y });
		}
		break;
	}
	return false;
}

void StageBoard::drawBoard(Context* context) const {
	sf::RectangleShape rect({ this->tileSize, this->tileSize });

	for (int i = 0; i < this->board->width; i++) {
		for (int j = 0; j < this->board->height; j++) {
			State value = this->board->getAt(i, j);

			if ((value & State::Empty) == State::Empty) {
				rect.setFillColor(sf::Color(178, 190, 195));
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

			rect.setPosition(i * (this->tileSize + this->tileMargin.x) + this->boardOffset.x, j * (this->tileSize + this->tileMargin.y) + this->boardOffset.y);
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
				i * (this->tileSize + this->tileMargin.x) + this->tileSize / 2.0f + this->boardOffset.x, 
				this->boardOffset.y - (text.getLocalBounds().height + 10) * (j + 1)
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
				this->boardOffset.x - (text.getLocalBounds().height / 2 + 10) * (j + 1),
				i * (this->tileSize + this->tileMargin.y) + this->tileSize / 2.0f + this->boardOffset.y
			);
			context->window->draw(text);
		}
	}
}

bool StageBoard::isInRange(Context* context) const {
	sf::Vector2f pos = context->window->mapPixelToCoords(sf::Mouse::getPosition(*context->window));
	return pos.x > this->boardOffset.x &&
		pos.x < this->boardOffset.x + this->board->width * this->tileSize &&
		pos.y > this->boardOffset.y &&
		pos.y < this->boardOffset.y + this->board->height * this->tileSize;
}

sf::Vector2i StageBoard::getSelectedTile(Context* context) const {
	sf::Vector2f pos = context->window->mapPixelToCoords(sf::Mouse::getPosition(*context->window));
	return {
		(int)((pos.x - this->boardOffset.x) / (this->tileSize + this->tileMargin.x)),
		(int)((pos.y - this->boardOffset.y) / (this->tileSize + this->tileMargin.y))
	};
}

void StageBoard::markTile(sf::Vector2i pos) const {
	if (pos.x < 0 || pos.x >= this->board->width || pos.y < 0 || pos.y >= this->board->height) {
		throw std::runtime_error(Utils::format("Cannot mark tile at (%d, %d)", pos.x, pos.y).c_str());
	}
	State state = this->board->getAt(pos.x, pos.y) | ((this->board->getAt(pos.x, pos.y) & State::Filled) == State::Filled ? State::Correct : State::Wrong);
	this->board->setAt(pos.x, pos.y, state);
}