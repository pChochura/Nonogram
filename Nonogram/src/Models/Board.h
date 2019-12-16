#pragma once
#include <vector>
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>
#include "Enums/State.h"
#include "Enums/Difficulty.h"
#include "../Utils/ResourceIdentifier.h"

////////////////////////////////////////////////////////////
//	Class describing whole board
////////////////////////////////////////////////////////////
class Board {
public:
	Board();
	~Board();

	void set(std::string);
	void random(Context*, Difficulty);

	State getAt(int x, int y);
	void setAt(int x, int y, State state);

	State getCurrentState();
	void setCurrentState(State state);

	////////////////////////////////////////////////////////////
	//	Changes marked tiles to {@param state}
	////////////////////////////////////////////////////////////
	void toggleMarked(State state);

	////////////////////////////////////////////////////////////
	//	Fills tiles with mark when in horizontal or 
	//	vertical line pointed by {@param x} and {@param y}
	//	values no tile can be filled.
	////////////////////////////////////////////////////////////
	void fillMarkedNot(int x, int y);

	////////////////////////////////////////////////////////////
	//	Getter
	////////////////////////////////////////////////////////////
	std::vector<int> getVerticalValuesFor(int x);

	////////////////////////////////////////////////////////////
	//	Returns sequence of tiles with states equal to 
	//	{@param availableState} in the column pointed
	//	by {@param x}.
	////////////////////////////////////////////////////////////
	std::vector<int> calculateVerticalValuesFor(int x, State availableState = State::Filled);

	////////////////////////////////////////////////////////////
	//	Getter
	////////////////////////////////////////////////////////////
	std::vector<int> getHorizontalValuesFor(int y);

	////////////////////////////////////////////////////////////
	//	Returns sequence of tiles with states equal to 
	//	{@param availableState} in the row pointed
	//	by {@param y}.
	////////////////////////////////////////////////////////////
	std::vector<int> calculateHorizontalValuesFor(int y, State availableState = State::Filled);

	////////////////////////////////////////////////////////////
	//	Checks if numbers in sequence is completed for the 
	//	column pointed by {@param x}
	////////////////////////////////////////////////////////////
	std::vector<bool> isVerticalValuesCompleteFor(int x);

	////////////////////////////////////////////////////////////
	//	Checks if numbers in sequence is completed for the row
	//	pointed by {@param x}
	////////////////////////////////////////////////////////////
	std::vector<bool> isHorizontalValuesCompleteFor(int y);

	////////////////////////////////////////////////////////////
	//	Checks if the board is filled correctly 
	////////////////////////////////////////////////////////////
	bool isBoardCompleted();

	void resetBoardScale(Context*);
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
	sf::Clock timer;
	sf::Time timePassed;
	std::function<void(void)> onStopTimerListner;

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