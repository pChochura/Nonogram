#include "Clickable.h"

void Clickable::setOnClickListener(std::function<void(Clickable*, bool)> onClickListener) {
	this->onClickListener = onClickListener;
}

int Clickable::getId() const {
	return this->id;
}
