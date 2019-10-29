#pragma once
#include <SFML/Graphics.hpp>

class TransformController {
public:
	void setPos(sf::Vectorf pos);
	void setScale(sf::Vectorf scale);
	void translateTo(sf::Vectorf offset);
	void translateBy(sf::Vectorf offset);
	void scaleTo(sf::Vectorf scale, sf::Vectorf origin = { 0, 0 });
	void scaleBy(sf::Vectorf scale, sf::Vectorf origin = { 0, 0 });

private:
	sf::Vectorf pos;
	sf::Vectorf scale;
};