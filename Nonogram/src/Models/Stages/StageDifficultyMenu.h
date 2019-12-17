#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "Stage.h"
#include "../Actors/Button.h"
#include "../Enums/Difficulty.h"
#include "../../Utils/ResourceIdentifier.h"

class StageDifficultyMenu : public Stage {
public:
	virtual void init(Context*) override;
	virtual void draw(Context*) override;
	virtual bool onEvent(Context*, sf::Event) override;
	void setOnClickListener(std::function<void(Difficulty)> onClickListener);

private:
	void initClickListeners(Context*);

private:
	sf::SoundBuffer tapSound;
	sf::Sound sound;
	sf::Vector2f difficultyMenuSize;
	sf::Vector2f difficultyMenuPos;
	std::vector<Button*> buttons;
	std::function<void(Difficulty)> onClickListener;

	enum ID {
		ButtonTutorial		= (1 << 0),
		ButtonBabyStyle		= (1 << 1),
		ButtonDecent		= (1 << 2),
		ButtonImpresive		= (1 << 3),
		ButtonWorldClass	= (1 << 4),
		ButtonFromFile		= (1 << 5)
	};
};