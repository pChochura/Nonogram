#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "../Board.h"
#include "../Enums/Difficulty.h"
#include "../Stages/StageBoardValues.h"
#include "../../Utils/Utils.h"
#include "../../Utils/ResourceIdentifier.h"

void StageBoardValues::init(Context* context) {
	context->fonts.load(Fonts::Arcon, "data/Fonts/Arcon.otf");
}

void StageBoardValues::setBoard(Board* board) {
	this->board = board;
}

void StageBoardValues::draw(Context* context) {
	context->window->setView(this->view);

	drawValues(context);
}

bool StageBoardValues::onEvent(Context* context, sf::Event event) {
	context->window->setView(this->view);

	switch (event.type) {
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Middle) {
			this->startPos = context->window->mapPixelToCoords(sf::Mouse::getPosition(*context->window));
			this->isPanning = true;
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (event.mouseButton.button == sf::Mouse::Middle) {
			this->isPanning = false;
		}
		break;
	case sf::Event::MouseMoved:
		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && isPanning) {
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

void StageBoardValues::drawValues(Context* context) const {
	sf::RectangleShape textBackground;
	textBackground.setFillColor(sf::Color(51, 51, 51, 51));

	sf::Color completeColor = sf::Color(150, 150, 150);
	sf::Color incompleteColor = sf::Color(255, 255, 255);

	sf::Text text("1", context->fonts.get(Fonts::Arcon), (unsigned int) (this->board->tileSize / 2));
	text.setFillColor(incompleteColor);

	sf::Vector2f viewPos = this->view.getCenter() - this->view.getSize() / 2.0f;

	std::vector<int> values;
	std::vector<bool> isValuesComplete;

	int maxVertical = 0;
	int maxHorizontal = 0;

	for (int i = 0; i < this->board->width || i < this->board->height; i++) {
		if (i < this->board->width) {
			auto valuesVertical = this->board->getVerticalValuesFor(i);
			maxVertical = std::max(maxVertical, (int) valuesVertical.size());
		}
		if (i < this->board->height) {
			auto valuesHorizontal = this->board->getHorizontalValuesFor(i);
			maxHorizontal = std::max(maxHorizontal, (int) valuesHorizontal.size());
		}
	}

	textBackground.setSize({ (this->board->tileSize + this->board->tileMargin.x) * this->board->width - this->board->tileMargin.x, maxVertical * this->board->tileSize / 2.0f });
	textBackground.setPosition({ 
		(float)this->board->offset.x,
		this->board->offset.y - textBackground.getSize().y - this->board->tileMargin.y + std::max(0.0f, viewPos.y - (this->board->offset.y - textBackground.getSize().y - this->board->tileMargin.y))
	});
	context->window->draw(textBackground);

	for (int i = 0; i < this->board->width; i++) {
		values = this->board->getVerticalValuesFor(i);
		int j = 0;
		isValuesComplete = this->board->isVerticalValuesCompleteFor(i);
		for (auto it = values.rbegin(); it != values.rend(); it++, j++) {
			text.setFillColor(isValuesComplete[values.size() - j - 1] ? completeColor : incompleteColor);
			text.setString(std::to_string(*it));
			text.setPosition(
				i * (this->board->tileSize + this->board->tileMargin.x) + (this->board->tileSize + this->board->tileMargin.x - text.getLocalBounds().width) / 2.0f + this->board->offset.x,
				this->board->offset.y - this->board->tileSize / 2.0f * (j + 1.25f) + std::max(0.0f, viewPos.y - (this->board->offset.y - this->board->tileSize / 2.0f * maxVertical - this->board->tileMargin.y))
			);
			context->window->draw(text);
		}
	}

	textBackground.setSize({ maxHorizontal * this->board->tileSize / 2.5f, (this->board->tileSize + this->board->tileMargin.y) * this->board->height - this->board->tileMargin.y });
	textBackground.setPosition({ 
		this->board->offset.x - textBackground.getSize().x - this->board->tileMargin.x + std::max(0.0f, viewPos.x - (this->board->offset.x - textBackground.getSize().x - this->board->tileMargin.x)),
		(float)this->board->offset.y
	});
	context->window->draw(textBackground);

	for (int i = 0; i < this->board->height; i++) {
		values = this->board->getHorizontalValuesFor(i);
		int j = 0;
		isValuesComplete = this->board->isHorizontalValuesCompleteFor(i);
		for (auto it = values.rbegin(); it != values.rend(); it++, j++) {
			text.setFillColor(isValuesComplete[values.size() - j - 1] ? completeColor : incompleteColor);
			text.setOrigin(this->board->tileSize / 5.0f, 0.0f);
			text.setString(std::to_string(*it));
			text.setPosition(
				this->board->offset.x - this->board->tileSize / 2.5f * (j + 0.25f) - text.getLocalBounds().width / 2.0f + std::max(0.0f, viewPos.x - (this->board->offset.x - this->board->tileSize / 2.5f * maxHorizontal - this->board->tileMargin.x)),
				i * (this->board->tileSize + this->board->tileMargin.y) + (this->board->tileSize + this->board->tileMargin.y - this->board->tileSize / 2.0f) / 2.0f + this->board->offset.y
			);
			context->window->draw(text);
		}
	}
}