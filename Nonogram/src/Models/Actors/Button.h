#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include "Actor.h"

class Button : public Actor, public sf::Drawable {
public:
	Button(int id, std::string text, sf::Font textFont, float textSize, sf::Vector2f pos, sf::Vector2f padding);
	Button(int id, sf::Texture texture, sf::Vector2f pos, sf::Vector2f size);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setOnClickListener(std::function<void(Button*)> onClickListener);
	void onEvent(sf::Event);
	void setTextColor(sf::Color textColor);
	void setBackgroundColor(sf::Color backgroundColor);
	void setTexture(sf::Texture texture);
	int getId();

private:
	std::function<void(Button*)> onClickListener;
	std::string text;
	sf::Vector2f padding;
	sf::Color textColor = sf::Color::White;
	sf::Color backgroundColor = sf::Color::Black;
	sf::Font textFont;
	sf::Texture texture;
	float textSize = -1;
	int id;
};