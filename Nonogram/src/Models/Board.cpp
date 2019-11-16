#include <time.h>
#include <cstdlib>
#include <vector>
#include "Board.h"
#include "Enums/State.h"
#include "Enums/Difficulty.h"
#include "../Utils/Utils.h"

Board::Board() : width(0), height(0), currentState(State::Marked), verticalValues(nullptr), horizontalValues(nullptr), map(nullptr) {
	std::srand((unsigned int) time(NULL));
}

Board::~Board() {
	delete this->verticalValues;
	delete this->horizontalValues;
	for (int i = 0; i < this->height; i++) {
		delete this->map[i];
	}
}

void Board::random(Difficulty difficulty) {
	int maxWidth = 5, maxHeight = 5;
	int constCount = 0;
	switch (difficulty) {
	case Difficulty::BabyStyle:
		maxWidth = maxHeight = 5;
		constCount = rand() % 3 + 5;
		break;
	case Difficulty::Decent:
		maxWidth = maxHeight = 8;
		constCount = rand() % 1 + 3;
		break;
	case Difficulty::Impresive:
		maxWidth = maxHeight = 12;
		break;
	case Difficulty::WorldClass:
		maxWidth = maxHeight = 16;
		break;
	}
	this->width = std::rand() % 3 + maxWidth;
	this->height = std::rand() % 3 + maxHeight;

	this->map = new State * [this->width];
	this->mapCopy = new State * [this->width];
	for (int i = 0; i < this->width; i++) {
		this->map[i] = new State[this->height];
		this->mapCopy[i] = new State[this->height];
		for (int j = 0; j < this->height; j++) {
			//TODO: add better algorithm to generate maps
			this->map[i][j] = rand() % 2 == 0 ? State::Filled : State::Empty;
		}
	}

	for (int x, y; constCount > 0; constCount--) {
		do {
			x = rand() % this->width;
			y = rand() % this->height;
		} while ((this->map[x][y] & State::Const) != State::None);
		this->map[x][y] = this->map[x][y] | (this->map[x][y] == State::Filled ? State::Selected : State::MarkedNot) | State::Const;
	}

	calculateVerticalValues();
	calculateHorizontalValues();
	startTimer();
}

State Board::getAt(int x, int y) {
	return this->map[x][y];
}

void Board::setAt(int x, int y, State state) {
	this->map[x][y] = state;

	if (isBoardCompleted()) {
		stopTimer();
	}
}

State Board::getCurrentState() {
	return this->currentState;
}

void Board::setCurrentState(State state) {
	this->currentState = state;
}

void Board::toggleMarked(State state) {
	backupMap();
	for (int i = 0; i < this->width; i++) {
		for (int j = 0; j < this->height; j++) {
			if ((this->map[i][j] & State::Marked) != State::None) {
				State rawState = this->map[i][j] & (State::Empty | State::Filled);
				this->mapCopy[i][j] = rawState | state;
			}
		}
	}
	restoreMap();
	if (state == State::Selected) {
		for (int i = 0; i < this->width; i++) {
			for (int j = 0; j < this->height; j++) {
				fillMarkedNot(i, j);
			}
		}
	}
}

void Board::fillMarkedNot(int x, int y) {
	if (calculateVerticalValuesFor(x, State::Selected) == getVerticalValuesFor(x)) {
		for (int i = 0; i < this->height; i++) {
			if ((this->map[x][i] & State::Selected) != State::Selected) {
				this->map[x][i] = this->map[x][i] | State::Marked;
			}
		}
	}
	if (calculateHorizontalValuesFor(y, State::Selected) == getHorizontalValuesFor(y)) {
		for (int i = 0; i < this->width; i++) {
			if ((this->map[i][y] & State::Selected) != State::Selected) {
				this->map[i][y] = this->map[i][y] | State::Marked;
			}
		}
	}
}

std::vector<int> Board::getVerticalValuesFor(int x) {
	return this->verticalValues[x];
}

std::vector<int> Board::getHorizontalValuesFor(int y) {
	return this->horizontalValues[y];
}

void Board::calculateVerticalValues() {
	this->verticalValues = new std::vector<int>[this->width];
	for (int i = 0; i < this->width; i++) {
		this->verticalValues[i] = calculateVerticalValuesFor(i);
	}
}

