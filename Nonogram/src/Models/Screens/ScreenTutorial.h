#pragma once
#include <string>
#include "Screen.h"
#include "../Enums/Difficulty.h"
#include "../Stages/StageBackground.h"
#include "../Stages/StageBoard.h"
#include "../Stages/StageBoardValues.h"
#include "../Stages/StageInGameUI.h"
#include "../Stages/StageMessage.h"

class ScreenTutorial : public Screen {
public:
	virtual void load(Context*) override;

private:
	void resetBoardScale(Context*);

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
		"To complete Nonogram you\nhave to paint tiles in such\nway that the numbers\nmatch painted tiles count.",
		"Great! Now we will add\nanother row to increase\ndifficulty.",
		"If you see more than one\nnumber you have to split\npainted tiles as the numbers\nindicate.",
		"Another row will show how\nsplitting should look like in\nmore difficult scenario.",
		"Nice! If you want to set\nthe tile to be not paintable\njust click the right mouse button.",
		"Congratulations! You've solved\nyour first Nonogram.\nTap OK to continue."
	};
};