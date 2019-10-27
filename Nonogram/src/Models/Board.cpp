#include <time.h>
#include <cstdlib>
#include <vector>
#include <iostream>
#include "Board.h"
#include "Enums/State.h"
#include "Enums/Difficulty.h"

Board::Board() : width(0), height(0), verticalValues(nullptr), horizontalValues(nullptr), map(nullptr) {
	std::srand(time(NULL));
}

Board::~Board() {
	delete this->verticalValues;
	delete this->horizontalValues;
	for (int i = 0; i < this->height; i++) {
		delete this->map[i];
	}
}

void Board::random(Difficulty difficulty) {
	this->width = std::rand() % 4 + 5;
	this->height = std::rand() % 5 + 7;

	this->map = new State * [this->width];
	for (int i = 0; i < this->width; i++) {
		this->map[i] = new State[this->height];
		for (int j = 0; j < this->height; j++) {
			//TODO: add better algorithm to generate maps
			this->map[i][j] = rand() % 2 == 0 ? State::Filled : State::Empty;
		}
	}

	calculateVerticalValues();
	calculateHorizontalValues();
}

State Board::getAt(int x, int y) {
	return this->map[x][y];
}

void Board::setAt(int x, int y, State state) {
	this->map[x][y] = state;
}

std::vector<int> Board::getVerticalValuesFor(int x) {
	return this->verticalValues[x];
}

std::vector<int> Board::getHorizontalValuesFor(int y) {
	return this->horizontalValues[y];
}

void Board::calculateVerticalValues() {
	bool hit = false;
	this->verticalValues = new std::vector<int>[this->width];
	for (int i = 0; i < this->width; i++) {
		hit = false;
		for (int j = 0; j < this->height; j++) {
			if ((getAt(i, j) & State::Filled) == State::Filled) {
				if (!hit) {
					hit = true;
					this->verticalValues[i].push_back(1);
				} else {
					this->verticalValues[i].back()++;
				}
			} else {
				hit = false;
			}
		}
	}
}

void Board::calculateHorizontalValues() {
	bool hit = false;
	this->horizontalValues = new std::vector<int>[this->height];
	for (int i = 0; i < this->height; i++) {
		hit = false;
		for (int j = 0; j < this->width; j++) {
			if ((getAt(j, i) & State::Filled) == State::Filled) {
				if (!hit) {
					hit = true;
					this->horizontalValues[i].push_back(1);
				} else {
					this->horizontalValues[i].back()++;
				}
			} else {
				hit = false;
			}
		}
	}
}