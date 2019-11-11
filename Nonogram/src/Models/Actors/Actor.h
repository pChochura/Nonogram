#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"
#include "Clickable.h"
#include "../../Utils/ResourceIdentifier.h"

class Actor : public Clickable {
public:
	void act(float deltaTime);
	virtual bool onEvent(Context*, sf::Event) = 0;
	virtual void draw(Context*) const = 0;
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
	std::vector<Animation*> animations;
};