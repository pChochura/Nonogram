#pragma once
#include "Screen.h"
#include "../Enums/Difficulty.h"
#include "../Stages/StageBackground.h"
#include "../Stages/StageBoard.h"
#include "../Stages/StageBoardValues.h"
#include "../Stages/StageInGameUI.h"

class ScreenPlay : public Screen {
public:
	virtual void load(Context*) override;
	ScreenPlay(Difficulty diff);

private:
	Difficulty difficulty;
	Board* board;

	StageBackground stageBackground;
	StageBoard stageBoard;
	StageBoardValues stageBoardValues;
	StageInGameUI stageInGameUI;
};