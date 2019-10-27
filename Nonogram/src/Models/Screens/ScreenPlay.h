#pragma once
#include "Screen.h"
#include "../Stages/StageBackground.h"
#include "../../Utils/ResourceIdentifier.h"

class ScreenPlay : public Screen {
public:
	virtual void load(Context*) override;

private:
	StageBackground stageBackground;
};