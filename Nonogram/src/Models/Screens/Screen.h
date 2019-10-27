#pragma once
#include <vector>
#include "../Stages/Stage.h"
#include "../../Utils/ResourceIdentifier.h"

class Screen {
public:
	virtual void load(Context*) = 0;
	void show(Context*) const;
	void mousePressedEvent(Context*, sf::Event) const;

protected:
	std::vector<Stage*> stages;
};