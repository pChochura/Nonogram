#pragma once
#include "Screen.h"
#include "StageBackground.h"

class ScreenPlay : public Screen {
public:
	ScreenPlay();

private:
	StageBackground stageBackground;
};