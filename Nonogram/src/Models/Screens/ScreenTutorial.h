#pragma once
#include <string>
#include "Screen.h"
#include "../Enums/Difficulty.h"
#include "../Stages/StageBackground.h"
#include "../Stages/StageBoard.h"
#include "../Stages/StageBoardValues.h"
#include "../Stages/StageInGameUI.h"
#include "../Stages/StageMessage.h"

////////////////////////////////////////////////////////////
//	Tutorial screen
////////////////////////////////////////////////////////////
class ScreenTutorial : public Screen {
public:
	////////////////////////////////////////////////////////////
	//	@inheritDoc
	////////////////////////////////////////////////////////////
	virtual void load(Context*) override;

private:
	Board* board;

	StageBackground stageBackground;
	StageBoard stageBoard;
	StageBoardValues stageBoardValues;
	StageInGameUI stageInGameUI;
	StageMessage stageMessage;

	int currentLevel;
	static const int maxLevels = 5;
	std::string levels[maxLevels] = {
		"5 1 11111",
		"5 2 2222211110",
		"5 3 222222222011011",
		"5 4 22222222202202210111",
		"5 5 2222222220220222022200100"
	};
	std::string messages[maxLevels + 1] = {
		"To complete Nonogram you have to paint tiles in such way that the numbers match painted tiles count.",
		"Great! Now we will add another row to increase difficulty.",
		"If you see more than one number you have to split painted tiles as the numbers indicate.",
		"Another row will show how splitting should look like in more difficult scenario.",
		"Nice! If you want to set the tile to be not paintable just click the right mouse button.",
		"Congratulations! You've solved your first Nonogram.\nTap OK to continue."
	};
};