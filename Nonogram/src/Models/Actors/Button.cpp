#include "Button.h"
#include <iostream>
#include "../Drawables/RoundedRectangleShape.h"

Button::Button(int id, sf::Vector2f size) : hasBackgroundColor(false), hasTexture(false) {
	this->id = id;
	this->size = size;
	this->visible = true;
}

bool Button::isHovering(Context* context) const {
	sf::Vector2i pos = sf::Mouse::getPosition(*context->window);
	if (pos.x >= this->pos.x && pos.x <= this->pos.x + this->size.x &&
		pos.y >= this->pos.y && pos.y <= this->pos.y + this->size.y) {
		return true;
	}
	return false;
}

bool Button::onEvent(Context* context, sf::Event event) {
	if (!this->visible) {
		return false;
	}
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		if (isHovering(context)) {
			if (this->onClickListener != nullptr) {
				this->onClickListener(this, true);
			}
			return true;
		}
	}
	return false;
}

void Button::draw(Context* context) const {
	if (!this->visible) {
		return;
	}

	if (this->hasBackgroundColor) {
		sf::Color maskColor = isHovering(context) ? sf::Color(200, 200, 200) : sf::Color::White;

		sf::RoundedRectangleShape rect(this->size, 5, 50);
		rect.setFillColor(this->backgroundColor * maskColor);
		rect.setPosition(this->pos);
		context->window->draw(rect);
	}

	if (this->hasTexture) {
		sf::Color maskColor = isHovering(context) ? sf::Color(200, 200, 200) : sf::Color::White;

		sf::Sprite sprite(this->texture);
		sprite.setPosition(this->pos);
		sprite.setColor(maskColor);
		sprite.setScale(this->size.x / this->texture.getSize().x, this->size.y / this->texture.getSize().y);
		context->window->draw(sprite);
	}

	if (this->text.length() != 0) {
		sf::Text text(this->text, this->textFont, (unsigned int) this->textSize);
		text.setFillColor(this->textColor);
		text.setPosition(this->pos.x + this->size.x / 2.0f - text.getLocalBounds().width / 2.0f, this->pos.y + this->size.y / 2.0f - text.getLocalBounds().height);
		context->window->draw(text);
	}
}

void Button::calculateSize() {
	sf::Text text(this->text, this->textFont, (unsigned int)this->textSize);
	if (this->text.length() != 0) {
		if (this->size.x == ButtonSize::WrapContent) {
			this->size.x = text.getLocalBounds().width + this->padding.x;
		}
		if (this->size.y == ButtonSize::WrapContent) {
			this->size.y = text.getLocalBounds().height + this->padding.y;
		}
	}
}

Button* Button::withTexture(sf::Texture texture) {
	this->texture = texture;
	this->hasTexture = true;
	return this;
}

Button* Button::withPadding(sf::Vector2f padding) {
	this->padding = padding;
	return this;
}

Button* Button::withText(std::string text) {
	this->text = text;
	return this;
}

Button* Button::withTextSize(float textSize) {
	this->textSize = textSize;
	return this;
}

Button* Button::withTextColor(sf::Color textColor) {
	this->textColor = textColor;
	return this;
}

Button* Button::withTextFont(sf::Font textFont) {
	this->textFont = textFont;
	return this;
}

Button* Button::withBackgroundColor(sf::Color backgroundColor) {
	this->backgroundColor = backgroundColor;
	this->hasBackgroundColor = true;
	return this;
}

Button* Button::withPosition(sf::Vector2f position) {
	this->pos = position;
	return this;
}

Button* Button::build() {
	if (this->size.x == ButtonSize::WrapContent || this->size.y == ButtonSize::WrapContent) {
		this->calculateSize();
	}
	return this;
}