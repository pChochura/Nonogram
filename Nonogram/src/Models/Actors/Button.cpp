#include "Button.h"
#include "../Shapes/RoundedRectangleShape.h"

Button::Button(std::string text, sf::Font textFont, float textSize, sf::Vector2f pos, sf::Vector2f padding) : 
	text(text), textFont(textFont), textSize(textSize), padding(padding) {
	this->pos = pos;
	sf::Text temp(text, textFont, textSize);
	this->size = { temp.getLocalBounds().width + padding.x * 2, temp.getLocalBounds().height + padding.y * 2 };
}

void Button::setOnClickListener(std::function<void(void)> onClickListener) {
	this->onClickListener = onClickListener;
}

void Button::onEvent(sf::Event* event) {

}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::RoundedRectangleShape rect(this->size, 5, 50);
	rect.setFillColor(this->backgroundColor);
	rect.setPosition(this->pos);
	target.draw(rect, states);

	sf::Text text(this->text, this->textFont, this->textSize);
	text.setFillColor(this->textColor);
	text.setOrigin({ text.getLocalBounds().width / 2, text.getLocalBounds().height });
	text.setPosition(this->pos.x + this->size.x / 2, this->pos.y + this->size.y / 2);
	target.draw(text);
}

void Button::setTextColor(sf::Color textColor) {
	this->textColor = textColor;
}

void Button::setBackgroundColor(sf::Color backgroundColor) {
	this->backgroundColor = backgroundColor;
}
