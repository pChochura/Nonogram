#pragma once
#include <vector>
#include <functional>
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
	void toggleMarked(State state);
	void fillMarkedNot(int x, int y);
	std::vector<int> getVerticalValuesFor(int x);
	std::vector<int> calculateVerticalValuesFor(int x, State availableState = State::Filled);
	std::vector<int> getHorizontalValuesFor(int y);
	std::vector<int> calculateHorizontalValuesFor(int y, State availableState = State::Filled);
	std::vector<bool> isVerticalValuesCompleteFor(int x);
	std::vector<bool> isHorizontalValuesCompleteFor(int y);
	bool isBoardCompleted();
	void startTimer();
	void stopTimer();
	sf::Time getElapsedTime();
	void setOnStopTimerListener(std::function<void(void)> onStopTimerListner);

private:
	void calculateVerticalValues();
	void calculateHorizontalValues();
	void backupMap();
	void restoreMap();

private:
	std::function<void(void)> onStopTimerListner;
	sf::Clock timer;
	sf::Time timePassed;
	std::vector<int>* verticalValues;
	std::vector<int>* horizontalValues;
	State** map;
	State** mapCopy;
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