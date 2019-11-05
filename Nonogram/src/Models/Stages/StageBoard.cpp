#include <SFML/Graphics.hpp>
#include <math.h>
#include "../Board.h"
#include "../Enums/Difficulty.h"
#include "../Stages/StageBoard.h"
#include "../../Utils/Utils.h"
#include "../../Utils/ResourceIdentifier.h"
#include "../../Models/Shapes/RoundedRectangleShape.h"

void StageBoard::init(Context* context) {
	this->view = context->window->getDefaultView();

	this->board = new Board;
	this->boardPadding = { 150, 200 };
	this->tileMargin = { 2, 2 };

	this->board->random(Difficulty::BabyStyle);

	auto windowSize = context->window->getSize();
	float width = (float) (windowSize.x - this->boardPadding.x) / this->board->width;
	float height = (float) (windowSize.y - this->boardPadding.y) / this->board->height;

	this->tileSize = std::min(width, height);
	this->scaleAmount = 1.1f;
	this->scale = 1.0f;

	this->boardOffset.x = (int)(windowSize.x - this->board->width * this->tileSize + boardPadding.x / 2) / 2;
	this->boardOffset.y = (int)(windowSize.y - this->board->height * this->tileSize + boardPadding.y / 2) / 2;
}

void StageBoard::draw(Context* context) {
	context->window->setView(this->view);

	drawBoard(context);
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
			Utils::moveView(context, &this->view, offset * this->scale);

			this->startPos = sf::Mouse::getPosition(*context->window);
		}
		break;
	case sf::Event::MouseWheelScrolled:
		if (event.mouseWheelScroll.delta > 0) {
			this->scale /= this->scaleAmount;
			Utils::scaleView(context, &this->view, (1.f / this->scaleAmount), { event.mouseWheelScroll.x, event.mouseWheelScroll.y });
		} else if (event.mouseWheelScroll.delta < 0) {
			this->scale *= this->scaleAmount;
			Utils::scaleView(context, &this->view, this->scaleAmount, { event.mouseWheelScroll.x, event.mouseWheelScroll.y });
		}
		break;
	}
	return false;
}

void StageBoard::drawBoard(Context* context) const {
	sf::RoundedRectangleShape rect({ this->tileSize, this->tileSize }, 5, 50);
	rect.setOutlineColor(sf::Color(51, 51, 51));

	sf::Vector2i hoveredTile = getSelectedTile(context);

	if (!isInRange(context)) {
		hoveredTile.x = hoveredTile.y = -1;
	}

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

			rect.setOutlineThickness(hoveredTile.x == i && hoveredTile.y == j ? -2.0f : 0.0f);

			rect.setPosition(i * (this->tileSize + this->tileMargin.x) + this->boardOffset.x, j * (this->tileSize + this->tileMargin.y) + this->boardOffset.y);
			context->window->draw(rect);
		}
	}

	if (hoveredTile.x != -1 && hoveredTile.y != -1) {
		rect.setFillColor(sf::Color(30, 82, 88, 50));
		rect.setOutlineThickness(0.0f);

		rect.setSize({ this->tileSize, (this->tileSize + this->tileMargin.y) * this->board->height - this->tileMargin.y });
		rect.setPosition({ hoveredTile.x * (this->tileSize + this->tileMargin.x) + this->boardOffset.x, (float)this->boardOffset.y });
		context->window->draw(rect);

		rect.setSize({ (this->tileSize + this->tileMargin.x) * this->board->width - this->tileMargin.x, this->tileSize });
		rect.setPosition({ (float)this->boardOffset.x, hoveredTile.y * (this->tileSize + this->tileMargin.y) + this->boardOffset.y });
		context->window->draw(rect);
	}
}

bool StageBoard::isInRange(Context* context) const {
	sf::Vector2f pos = context->window->mapPixelToCoords(sf::Mouse::getPosition(*context->window));
	return pos.x > this->boardOffset.x &&
		pos.x < this->boardOffset.x + this->board->width * (this->tileSize + this->tileMargin.x) &&
		pos.y > this->boardOffset.y &&
		pos.y < this->boardOffset.y + this->board->height * (this->tileSize + this->tileMargin.y);
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