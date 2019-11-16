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
	void setBoard(Board* board);

private:
	void drawBoard(Context*) const;
	bool isInRange(Context*) const;
	void markTile(sf::Vector2i);
	sf::Vector2i getSelectedTile(Context*) const;

private:
	sf::SoundBuffer tapSound;
	sf::Sound sound;
	Board* board;
	bool isPanning; //Indicates that the user is moving the view
	bool isSwiping; //Indicates that the user is selecting by swiping
	bool isUndoingSelection; //Indicates that the user started to swiping on the selected tile and want to unselect it
	sf::Vector2f startPos;
};