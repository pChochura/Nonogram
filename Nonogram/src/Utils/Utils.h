#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <cstdarg>
#include "ResourceIdentifier.h"

namespace Utils {
	inline std::string format(const char* fmt, ...) {
		int size = 512;
		char* buffer = 0;
		buffer = new char[size];
		va_list vl;
		va_start(vl, fmt);
		int nsize = vsnprintf(buffer, size, fmt, vl);
		if (size <= nsize) { //fail delete buffer and try again
			delete[] buffer;
			buffer = 0;
			buffer = new char[nsize + 1]; //+1 for /0
			nsize = vsnprintf(buffer, size, fmt, vl);
		}
		std::string ret(buffer);
		va_end(vl);
		delete[] buffer;
		return ret;
	}

	inline void moveView(Context* context, sf::Vector2f translation) {
		sf::View view{ context->window->getView() };
		view.move(translation);
		context->window->setView(view);
	}

	inline void scaleView(Context* context, float scaleFactor, sf::Vector2i origin = { 0, 0 }) {
		const sf::Vector2f beforeCoord{ context->window->mapPixelToCoords(origin) };
		sf::View view{ context->window->getView() };
		view.zoom(scaleFactor);
		context->window->setView(view);
		const sf::Vector2f afterCoord{ context->window->mapPixelToCoords(origin) };
		const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
		view.move(offsetCoords);
		context->window->setView(view);
	}
}