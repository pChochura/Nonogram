#include "ScreenPlay.h"
#include "../../Utils/Utils.h"
#include "../../Utils/ResourceIdentifier.h"

void ScreenPlay::load(Context* context) {
	this->stageBackground.init(context);
	this->stageBoard.init(context);
	this->stageBoardValues.init(context);
	this->stageInGameUI.init(context);

	this->stages.push_back(&this->stageBackground);
	this->stages.push_back(&this->stageBoard);
	this->stages.push_back(&this->stageBoardValues);
	this->stages.push_back(&this->stageInGameUI);

	this->board = new Board;

	this->board->random(Difficulty::WorldClass);

	auto windowSize = context->window->getSize();

	float width = (float)(windowSize.x - this->board->padding.x) / this->board->width;
	float height = (float)(windowSize.y - this->board->padding.y) / this->board->height;

	this->board->tileSize = std::min(width, height);
	this->board->scaleAmount = 1.1f;
	this->board->scale = 1.0f;

	this->board->padding = { 150, 200 };
	this->board->tileMargin = { (int)(this->board->tileSize / 20), (int)(this->board->tileSize / 20) };

	this->board->offset.x = (int)(windowSize.x - this->board->width * this->board->tileSize + this->board->padding.x / 2) / 2;
	this->board->offset.y = (int)(windowSize.y - this->board->height * this->board->tileSize + this->board->padding.y / 2) / 2;

	this->stageBoard.setBoard(this->board);
	this->stageBoardValues.setBoard(this->board);
	this->stageInGameUI.setBoard(this->board);

	//Settings the same view to the stageBoard and stageBoardValues to synchronise all the movement
	sf::View view = context->window->getDefaultView();
	this->stageBoard.setView(view);
	this->stageBoardValues.setView(view);
}