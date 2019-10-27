#pragma once
#include "Stage.h"
#include "../Board.h"
#include "../../Utils/ResourceIdentifier.h"

class StageBoard : public Stage {
public:
	virtual void init(Context*) override;
	virtual void draw(Context*) override;
	virtual bool mousePressedEvent(Context*, sf::Event) override;

private:
	void drawBoard(Context*) const;
	void drawValues(Context*) const;

private:
	float paddingHorizontal;
	float paddingVertical;
	float tileSize;
	Board* board;
};