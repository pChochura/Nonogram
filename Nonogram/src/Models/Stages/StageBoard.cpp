#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

	context->sounds.load(Sounds::BoardTap, "data/Sounds/tap_sound_3.wav");

	this->tapSound = context->sounds.get(Sounds::BoardTap);
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
		if (event.mouseButton.button == sf::Mouse::Left || event.mouseButton.button == sf::Mouse::Right) {
			if (isInRange(context)) {
				State currentState = this->board->getCurrentState();
				if (event.mouseButton.button == sf::Mouse::Right) {
					this->board->setCurrentState(State::MarkedNot);
				}
				sf::Vector2i selectedTile = getSelectedTile(context);
				State state = this->board->getAt(selectedTile.x, selectedTile.y);
				if (!this->isSwiping && (state & this->board->getCurrentState()) != State::None) {
					this->isUndoingSelection = true;
				}
				markTile(selectedTile);
				this->board->setCurrentState(currentState);
				return true;
			}
		} else if (event.mouseButton.button == sf::Mouse::Middle) {
			this->startPos = context->window->mapPixelToCoords(sf::Mouse::getPosition(*context->window));
			this->isPanning = true;
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (event.mouseButton.button == sf::Mouse::Middle) {
			this->isPanning = false;
		} else if (event.mouseButton.button == sf::Mouse::Left || event.mouseButton.button == sf::Mouse::Right) {
			this->isSwiping = false;
			this->isUndoingSelection = false;
		}
		break;
	case sf::Event::MouseMoved:
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			if (isInRange(context)) {
				State currentState = this->board->getCurrentState();
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
					this->board->setCurrentState(State::MarkedNot);
				}
				this->isSwiping = true;
				markTile(getSelectedTile(context));
				this->board->setCurrentState(currentState);
				return true;
			}
		} else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && isPanning) {
			sf::Vector2f offset = sf::Vector2f(this->startPos - context->window->mapPixelToCoords(sf::Mouse::getPosition(*context->window)));
			Utils::moveView(context, &this->view, offset);

			this->startPos = context->window->mapPixelToCoords(sf::Mouse::getPosition(*context->window));
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

	if (!isInRange(context)) {
		hoveredTile.x = hoveredTile.y = -1;
	}

	for (int i = 0; i < this->board->width; i++) {
		for (int j = 0; j < this->board->height; j++) {
			tileEmpty.setPosition(i * (this->board->tileSize + this->board->tileMargin.x) + this->board->offset.x, j * (this->board->tileSize + this->board->tileMargin.y) + this->board->offset.y);
			context->window->draw(tileEmpty);

			State value = this->board->getAt(i, j);
			if ((value & State::Selected) != State::None) {
				tileMark.setTexture(context->textures.get(Textures::BoardTileSelected));
				drawTile = true;
			}
			if ((value & State::Marked) != State::None) {
				tileMark.setTexture(context->textures.get(Textures::BoardTileMarked));
				drawTile = true;
			}
			if ((value & State::MarkedNot) != State::None) {
				tileMark.setTexture(context->textures.get(Textures::BoardTileMarkedNot));
				drawTile = true;
			}
			if ((value & State::Lost) != State::None) {
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

void StageBoard::markTile(sf::Vector2i pos) {
	if (pos.x < 0 || pos.x >= this->board->width || pos.y < 0 || pos.y >= this->board->height) {
		return;
	}
	State state = this->board->getAt(pos.x, pos.y);
	State rawState = state & (State::Empty | State::Filled);
	State selectionState = state & ~rawState;
	State currentState = this->board->getCurrentState();

	if ((selectionState & State::Const) != State::None) {
		return;
	}

	if (this->isUndoingSelection && (currentState & (selectionState | rawState)) == selectionState) {
		state = rawState;
	} else {
		switch (currentState) {
		case State::Selected:
			if ((selectionState & State::Selected) == selectionState || (!this->isUndoingSelection && (selectionState & State::Marked) == selectionState)) {
				state = State::Selected;
			}
			break;
		case State::Marked:
			if ((selectionState & State::Marked) == selectionState) {
				state = State::Marked;
			}
			break;
		case State::MarkedNot:
			if ((selectionState & State::Marked) == selectionState) {
				state = State::MarkedNot;
			}
			break;
		}
	}

	if ((rawState | state) != this->board->getAt(pos.x, pos.y)) {
		this->sound.setBuffer(this->tapSound);
		this->sound.play();
	}

	this->board->setAt(pos.x, pos.y, rawState | state);
	if (currentState == State::Selected) {
		this->board->fillMarkedNot(pos.x, pos.y);
	}

	if (this->board->isBoardCompleted()) {
		this->board->toggleMarked(State::MarkedNot);
	}
}