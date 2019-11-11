#include <algorithm>
#include <iostream>
#include "StageInGameUI.h"
#include "../Board.h"
#include "../Actors/Button.h"
#include "../Actors/ButtonGroup.h"
#include "../Shapes/RoundedRectangleShape.h"
#include "../../Utils/Utils.h"

void StageInGameUI::init(Context* context) {
	context->textures.load(Textures::Circle, "data/Textures/circle.png");
	context->textures.load(Textures::BottomMenu, "data/Textures/bottom_menu.png");
	context->textures.load(Textures::BoardTileWin, "data/Textures/board_tile_win.png");
	context->textures.load(Textures::BoardTileLost, "data/Textures/board_tile_lost.png");
	context->textures.load(Textures::BoardTileMarked, "data/Textures/board_tile_marked.png");
	context->textures.load(Textures::BoardTileMarkedNot, "data/Textures/board_tile_marked_not.png");
	context->textures.load(Textures::BoardTileMarkedExpand, "data/Textures/board_tile_marked_expand.png");
	context->textures.load(Textures::MarkExpandMenu, "data/Textures/mark_expand_menu.png");
	context->textures.load(Textures::ButtonMarkedToSelected, "data/Textures/button_marked_to_selected.png");
	context->textures.load(Textures::ButtonMarkedToNot, "data/Textures/button_marked_to_not.png");
	context->textures.load(Textures::ButtonMarkedToEmpty, "data/Textures/button_marked_to_empty.png");

	context->textures.get(Textures::Circle).setSmooth(true);
	context->textures.get(Textures::BottomMenu).setSmooth(true);
	context->textures.get(Textures::BoardTileWin).setSmooth(true);
	context->textures.get(Textures::BoardTileLost).setSmooth(true);
	context->textures.get(Textures::BoardTileMarked).setSmooth(true);
	context->textures.get(Textures::BoardTileMarkedNot).setSmooth(true);
	context->textures.get(Textures::BoardTileMarkedExpand).setSmooth(true);
	context->textures.get(Textures::MarkExpandMenu).setSmooth(true);
	context->textures.get(Textures::ButtonMarkedToSelected).setSmooth(true);
	context->textures.get(Textures::ButtonMarkedToNot).setSmooth(true);
	context->textures.get(Textures::ButtonMarkedToEmpty).setSmooth(true);


	context->fonts.load(Fonts::Arcon, "data/Fonts/Arcon.otf");

	this->view = context->window->getDefaultView();

	this->buttonSize = 40;
	this->buttonPadding = 10;

	this->bottomMenuSize = { (this->buttonSize + this->buttonPadding) * 4, this->buttonSize };
	this->bottomMenuPos = {
		(context->window->getSize().x - this->bottomMenuSize.x) / 2,
		context->window->getSize().y - this->bottomMenuSize.y - 20
	};

	this->topMenuSize = { (this->buttonSize + this->buttonPadding) * 3, this->buttonSize / 2.0f };
	this->topMenuPos = {
		(context->window->getSize().x - this->topMenuSize.x) / 2,
		20
	};

	this->markMenuSize = { this->buttonSize * 1.5f + 2 * this->buttonPadding, this->buttonSize * 0.75f * 3 + 2 * this->buttonPadding };
	this->markMenuPos = {
		bottomMenuPos.x + 3 * (this->buttonSize + this->buttonPadding),
		bottomMenuPos.y - markMenuSize.y
	};

	initButtons(context);
	initClickListeners(context);
}

void StageInGameUI::initButtons(Context* context) {
	this->buttons.push_back(new Button(
		ID::ButtonMarkedNot,
		context->textures.get(Textures::BoardTileMarkedNot),
		{ this->bottomMenuPos.x + this->buttonPadding, this->bottomMenuPos.y },
		{ this->buttonSize, this->buttonSize }
	));
	this->buttons.push_back(new Button(
		ID::ButtonSelect,
		context->textures.get(Textures::BoardTileWin),
		{ this->bottomMenuPos.x + 2 * this->buttonPadding + this->buttonSize, this->bottomMenuPos.y },
		{ this->buttonSize, this->buttonSize }
	));
	this->buttons.push_back(new Button(
		ID::ButtonMarked,
		context->textures.get(Textures::BoardTileMarked),
		{ this->bottomMenuPos.x + 3 * this->buttonPadding + 2 * this->buttonSize, this->bottomMenuPos.y },
		{ this->buttonSize, this->buttonSize }
	));
	this->buttons.push_back(new Button(
		ID::ButtonMarkedExpand,
		context->textures.get(Textures::BoardTileMarkedExpand),
		{ this->bottomMenuPos.x + 4 * this->buttonPadding + 3 * this->buttonSize, this->bottomMenuPos.y },
		{ this->buttonSize, this->buttonSize }
	));
	this->buttons.push_back(new ButtonGroup(ID::ButtonGroupMarkMenu, {
		new Button(
			ID::ButtonMarkedToSelected,
			context->textures.get(Textures::ButtonMarkedToSelected),
			{ this->markMenuPos.x + this->buttonPadding, this->markMenuPos.y + this->buttonPadding },
			{ this->buttonSize * 1.5f, this->buttonSize * 0.75f }
		),
		new Button(
			ID::ButtonMarkedToNot,
			context->textures.get(Textures::ButtonMarkedToNot),
			{ this->markMenuPos.x + this->buttonPadding, this->markMenuPos.y + this->buttonSize * 0.75f + this->buttonPadding },
			{ this->buttonSize * 1.5f, this->buttonSize * 0.75f }
		),
		new Button(
			ID::ButtonMarkedToEmpty,
			context->textures.get(Textures::ButtonMarkedToEmpty),
			{ this->markMenuPos.x + this->buttonPadding, this->markMenuPos.y + 2 * this->buttonSize * 0.75f + this->buttonPadding },
			{ this->buttonSize * 1.5f, this->buttonSize * 0.75f }
		)
		}));
}

