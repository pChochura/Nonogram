#include "ScreenMenu.h"
#include "ScreenPlay.h"

void ScreenMenu::load(Context* context) {
	this->stageBackground.init(context);
	this->stageDifficultyMenu.init(context);
	this->stageInMenuUI.init(context);

	this->stages.push_back(&stageBackground);
	this->stages.push_back(&stageDifficultyMenu);
	this->stages.push_back(&stageInMenuUI);

	stageDifficultyMenu.setOnClickListener([&](Difficulty diff) {
		this->onChangeScreenListener(new ScreenPlay(diff));
	});
}