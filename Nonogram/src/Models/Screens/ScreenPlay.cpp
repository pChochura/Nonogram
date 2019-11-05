#include "ScreenPlay.h"
#include "../../Utils/ResourceIdentifier.h"

void ScreenPlay::load(Context* context) {
	this->stageBackground.init(context);
	this->stageBoard.init(context);
	this->stageBoardValues.init(context);

	this->stages.push_back(&this->stageBackground);
	this->stages.push_back(&this->stageBoard);
	this->stages.push_back(&this->stageBoardValues);
}
