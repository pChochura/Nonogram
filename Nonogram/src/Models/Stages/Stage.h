#pragma once
#include "../../Utils/ResourceIdentifier.h"

class Stage {
public:
	virtual void init(Context*) = 0;
	virtual void draw(Context*) = 0;
	virtual bool onEvent(Context*, sf::Event) = 0;
};