#pragma once
#include "Screen.h"
#include "../Stages/StageBackground.h"
#include "../Stages/StageBoard.h"
#include "../Stages/StageBoardValues.h"

class ScreenPlay : public Screen {
public:
	virtual void load(Context*) override;

private:
	StageBackground stageBackground;
	StageBoard stageBoard;
	StageBoardValues stageBoardValues;
};