#pragma once
#include <SFML/Graphics.hpp>
#include "Stage.h"
#include "../Actors/Actor.h"
#include "../../Utils/ResourceIdentifier.h"

class StageInMenuUI : public Stage {
public:
	virtual void init(Context*) override;
	virtual void draw(Context*) override;
	virtual bool onEvent(Context*, sf::Event) override;

private:
	void initClickListeners(Context*);

private:
	sf::SoundBuffer tapSound;
	sf::Sound sound;
	std::vector<Actor*> buttons;

	enum ID {
		ButtonExit = (1 << 0)
	};
};