#include <SFML/Graphics.hpp>
#include <math.h>
#include "ButtonGroup.h"
#include "Button.h"

ButtonGroup::ButtonGroup(int id, std::vector<Button*> buttons) :
	buttons(buttons) {
	this->id = id;

	float leftMost = FLT_MAX;
	float topMost = FLT_MAX;
	float rightMost = FLT_MIN;
	float bottomMost = FLT_MIN;

	for (auto& button : buttons) {
		leftMost = std::min(leftMost, button->getPos().x);
		topMost = std::min(topMost, button->getPos().y);
		rightMost = std::max(rightMost, button->getPos().x + button->getSize().x);
		bottomMost = std::max(bottomMost, button->getPos().y + button->getSize().y);
	}

	this->pos = { leftMost, topMost };
	this->size = { rightMost - leftMost, bottomMost - topMost };
}

void ButtonGroup::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (!this->visible) {
		return;
	}

	for (auto& button : this->buttons) {
		button->draw(target, states);
	}
}

bool ButtonGroup::onEvent(sf::Event event) {
	if (!this->visible) {
		return false;
	}
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		sf::Vector2i pos = { event.mouseButton.x, event.mouseButton.y };
		if (pos.x >= this->pos.x && pos.x <= this->pos.x + this->size.x &&
			pos.y >= this->pos.y && pos.y <= this->pos.y + this->size.y) {
			for (auto& button : this->buttons) {
				if (button->onEvent(event)) {
					if (this->onClickListener != nullptr) {
						this->onClickListener(button, true);
					}
					return true;
				}
			}
			if (this->onClickListener != nullptr) {
				this->onClickListener(&Button::EMPTY(), true);
			}
			return true;
		} else {
			if (this->onClickListener != nullptr) {
				this->onClickListener(&Button::EMPTY(), false);
			}
			return true;
		}
	}
	return false;
}