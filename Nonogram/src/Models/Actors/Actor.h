#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Clickable.h"
#include "../../Utils/ResourceIdentifier.h"

////////////////////////////////////////////////////////////
//	Class describing elements with properties such as opacity, rotation or visibility.
////////////////////////////////////////////////////////////
class Actor : public Clickable {
public:
	////////////////////////////////////////////////////////////
	//	Method invoked when SFML event occured. For instance: the mouse was moved.
	////////////////////////////////////////////////////////////
	virtual bool onEvent(Context*, sf::Event) = 0;

	////////////////////////////////////////////////////////////
	//	Method invoked every frame. Should be used only for drawing.
	////////////////////////////////////////////////////////////
	virtual void draw(Context*) const = 0;

	////////////////////////////////////////////////////////////
	// Getters and setters
	////////////////////////////////////////////////////////////
	sf::Vector2f getPos();
	sf::Vector2f getSize();
	float getAlpha();
	float getRotation();
	bool isVisible();
	void setVsibility(bool visibility);

protected:
	float alpha;
	float rotation;
	bool visible;
	sf::Vector2f pos;
	sf::Vector2f size;
};