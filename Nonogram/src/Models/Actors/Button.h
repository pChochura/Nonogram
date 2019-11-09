#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include "Actor.h"

class Button : public Actor {
public:
	Button(int id, std::string text, sf::Font textFont, float textSize, sf::Vector2f pos, sf::Vector2f padding, bool visibility = true);
	Button(int id, sf::Texture texture, sf::Vector2f pos, sf::Vector2f size, bool visibility = true);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual bool onEvent(sf::Event) override;
	void setTextColor(sf::Color textColor);
	void setBackgroundColor(sf::Color backgroundColor);
	void setTexture(sf::Texture texture);

private:
	Button(int id);

private:
	std::string text;
	sf::Vector2f padding;
	sf::Color textColor = sf::Color::White;
	sf::Color backgroundColor = sf::Color::Black;
	sf::Font textFont;
	sf::Texture texture;
	float textSize = -1;

public:
	static Button& EMPTY() {
		static Button empty(-1);
		return empty;
	}
};