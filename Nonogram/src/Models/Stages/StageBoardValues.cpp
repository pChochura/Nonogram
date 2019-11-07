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

	this->view = context->window->getDefaultView();
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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && isPanning) {
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

void StageBoardValues::drawValues(Context* context) const {
	sf::RectangleShape textBackground;
	textBackground.setFillColor(sf::Color(51, 51, 51, 51));

	sf::Text text("1", context->fonts.get(Fonts::Arcon), 18U);
	text.setFillColor(sf::Color(255, 255, 255));

	sf::Vector2f viewPos = this->view.getCenter() - this->view.getSize() / 2.0f;

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

	textBackground.setSize({ (this->board->tileSize + this->board->tileMargin.x) * this->board->width - this->board->tileMargin.x, maxVertical * (text.getLocalBounds().height + 14) });
	textBackground.setPosition({ 
		(float)this->board->offset.x,
		this->board->offset.y - textBackground.getSize().y - this->board->tileMargin.y + std::max(0.0f, viewPos.y - (this->board->offset.y - textBackground.getSize().y - this->board->tileMargin.y))
	});
	context->window->draw(textBackground);

	for (int i = 0; i < this->board->width; i++) {
		auto values = this->board->getVerticalValuesFor(i);
		int j = 0;
		for (auto it = values.rbegin(); it != values.rend(); it++, j++) {
			text.setString(std::to_string(*it));
			text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
			text.setPosition(
				i * (this->board->tileSize + this->board->tileMargin.x) + (this->board->tileSize + this->board->tileMargin.x) / 2.0f + this->board->offset.x,
				this->board->offset.y - (text.getLocalBounds().height + 10) * (j + 1) + std::max(0.0f, viewPos.y - (this->board->offset.y - (text.getLocalBounds().height + 10) * (maxVertical + 0.5f)))
			);
			context->window->draw(text);
		}
	}

	textBackground.setSize({ maxHorizontal * (text.getLocalBounds().height / 2 + 14), (this->board->tileSize + this->board->tileMargin.y) * this->board->height - this->board->tileMargin.y });
	textBackground.setPosition({ 
		this->board->offset.x - textBackground.getSize().x - this->board->tileMargin.x + std::max(0.0f, viewPos.x - (this->board->offset.x - textBackground.getSize().x - this->board->tileMargin.x)),
		(float)this->board->offset.y
	});
	context->window->draw(textBackground);

	for (int i = 0; i < this->board->height; i++) {
		auto values = this->board->getHorizontalValuesFor(i);
		int j = 0;
		for (auto it = values.rbegin(); it != values.rend(); it++, j++) {
			text.setString(std::to_string(*it));
			text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
			text.setPosition(
				this->board->offset.x - (text.getLocalBounds().height / 2 + 10) * (j + 1) + std::max(0.0f, viewPos.x - (this->board->offset.x - (text.getLocalBounds().height / 2 + 10) * (maxHorizontal + 0.5f))),
				i * (this->board->tileSize + this->board->tileMargin.y) + (this->board->tileSize + this->board->tileMargin.y) / 2.0f + this->board->offset.y
			);
			context->window->draw(text);
		}
	}
}