#pragma once
#include <SFML/Graphics.hpp>
#include "Stage.h"
#include "../Board.h"
#include "../Actors/Button.h"
#include "../../Utils/ResourceIdentifier.h"

class StageInGameUI : public Stage {
public:
	virtual void init(Context*) override;
	virtual void draw(Context*) override;
	virtual bool onEvent(Context*, sf::Event) override;
	void setBoard(Board* board);
	sf::Vector2f getButtonPosByState(State state);

private:
	void initClickListeners(Context*);

private:
	Board* board;
	std::vector<Button*> buttons;
	sf::Vector2f bottomMenuSize;
	sf::Vector2f bottomMenuPos;
	float buttonSize;
	float buttonPadding;

	bool markMenuShowed = false;

	enum ID {
		ButtonMarked,
		ButtonMarkedNot,
		ButtonSelect,
		ButtonMarkedExpand
	};
};