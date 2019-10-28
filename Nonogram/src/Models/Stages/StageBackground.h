#pragma once
#include "../Stages/Stage.h"
#include "../../Utils/ResourceIdentifier.h"

class StageBackground : public Stage {
public:
	virtual void init(Context*) override;
	virtual void draw(Context*) override;
	virtual bool onEvent(Context*, sf::Event) override;
};