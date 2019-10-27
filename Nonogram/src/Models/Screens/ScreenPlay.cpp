#include "ScreenPlay.h"
#include "../../Utils/ResourceIdentifier.h"

void ScreenPlay::load(Context* context) {
	this->stageBackground.load(context);
	this->stages.push_back(&this->stageBackground);
}
