#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "ResourceIdentifier.h"
#include "../Models/Enums/BlendMode.h"

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

	template<typename T>
	inline std::vector<T> slice(std::vector<T> v, unsigned int n) {
		if (n >= v.size()) {
			return v;
		}
		return std::vector<T>(v.begin(), v.begin() + n);
	}

	inline std::string formatTime(sf::Time time) {
		char buffer[10];
		int seconds = (int) time.asSeconds();
		int minutes = seconds / 60;
		seconds = seconds - minutes * 60;
		sprintf_s(buffer, 10, "%02d:%02d", minutes, seconds);
		return buffer;
	}

	inline std::vector<std::string> split(std::string input, std::string delimiter) {
		std::vector<std::string> output;
		size_t prevPos = 0, pos = 0;
		for (; (pos = input.find(delimiter, prevPos)) != std::string::npos; prevPos = pos + delimiter.length()) {
			output.push_back(input.substr(prevPos, pos - prevPos));
		}
		output.push_back(input.substr(prevPos));
		return output;
	}
}