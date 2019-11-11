#pragma once
#include <vector>
#include <functional>
#include "../Stages/Stage.h"
#include "../../Utils/ResourceIdentifier.h"

class Screen {
public:
	virtual void load(Context*) = 0;
	void show(Context*) const;
	void onEvent(Context*, sf::Event) const;
	void setOnChangeScreenListener(std::function<void(Screen*)> onChangeScreenListener);

protected:
	std::vector<Stage*> stages;
	std::function<void(Screen*)> onChangeScreenListener;
};