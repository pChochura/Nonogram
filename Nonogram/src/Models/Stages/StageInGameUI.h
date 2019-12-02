#pragma once
#include <SFML/Graphics.hpp>
#include "Stage.h"
#include "../Board.h"
#include "../Actors/Actor.h"
#include "../../Utils/ResourceIdentifier.h"

////////////////////////////////////////////////////////////
//	User interface displayed in game
////////////////////////////////////////////////////////////
class StageInGameUI : public Stage {
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
	//	Setters and getters
	////////////////////////////////////////////////////////////
	void setBoard(Board* board);
	Actor* findById(int id);
	sf::Vector2f getButtonPosByState(State state);

private:
	void initButtons(Context*);
	void initClickListeners(Context*);

private:
	sf::SoundBuffer tapSound;
	sf::Sound sound;
	Board* board;
	std::vector<Actor*> buttons;
	sf::Vector2f bottomMenuSize;
	sf::Vector2f bottomMenuPos;
	sf::Vector2f topMenuPos;
	sf::Vector2f topMenuSize;
	sf::Vector2f markMenuSize;
	sf::Vector2f markMenuPos;
	float buttonSize;
	float buttonPadding;

	bool markMenuShowed = false;

	enum ID {
		ButtonMarked			= (1 << 0),
		ButtonMarkedNot			= (1 << 1),
		ButtonSelect			= (1 << 2),
		ButtonMarkedExpand		= (1 << 3),
		ButtonMarkedToSelected	= (1 << 4),
		ButtonMarkedToNot		= (1 << 5),
		ButtonMarkedToEmpty		= (1 << 6),
		ButtonGroupMarkMenu		= (1 << 7)
	};
};