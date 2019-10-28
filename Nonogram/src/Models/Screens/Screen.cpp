#include "../Screens/ScreenPlay.h"
#include "../../Utils/ResourceIdentifier.h"

void Screen::show(Context* context) const {
	for (auto& stage : this->stages) {
		stage->draw(context);
	}
}

void Screen::onEvent(Context* context, sf::Event event) const {
	for (auto& stage : this->stages) {
		if (stage->onEvent(context, event)) {
			return;
		}
	}
}