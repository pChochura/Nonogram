#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include "Actor.h"

class Button : public Actor, public sf::Drawable {
public:
	Button(std::string text, sf::Font textFont, float textSize, sf::Vector2f pos, sf::Vector2f padding);
	void setOnClickListener(std::function<void(void)> onClickListener);
	void onEvent(sf::Event*);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setTextColor(sf::Color textColor);
	void setBackgroundColor(sf::Color backgroundColor);

private:
	std::function<void(void)> onClickListener;
	std::string text;
	sf::Vector2f padding;
	sf::Color textColor = sf::Color::White;
	sf::Color backgroundColor = sf::Color::Black;
	sf::Font textFont;
	float textSize;
};