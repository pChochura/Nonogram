#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceIdentifier.h"

namespace Utils {
	inline void moveView(Context* context, sf::View* view, sf::Vector2f translation) {
		view->move(translation);
		context->window->setView(*view);
	}

	inline void scaleView(Context* context, sf::View* view, float scaleFactor, sf::Vector2i origin = { 0, 0 }) {
		const sf::Vector2f beforeCoord{ context->window->mapPixelToCoords(origin) };
		view->zoom(scaleFactor);
		context->window->setView(*view);
		const sf::Vector2f afterCoord{ context->window->mapPixelToCoords(origin) };
		const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
		view->move(offsetCoords);
		context->window->setView(*view);
	}

	template<typename Base, typename T>
	inline bool instanceof(const T* ptr) {
		return dynamic_cast<const Base*>(ptr) != nullptr;
	}
}