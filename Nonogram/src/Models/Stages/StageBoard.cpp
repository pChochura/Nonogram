#include <SFML/Graphics.hpp>
#include <math.h>
#include "../Board.h"
#include "../Enums/Difficulty.h"
#include "../Stages/StageBoard.h"
#include "../../Utils/Utils.h"
#include "../../Utils/ResourceIdentifier.h"
#include "../../Models/Shapes/RoundedRectangleShape.h"

void StageBoard::init(Context* context) {
	context->textures.load(Textures::BoardTile, "data/Textures/board_tile.png");
	context->textures.load(Textures::BoardTileSelected, "data/Textures/board_tile_selected.png");
	context->textures.load(Textures::BoardTileMarked, "data/Textures/board_tile_marked.png");
	context->textures.load(Textures::BoardTileMarkedNot, "data/Textures/board_tile_marked_not.png");
	context->textures.load(Textures::BoardTileLost, "data/Textures/board_tile_lost.png");
	context->textures.load(Textures::BoardTileHovered, "data/Textures/board_tile_hovered.png");

	this->view = context->window->getDefaultView();
}

void StageBoard::setBoard(Board* board) {
	this->board = board;
}

void StageBoard::draw(Context* context) {
	context->window->setView(this->view);

	drawBoard(context);
}

bool StageBoard::onEvent(Context* context, sf::Event event) {
	context->window->setView(this->view);

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
			Utils::moveView(context, &this->view, offset * this->board->scale);

			this->startPos = sf::Mouse::getPosition(*context->window);
		}
		break;
	case sf::Event::MouseWheelScrolled:
		if (event.mouseWheelScroll.delta > 0) {
			this->board->scale /= this->board->scaleAmount;
			Utils::scaleView(context, &this->view, (1.f / this->board->scaleAmount), { event.mouseWheelScroll.x, event.mouseWheelScroll.y });
		} else if (event.mouseWheelScroll.delta < 0) {
			this->board->scale *= this->board->scaleAmount;
			Utils::scaleView(context, &this->view, this->board->scaleAmount, { event.mouseWheelScroll.x, event.mouseWheelScroll.y });
		}
		break;
	}
	return false;
}

void StageBoard::drawBoard(Context* context) const {
	sf::Sprite tileEmpty(context->textures.get(Textures::BoardTile));
	tileEmpty.setScale((this->board->tileSize - this->board->tileMargin.x) / tileEmpty.getLocalBounds().width, (this->board->tileSize - this->board->tileMargin.y) / tileEmpty.getLocalBounds().height);

	sf::Sprite tileMark;
	bool drawTile = false;

	sf::Vector2i hoveredTile = getSelectedTile(context);

	for (int i = 0; i < this->board->width; i++) {
		for (int j = 0; j < this->board->height; j++) {
			tileEmpty.setPosition(i * (this->board->tileSize + this->board->tileMargin.x) + this->board->offset.x, j * (this->board->tileSize + this->board->tileMargin.y) + this->board->offset.y);
			context->window->draw(tileEmpty);

			State value = this->board->getAt(i, j);
			if ((value & State::Selected) == State::Selected) {
				tileMark.setTexture(context->textures.get(Textures::BoardTileSelected));
				drawTile = true;
			}
			if ((value & State::Marked) == State::Marked) {
				tileMark.setTexture(context->textures.get(Textures::BoardTileMarked));
				drawTile = true;
			}
			if ((value & State::MarkedNot) == State::MarkedNot) {
				tileMark.setTexture(context->textures.get(Textures::BoardTileMarkedNot));
				drawTile = true;
			}
			if ((value & State::Lost) == State::Lost) {
				tileMark.setTexture(context->textures.get(Textures::BoardTileLost));
				drawTile = true;
			}

			if (drawTile) {
				drawTile = false;
				tileMark.setScale((this->board->tileSize - this->board->tileMargin.x) / tileMark.getLocalBounds().width, (this->board->tileSize - this->board->tileMargin.y) / tileMark.getLocalBounds().height);
				tileMark.setPosition(i * (this->board->tileSize + this->board->tileMargin.x) + this->board->offset.x, j * (this->board->tileSize + this->board->tileMargin.y) + this->board->offset.y);
				context->window->draw(tileMark);
			}

			if (hoveredTile.x == i && hoveredTile.y == j) {
				tileMark.setTexture(context->textures.get(Textures::BoardTileHovered));
				tileMark.setScale((this->board->tileSize - this->board->tileMargin.x) / tileMark.getLocalBounds().width, (this->board->tileSize - this->board->tileMargin.y) / tileMark.getLocalBounds().height);
				tileMark.setPosition(i * (this->board->tileSize + this->board->tileMargin.x) + this->board->offset.x, j * (this->board->tileSize + this->board->tileMargin.y) + this->board->offset.y);
				context->window->draw(tileMark);
			}
		}
	}
}

bool StageBoard::isInRange(Context* context) const {
	sf::Vector2f pos = context->window->mapPixelToCoords(sf::Mouse::getPosition(*context->window));
	return pos.x > this->board->offset.x &&
		pos.x < this->board->offset.x + this->board->width * (this->board->tileSize + this->board->tileMargin.x) &&
		pos.y > this->board->offset.y &&
		pos.y < this->board->offset.y + this->board->height * (this->board->tileSize + this->board->tileMargin.y);
}

sf::Vector2i StageBoard::getSelectedTile(Context* context) const {
	sf::Vector2f pos = context->window->mapPixelToCoords(sf::Mouse::getPosition(*context->window));
	return {
		(int)((pos.x - this->board->offset.x) / (this->board->tileSize + this->board->tileMargin.x)),
		(int)((pos.y - this->board->offset.y) / (this->board->tileSize + this->board->tileMargin.y))
	};
}

void StageBoard::markTile(sf::Vector2i pos) const {
	if (pos.x < 0 || pos.x >= this->board->width || pos.y < 0 || pos.y >= this->board->height) {
		throw std::runtime_error(Utils::format("Cannot mark tile at (%d, %d)", pos.x, pos.y).c_str());
	}
	State state = this->board->getAt(pos.x, pos.y);
	State rawState = state & (State::Empty | State::Filled);
	State currentState = this->board->getCurrentState();
	if ((state & currentState) == currentState) {
		state = state & ~currentState;
	} else if (rawState == state) {
		state = state | currentState;
	}
	this->board->setAt(pos.x, pos.y, state);
}