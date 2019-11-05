#pragma once
#include <SFML/Graphics.hpp>
#include "Stage.h"
#include "../Actors/Button.h"
#include "../../Utils/ResourceIdentifier.h"

class StageDifficultyMenu : public Stage {
public:
	virtual void init(Context*) override;
	virtual void draw(Context*) override;
	virtual bool onEvent(Context*, sf::Event) override;

private:
	std::vector<Button*> buttons;
};