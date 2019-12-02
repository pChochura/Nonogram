#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "Stage.h"
#include "../Actors/Actor.h"
#include "../Enums/Difficulty.h"
#include "../../Utils/ResourceIdentifier.h"

////////////////////////////////////////////////////////////
//	Complete dialog
////////////////////////////////////////////////////////////
class StageComplete : public Stage {
public:
	////////////////////////////////////////////////////////////
	//	@inheritDoc
	////////////////////////////////////////////////////////////
	virtual void init(Context*) override;

	////////////////////////////////////////////////////////////
	//	@inheritDoc
	////////////////////////////////////////////////////////////
	virtual void draw(Context*) override;

	////////////////////////////////////////////////////////////
	//	@inheritDoc
	////////////////////////////////////////////////////////////
	virtual bool onEvent(Context*, sf::Event) override;

	////////////////////////////////////////////////////////////
	//	Setters
	////////////////////////////////////////////////////////////
	void setElapsedTime(sf::Time elapsedTime);
	void setDifficulty(Difficulty difficulty);
	void setOnPlayAgainClickListener(std::function<void(void)> onPlayAgainClickListener);
	void setOnExitClickListner(std::function<void(void)> onExitClickListener);

private:
	void initClickListeners(Context*);

private:
	std::function<void(void)> onPlayAgainClickListener;
	std::function<void(void)> onExitClickListener;
	sf::SoundBuffer tapSound;
	sf::Sound sound;
	sf::Time elapsedTime;
	Difficulty difficulty;
	sf::Vector2f winMenuSize;
	sf::Vector2f winMenuPos;
	std::vector<Actor*> buttons;

	enum ID {
		ButtonPlayAgain,
		ButtonExit
	};
};