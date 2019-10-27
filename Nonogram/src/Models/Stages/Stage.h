#pragma once
#include "../../Utils/ResourceIdentifier.h"

class Stage {
public:
	virtual void draw(Context*) = 0;
};