#pragma once
#include "Screen.h"
#include "../Enums/Difficulty.h"
#include "../Stages/StageBackground.h"
#include "../Stages/StageBoard.h"
#include "../Stages/StageBoardValues.h"
#include "../Stages/StageInGameUI.h"
#include "../Stages/StageComplete.h"

////////////////////////////////////////////////////////////
//	Play screen
////////////////////////////////////////////////////////////
class ScreenPlay : public Screen {
public:
	ScreenPlay(Difficulty diff);

	////////////////////////////////////////////////////////////
	//	@inheritDoc
	////////////////////////////////////////////////////////////
	virtual void load(Context*) override;

private:
	Difficulty difficulty;
	Board* board;

	StageBackground stageBackground;
	StageBoard stageBoard;
	StageBoardValues stageBoardValues;
	StageInGameUI stageInGameUI;
	StageComplete stageComplete;
};