#pragma once
#include <vector>
#include <functional>
#include "../Stages/Stage.h"
#include "../../Utils/ResourceIdentifier.h"

////////////////////////////////////////////////////////////
//	Base class describing window screen
////////////////////////////////////////////////////////////
class Screen {
public:
	////////////////////////////////////////////////////////////
	//	It's called once to load all necessary resources
	////////////////////////////////////////////////////////////
	virtual void load(Context*) = 0;

	////////////////////////////////////////////////////////////
	//	It's called every frame and should contain only 
	//	drawing procedures
	////////////////////////////////////////////////////////////
	void show(Context*) const;

	////////////////////////////////////////////////////////////
	//	Method invoked when SFML event occured
	////////////////////////////////////////////////////////////
	void onEvent(Context*, sf::Event) const;

	////////////////////////////////////////////////////////////
	//	It's used to allow changing screen from another Screen 
	//	object. It should be invoked at once to work properly.
	////////////////////////////////////////////////////////////
	void setOnChangeScreenListener(std::function<void(Screen*)> onChangeScreenListener);

protected:
	std::vector<Stage*> stages;
	std::function<void(Screen*)> onChangeScreenListener;
};