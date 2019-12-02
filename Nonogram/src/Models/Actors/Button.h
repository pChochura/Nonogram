#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "../../Utils/ResourceIdentifier.h"

enum ButtonSize {
	WrapContent = INT_MIN
};

////////////////////////////////////////////////////////////
//	Ordinary button with hover state and on click event listener.
////////////////////////////////////////////////////////////
class Button : public Actor {
public:
	Button(int id, sf::Vector2f size = { ButtonSize::WrapContent, ButtonSize::WrapContent });

	////////////////////////////////////////////////////////////
	//	@inheritDoc
	////////////////////////////////////////////////////////////
	virtual bool onEvent(Context*, sf::Event) override;

	////////////////////////////////////////////////////////////
	//	@inheritDoc
	////////////////////////////////////////////////////////////
	virtual void draw(Context* context) const override;

	////////////////////////////////////////////////////////////
	//	Setters returning instance of Button class to provide
	//	chain call
	////////////////////////////////////////////////////////////
	Button* withTexture(sf::Texture texture);

	Button* withPadding(sf::Vector2f padding);

	Button* withText(std::string text);
	Button* withTextSize(float textSize);
	Button* withTextColor(sf::Color textColor);
	Button* withTextFont(sf::Font textFont);

	Button* withBackgroundColor(sf::Color backgroundColor);

	Button* withPosition(sf::Vector2f position);

	Button* build();

private:
	bool isHovering(Context*) const;
	void calculateSize();

private:
	bool hasBackgroundColor;

	sf::Texture texture;

	sf::Vector2f padding;

	float textSize = -1;

	std::string text;
	sf::Color textColor;
	sf::Font textFont;

	sf::Color backgroundColor;

public:
	bool hasTexture;

	////////////////////////////////////////////////////////////
	//	`Empty` Button object
	////////////////////////////////////////////////////////////
	static Button& EMPTY() {
		static Button empty(-1);
		return empty;
	}
};