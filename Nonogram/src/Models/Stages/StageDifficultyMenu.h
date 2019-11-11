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
	std::vector<Button*> buttons;
	std::function<void(Difficulty)> onClickListener;

	enum ID {
		ButtonBabyStyle,
		ButtonDecent,
		ButtonImpresive,
		ButtonWorldClass
	};
};