#pragma once
#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Button.h"

class ButtonGroup : public Actor {
public:
	ButtonGroup(int id, std::vector<Button*> buttons);
	virtual bool onEvent(Context* context, sf::Event) override;
	virtual void draw(Context* context) const override;

private:
	std::vector<Button*> buttons;
};