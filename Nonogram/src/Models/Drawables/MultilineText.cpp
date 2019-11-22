#include "MultilineText.h"
#include "../Enums/Align.h"
#include "../../Utils/Utils.h"

MultilineText::MultilineText()
	: string(string), font(font), characterSize(characterSize), verticalSpacingMultiplier(1.2f), lineSize(0.0f), alignement(Align::LEFT) {}

MultilineText::MultilineText(const std::string& string, const sf::Font& font, unsigned int characterSize)
	: string(string), font(font), characterSize(characterSize), verticalSpacingMultiplier(1.2f), lineSize(0.0f), alignement(Align::LEFT) {
	recalculateTexts();
}

void MultilineText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto text : this->texts) {
		target.draw(*text, states);
	}
}

void MultilineText::setString(std::string string) {
	this->string = string;
	recalculateTexts();
	recalculatePosition();
}

void MultilineText::setFillColor(sf::Color fillColor) {
	this->fillColor = fillColor;
}

void MultilineText::setPosition(sf::Vector2f position) {
	this->position = position;
	recalculatePosition();
}

void MultilineText::setVerticalSpacingMultiplier(float multiplier) {
	this->verticalSpacingMultiplier = multiplier;
	recalculatePosition();
}

void MultilineText::setAlignement(Align alignement) {
	this->alignement = alignement;
}

void MultilineText::setMaxSize(float maxWidth) {
	this->maxWidth = maxWidth;
	recalculateTexts();
}

void MultilineText::recalculatePosition() {
	int index = 0;
	for (auto text : this->texts) {
		float x = this->position.x;
		if (this->alignement == Align::CENTER) {
			x = this->position.x + (getLocalBounds().width - text->getLocalBounds().width) / 2.0f;
		} else if (this->alignement == Align::RIGHT) {
			x = this->position.x + getLocalBounds().width - text->getLocalBounds().width;
		}
		text->setPosition({
			x,
			this->position.y + this->lineSize * this->verticalSpacingMultiplier * index++
		});
	}
}

void MultilineText::recalculateTexts() {
	this->texts.clear();

	if (this->string.empty()) {
		return;
	}

	if (this->maxWidth > 0) {
		splitInput();
	}

	auto strings = Utils::split(this->string, "\n");
	for (auto string : strings) {
		sf::Text* text = new sf::Text(string, this->font, this->characterSize);
		text->setFillColor(this->fillColor);
		this->texts.push_back(text);
		this->lineSize = std::max(this->lineSize, text->getLocalBounds().height);
	}
}

void MultilineText::splitInput() {
	sf::Text temp(this->string, this->font, this->characterSize);

	int offset = this->string.length() - 1;
	while (temp.getLocalBounds().width > this->maxWidth || this->string[offset] != ' ') {
		temp.setString(this->string.substr(0, offset--));
	}
	this->string[offset] = '\n';

	temp.setString(this->string);
	if (temp.getLocalBounds().width > this->maxWidth) {
		splitInput();
	}
}

sf::FloatRect MultilineText::getLocalBounds() {
	sf::FloatRect rect(this->texts.front()->getLocalBounds());
	for (auto text : this->texts) {
		rect.left = std::min(rect.left, text->getPosition().x);
		rect.top = std::min(rect.top, text->getPosition().y);
		rect.width = std::max(rect.width, text->getLocalBounds().width);
		rect.height = std::max(rect.height, text->getLocalBounds().height);
	}
	return rect;
}
