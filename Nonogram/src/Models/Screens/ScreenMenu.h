#pragma once
#include "Screen.h"
#include "../Stages/StageInMenuUI.h"
#include "../Stages/StageBackground.h"
#include "../Stages/StageDifficultyMenu.h"

////////////////////////////////////////////////////////////
//	Menu screen
////////////////////////////////////////////////////////////
class ScreenMenu : public Screen {
public:
	////////////////////////////////////////////////////////////
	//	@inheritDoc
	////////////////////////////////////////////////////////////
	virtual void load(Context*) override;

private:
	StageBackground stageBackground;
	StageDifficultyMenu stageDifficultyMenu;
	StageInMenuUI stageInMenuUI;
};