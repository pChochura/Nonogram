#include "ScreenPlay.h"
#include "StageBackground.h"

ScreenPlay::ScreenPlay() {
	this->stages.push_back(&(this->stageBackground));
}