std::vector<int> Board::calculateVerticalValuesFor(int x, State state) {
	std::vector<int> values;
	bool hit = false;
	for (int i = 0; i < this->height; i++) {
		if ((this->map[x][i] & state) != State::None) {
			if (!hit) {
				hit = true;
				values.push_back(1);
			} else {
				values.back()++;
			}
		} else {
			hit = false;
		}
	}
	return values;
}

void Board::calculateHorizontalValues() {
	this->horizontalValues = new std::vector<int>[this->height];
	for (int i = 0; i < this->height; i++) {
		this->horizontalValues[i] = calculateHorizontalValuesFor(i);
	}
}

void Board::backupMap() {
	for (int i = 0; i < this->width; i++) {
		for (int j = 0; j < this->height; j++) {
			this->mapCopy[i][j] = this->map[i][j];
		}
	}
}

void Board::restoreMap() {
	for (int i = 0; i < this->width; i++) {
		for (int j = 0; j < this->height; j++) {
			this->map[i][j] = this->mapCopy[i][j];
		}
	}
}

std::vector<int> Board::calculateHorizontalValuesFor(int y, State state) {
	std::vector<int> values;
	bool hit = false;
	for (int j = 0; j < this->width; j++) {
		if ((this->map[j][y] & state) != State::None) {
			if (!hit) {
				hit = true;
				values.push_back(1);
			} else {
				values.back()++;
			}
		} else {
			hit = false;
		}
	}
	return values;
}

std::vector<bool> Board::isVerticalValuesCompleteFor(int x) {
	std::vector<int> values = getVerticalValuesFor(x);
	std::vector<int> currentValues;
	bool hit = false;
	for (int i = 0; i < this->height; i++) {
		if ((this->map[x][i] & State::Selected) != State::None) {
			if (!hit) {
				hit = true;
				currentValues.push_back(1);
			} else {
				currentValues.back()++;
			}
		} else {
			if ((this->map[x][i] & (State::MarkedNot | State::Marked)) == State::None && 
				currentValues != Utils::slice(values, currentValues.size())) {
				break;
			}
			hit = false;
		}
	}

	std::vector<bool> isComplete;
	bool complete = true;
	for (unsigned int i = 0; i < values.size(); i++) {
		if (i >= currentValues.size() || values[i] != currentValues[i]) {
			complete = false;
		}
		isComplete.push_back(complete);
	}
	return isComplete;
}

std::vector<bool> Board::isHorizontalValuesCompleteFor(int y) {
	std::vector<int> values = getHorizontalValuesFor(y);
	std::vector<int> currentValues;
	bool hit = false;
	for (int i = 0; i < this->width; i++) {
		if ((this->map[i][y] & State::Selected) != State::None) {
			if (!hit) {
				hit = true;
				currentValues.push_back(1);
			} else {
				currentValues.back()++;
			}
		} else {
			if ((this->map[i][y] & (State::MarkedNot | State::Marked)) == State::None &&
				currentValues != Utils::slice(values, currentValues.size())) {
				break;
			}
			hit = false;
		}
	}

	std::vector<bool> isComplete;
	bool complete = true;
	for (unsigned int i = 0; i < values.size(); i++) {
		if (i >= currentValues.size() || values[i] != currentValues[i]) {
			complete = false;
		}
		isComplete.push_back(complete);
	}
	return isComplete;
}

bool Board::isBoardCompleted() {
	int size = std::max(this->width, this->height);
	for (int i = 0; i < size; i++) {
		if (i < this->width) {
			if (getVerticalValuesFor(i) != calculateVerticalValuesFor(i, State::Selected)) {
				return false;
			}
		}
		if (i < this->height) {
			if (getHorizontalValuesFor(i) != calculateHorizontalValuesFor(i, State::Selected)) {
				return false;
			}
		}
	}
	return true;
}

void Board::startTimer() {
	timePassed = sf::Time::Zero;
	this->timer.restart();
}

void Board::stopTimer() {
	this->timePassed = this->timer.getElapsedTime();
	if (this->onStopTimerListner != nullptr) {
		this->onStopTimerListner();
	}
}

sf::Time Board::getElapsedTime() {
	if (timePassed == sf::Time::Zero) {
		return this->timer.getElapsedTime();
	}
	return timePassed;
}

void Board::setOnStopTimerListener(std::function<void(void)> onStopTimerListner) {
	this->onStopTimerListner = onStopTimerListner;
}
