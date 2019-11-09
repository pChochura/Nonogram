#include "Button.h"
#include "../Shapes/RoundedRectangleShape.h"

Button::Button(int id, std::string text, sf::Font textFont, float textSize, sf::Vector2f pos, sf::Vector2f padding, bool visibility) :
	text(text), textFont(textFont), textSize(textSize), padding(padding) {
	this->id = id;
	this->pos = pos;
	this->visible = visibility;
	sf::Text temp(text, textFont, textSize);
	this->size = { temp.getLocalBounds().width + padding.x * 2, temp.getLocalBounds().height + padding.y * 2 };
}

Button::Button(int id, sf::Texture texture, sf::Vector2f pos, sf::Vector2f size, bool visibility) :
	texture(texture) {
	this->id = id;
	this->pos = pos;
	this->size = size;
	this->visible = visibility;
}

Button::Button(int id) {
	this->id = id;
}

bool Button::onEvent(sf::Event event) {
	if (!this->visible) {
		return false;
	}
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		sf::Vector2i pos = { event.mouseButton.x, event.mouseButton.y };
		if (pos.x >= this->pos.x && pos.x <= this->pos.x + this->size.x &&
			pos.y >= this->pos.y && pos.y <= this->pos.y + this->size.y) {
			if (this->onClickListener != nullptr) {
				this->onClickListener(this, true);
			}
			return true;
		}
	}
	return false;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (!this->visible) {
		return;
	}

	if (this->textSize != -1) {
		sf::RoundedRectangleShape rect(this->size, 5, 50);
		rect.setFillColor(this->backgroundColor);
		rect.setPosition(this->pos);
		target.draw(rect, states);

		sf::Text text(this->text, this->textFont, this->textSize);
		text.setFillColor(this->textColor);
		text.setOrigin({ text.getLocalBounds().width / 2, text.getLocalBounds().height });
		text.setPosition(this->pos.x + this->size.x / 2, this->pos.y + this->size.y / 2);
		target.draw(text);
	} else {
		sf::Sprite sprite(this->texture);
		sprite.setPosition(this->pos);
		sprite.setScale(this->size.x / this->texture.getSize().x, this->size.y / this->texture.getSize().y);
		target.draw(sprite);
	}
}

void Button::setTextColor(sf::Color textColor) {
	this->textColor = textColor;
}

void Button::setBackgroundColor(sf::Color backgroundColor) {
	this->backgroundColor = backgroundColor;
}

void Button::setTexture(sf::Texture texture) {
	this->texture = texture;
}
