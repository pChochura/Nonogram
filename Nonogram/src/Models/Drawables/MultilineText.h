#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "../Enums/Align.h"

////////////////////////////////////////////////////////////
//	Class used to display multiple lines of text as a 
//	widget more easily with align capabilities.
////////////////////////////////////////////////////////////
class MultilineText : public sf::Drawable {
public:
	MultilineText();
	MultilineText(const std::string& string, const sf::Font& font, unsigned int characterSize = 30);

	////////////////////////////////////////////////////////////
	//	@inheritDoc
	////////////////////////////////////////////////////////////
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

	////////////////////////////////////////////////////////////
	//	Setters
	////////////////////////////////////////////////////////////
	void setString(std::string);
	void setFillColor(sf::Color);
	void setPosition(sf::Vector2f);
	void setVerticalSpacingMultiplier(float multiplier);
	void setAlignement(Align);
	void setMaxSize(float);

	////////////////////////////////////////////////////////////
	//	Getters
	////////////////////////////////////////////////////////////
	sf::FloatRect getLocalBounds();

	void recalculatePosition();
	void recalculateTexts();
	void splitInput();

private:
	float maxWidth;
	float lineSize;
	Align alignement;
	std::string string;
	sf::Font font;
	sf::Color fillColor;
	sf::Vector2f position;
	unsigned int characterSize;
	float verticalSpacingMultiplier;
	std::vector<sf::Text*> texts;
};