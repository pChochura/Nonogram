#pragma once
#include "../Stages/Stage.h"
#include "../../Utils/ResourceIdentifier.h"

class StageBackground : public Stage {
public:
	void load(Context*);
	virtual void draw(Context*) override;
};