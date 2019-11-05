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

private:
	void drawValues(Context*) const;

private:
	float scale;
	float scaleAmount;
	float tileSize;
	bool isPanning;
	Board* board;
	sf::Vector2i tileMargin;
	sf::Vector2i boardPadding;
	sf::Vector2i boardOffset;
	sf::Vector2i startPos;
};