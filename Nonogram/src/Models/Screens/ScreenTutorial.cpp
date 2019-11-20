#include "ScreenTutorial.h"
#include "ScreenPlay.h"
#include "../Enums/Difficulty.h"

void ScreenTutorial::load(Context* context) {
	this->stageBackground.init(context);
	this->stageBoard.init(context);
	this->stageBoardValues.init(context);
	this->stageInGameUI.init(context);
	this->stageMessage.init(context);

	this->stages.push_back(&this->stageBackground);
	this->stages.push_back(&this->stageBoard);
	this->stages.push_back(&this->stageBoardValues);
	this->stages.push_back(&this->stageInGameUI);
	this->stages.push_back(&this->stageMessage);

	this->stageMessage.setMessage(this->messages[this->currentLevel]);

	this->stageMessage.setOnOkClickListner([&, context]() {
		this->currentLevel++;
		if (this->currentLevel < this->maxLevels) {
			this->stages.pop_back();
			this->board->set(this->levels[this->currentLevel]);
			resetBoardScale(context);
		} else {
			onChangeScreenListener(new ScreenPlay(Difficulty::BabyStyle));
		}
	});

	this->board = new Board;

	this->board->setOnStopTimerListener([&]() {
		if (this->currentLevel < this->maxLevels) {
			this->stageMessage.setMessage(this->messages[this->currentLevel + 1]);
			this->stages.push_back(&this->stageMessage);
		}
	});

	this->currentLevel = -1;

	this->board->padding = { 150, 200 };

	resetBoardScale(context);

	this->stageBoard.setBoard(this->board);
	this->stageBoardValues.setBoard(this->board);
	this->stageInGameUI.setBoard(this->board);

	//Settings the same view to the stageBoard and stageBoardValues to synchronise all the movement
	sf::View view = context->window->getDefaultView();
	view.zoom(1.5f);
	this->stageBoard.setView(view);
	this->stageBoardValues.setView(view);
}

void ScreenTutorial::resetBoardScale(Context* context) {
	auto windowSize = context->window->getSize();

	float width = (float)(windowSize.x - this->board->padding.x) / this->board->width;
	float height = (float)(windowSize.y - this->board->padding.y) / this->board->height;

	this->board->scaleAmount = 1.1f;
	this->board->scale = 1.5f;

	this->board->tileSize = std::min(width, height);
	this->board->tileMargin = { (int)(this->board->tileSize / 20), (int)(this->board->tileSize / 20) };
	this->board->offset.x = (int)(windowSize.x - this->board->width * this->board->tileSize + this->board->padding.x / 2) / 2;
	this->board->offset.y = (int)(windowSize.y - this->board->height * this->board->tileSize + this->board->padding.y / 2) / 2;
}