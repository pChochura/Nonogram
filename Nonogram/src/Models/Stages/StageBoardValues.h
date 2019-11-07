#pragma once
#include <SFML/Graphics.hpp>
#include "Stage.h"
#include "../Board.h"
#include "../../Utils/ResourceIdentifier.h"

class StageBoardValues : public Stage {
public:
	virtual void init(Context*) override;
	virtual void draw(Context*) override;
	virtual bool onEvent(Context*, sf::Event) override;
	void setBoard(Board* board);

private:
	void drawValues(Context*) const;

private:
	Board* board;
	bool isPanning;
	sf::Vector2i startPos;
};