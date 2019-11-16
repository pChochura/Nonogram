#pragma once
#include "Screen.h"
#include "../Stages/StageInMenuUI.h"
#include "../Stages/StageBackground.h"
#include "../Stages/StageDifficultyMenu.h"

class ScreenMenu : public Screen {
public:
	virtual void load(Context*) override;

private:
	StageBackground stageBackground;
	StageDifficultyMenu stageDifficultyMenu;
	StageInMenuUI stageInMenuUI;
};