void StageInGameUI::initClickListeners(Context* context) {
	Actor* buttonGroup;
	for (auto& button : this->buttons) {
		button->setOnClickListener([&](Clickable* b, bool inside) {
			switch (b->getId()) {
			case ID::ButtonMarkedNot:
				this->board->setCurrentState(State::MarkedNot);
				break;
			case ID::ButtonSelect:
				this->board->setCurrentState(State::Selected);
				break;
			case ID::ButtonMarked:
				this->board->setCurrentState(State::Marked);
				break;
			case ID::ButtonMarkedToSelected:
				this->board->toggleMarked(State::Selected);
				break;
			case ID::ButtonMarkedToNot:
				this->board->toggleMarked(State::MarkedNot);
				break;
			case ID::ButtonMarkedToEmpty:
				this->board->toggleMarked(State::Empty);
				break;
			case ID::ButtonMarkedExpand:
				buttonGroup = findById(ID::ButtonGroupMarkMenu);
				buttonGroup->setVsibility(!buttonGroup->isVisible());
				this->markMenuShowed = buttonGroup->isVisible();
				break;
			default:
				if (!inside) {
					buttonGroup = findById(ID::ButtonGroupMarkMenu);
					buttonGroup->setVsibility(false);
					this->markMenuShowed = false;
				}
				break;
			}
		});
	}
}

void StageInGameUI::draw(Context* context) {
	context->window->setView(this->view);

	sf::Sprite sprite(context->textures.get(Textures::BottomMenu));
	sprite.setScale(this->bottomMenuSize.x / sprite.getTexture()->getSize().x, this->bottomMenuSize.y / sprite.getTexture()->getSize().y);
	sprite.setPosition(this->bottomMenuPos);
	context->window->draw(sprite);

	sprite.setScale(this->topMenuSize.x / sprite.getTexture()->getSize().x, this->topMenuSize.y / sprite.getTexture()->getSize().y);
	sprite.setPosition(this->topMenuPos);
	context->window->draw(sprite);

	sf::Vector2f pos(getButtonPosByState(this->board->getCurrentState()));
	sprite.setTexture(context->textures.get(Textures::Circle), true);
	sprite.setScale((this->buttonSize - this->buttonPadding) / sprite.getTexture()->getSize().x, (this->buttonSize - this->buttonPadding) / sprite.getTexture()->getSize().y);
	sprite.setPosition({ pos.x + this->buttonPadding / 2, pos.y + this->buttonPadding / 2 });
	context->window->draw(sprite);

	if (markMenuShowed) {
		sprite.setTexture(context->textures.get(Textures::MarkExpandMenu), true);
		sprite.setScale(this->markMenuSize.x / sprite.getLocalBounds().width, this->markMenuSize.y / sprite.getLocalBounds().height);
		sprite.setPosition(this->markMenuPos);
		context->window->draw(sprite);
	}

	for (auto& button : this->buttons) {
		button->draw(context);
	}

	sf::Text text(Utils::formatTime(this->board->getElapsedTime()), context->fonts.get(Fonts::Arcon), 15U);
	text.setPosition((context->window->getSize().x - text.getLocalBounds().width) / 2, 20);
	text.setFillColor(sf::Color(51, 51, 51));
	context->window->draw(text);
}

bool StageInGameUI::onEvent(Context* context, sf::Event event) {
	context->window->setView(this->view);

	for (auto& button : this->buttons) {
		if (button->onEvent(context, event)) {
			return true;
		}
	}

	sf::Vector2i pos = sf::Mouse::getPosition(*context->window);

	if (event.type == sf::Event::MouseButtonPressed ||
		event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		return pos.x >= bottomMenuPos.x && pos.x <= bottomMenuPos.x + bottomMenuSize.x &&
			pos.y >= bottomMenuPos.y && pos.y <= bottomMenuPos.y + bottomMenuSize.y;
	}
	return false;
}

void StageInGameUI::setBoard(Board* board) {
	this->board = board;
}

Actor* StageInGameUI::findById(int id) {
	for (auto& button : this->buttons) {
		if (button->getId() == id) {
			return button;
		}
	}
	return nullptr;
}

sf::Vector2f StageInGameUI::getButtonPosByState(State state) {
	for (auto& button : buttons) {
		if (button->getId() == ID::ButtonMarkedNot && state == State::MarkedNot) {
			return button->getPos();
		}
		if (button->getId() == ID::ButtonSelect && state == State::Selected) {
			return button->getPos();
		}
		if (button->getId() == ID::ButtonMarked && state == State::Marked) {
			return button->getPos();
		}
	}
	return sf::Vector2f();
}
