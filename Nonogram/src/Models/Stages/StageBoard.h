#pragma once
#include <SFML/Graphics.hpp>
#include "Stage.h"
#include "../Board.h"
#include "../../Utils/ResourceIdentifier.h"

class StageBoard : public Stage {
public:
	virtual void init(Context*) override;
	virtual void draw(Context*) override;
	virtual bool onEvent(Context*, sf::Event) override;

private:
	void drawBoard(Context*) const;
	void drawValues(Context*) const;
	bool isInRange(Context*) const;
	sf::Vector2i getSelectedTile(Context*) const;
	void markTile(sf::Vector2i) const;

private:
	float tileSize;
	Board* board;
	sf::Vector2f scale;
	sf::Vector2i padding;
	sf::Vector2i offset;
	sf::Vector2i startPos;
};