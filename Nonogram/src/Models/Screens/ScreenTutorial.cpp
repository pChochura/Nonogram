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
			this->board->set(context, this->levels[this->currentLevel]);
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

	this->board->resetBoardScale(context);

	this->stageBoard.setBoard(this->board);
	this->stageBoardValues.setBoard(this->board);
	this->stageInGameUI.setBoard(this->board);

	//Settings the same view to the stageBoard and stageBoardValues to synchronise all the movement
	sf::View view = context->window->getDefaultView();
	view.zoom(1.5f);
	this->stageBoard.setView(view);
	this->stageBoardValues.setView(view);
}