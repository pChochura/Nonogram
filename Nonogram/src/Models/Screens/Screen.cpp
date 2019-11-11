#include "../Screens/ScreenPlay.h"
#include "../../Utils/ResourceIdentifier.h"

void Screen::show(Context* context) const {
	for (auto& stage : this->stages) {
		stage->draw(context);
	}
}

void Screen::onEvent(Context* context, sf::Event event) const {
	for (auto i = this->stages.rbegin(); i < this->stages.rend(); i++) {
		if ((*i)->onEvent(context, event)) {
			return;
		}
	}
}

void Screen::setOnChangeScreenListener(std::function<void(Screen*)> onChangeScreenListener) {
	this->onChangeScreenListener = onChangeScreenListener;
}
