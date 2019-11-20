#include "ScreenMenu.h"
#include "ScreenTutorial.h"
#include "ScreenPlay.h"

void ScreenMenu::load(Context* context) {
	this->stageBackground.init(context);
	this->stageDifficultyMenu.init(context);
	this->stageInMenuUI.init(context);

	this->stages.push_back(&stageBackground);
	this->stages.push_back(&stageDifficultyMenu);
	this->stages.push_back(&stageInMenuUI);

	stageDifficultyMenu.setOnClickListener([&](Difficulty diff) {
		if (diff == Difficulty::Tutorial) {
			this->onChangeScreenListener(new ScreenTutorial);
		} else {
			this->onChangeScreenListener(new ScreenPlay(diff));
		}
	});
}