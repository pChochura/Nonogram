#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Enums/State.h"
#include "Enums/Difficulty.h"

class Board {
public:
	Board();
	~Board();
	void random(Difficulty);
	State getAt(int x, int y);
	void setAt(int x, int y, State state);
	State getCurrentState();
	void setCurrentState(State state);
	std::vector<int> getVerticalValuesFor(int x);
	std::vector<int> getHorizontalValuesFor(int y);

private:
	void calculateVerticalValues();
	void calculateHorizontalValues();

private:
	std::vector<int>* verticalValues;
	std::vector<int>* horizontalValues;
	State** map;
	State currentState;

public:
	int width;
	int height;
	float scale;
	float scaleAmount;
	float tileSize;
	sf::Vector2i tileMargin;
	sf::Vector2i padding;
	sf::Vector2i offset;
};