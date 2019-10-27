#include "../Screens/ScreenPlay.h"
#include "../../Utils/ResourceIdentifier.h"

void Screen::show(Context* context) const {
	for (auto& stage : this->stages) {
		stage->draw(context);
	}
}