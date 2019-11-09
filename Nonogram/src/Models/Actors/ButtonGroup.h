#pragma once
#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Button.h"

class ButtonGroup : public Actor {
public:
	ButtonGroup(int id, std::vector<Button*> buttons);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual bool onEvent(sf::Event) override;

private:
	std::vector<Button*> buttons;
};