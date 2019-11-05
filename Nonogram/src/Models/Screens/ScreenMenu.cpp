#include "ScreenMenu.h"

void ScreenMenu::load(Context* context) {
	this->stageBackground.init(context);
	this->stageDifficultyMenu.init(context);

	this->stages.push_back(&stageBackground);
	this->stages.push_back(&stageDifficultyMenu);
}