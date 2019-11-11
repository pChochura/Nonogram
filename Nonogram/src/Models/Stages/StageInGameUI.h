#pragma once
#include <SFML/Graphics.hpp>
#include "Stage.h"
#include "../Board.h"
#include "../Actors/Actor.h"
#include "../../Utils/ResourceIdentifier.h"

class StageInGameUI : public Stage {
public:
	virtual void init(Context*) override;
	virtual void draw(Context*) override;
	virtual bool onEvent(Context*, sf::Event) override;
	void setBoard(Board* board);
	Actor* findById(int id);
	sf::Vector2f getButtonPosByState(State state);

private:
	void initButtons(Context*);
	void initClickListeners(Context*);

private:
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
		ButtonMarked = 1,
		ButtonMarkedNot = 2,
		ButtonSelect = 4,
		ButtonMarkedExpand = 8,
		ButtonMarkedToSelected = 16,
		ButtonMarkedToNot = 32,
		ButtonMarkedToEmpty = 64,
		ButtonGroupMarkMenu = 128
	};
};