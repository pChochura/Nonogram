#pragma once
#include <vector>
#include "../Models/Board.h"
#include "../Models/Enums/State.h"

namespace Solver {

	std::vector<std::vector<int>> getCombinationsFor(int offset, std::vector<int> values, int size) {
		int potentialSize = offset;
		for (unsigned int i = offset; i < values.size(); i++) {
			potentialSize += values[i] + (i < values.size() - 1 ? 1 : 0);
		}

		std::vector<std::vector<int>> output;

		if (offset == values.size()) {
			return output;
		}

		if (potentialSize == size) {
			std::vector<int> combination;
			combination.push_back(offset == 0 ? 0 : 1);
			for (unsigned int i = offset; i < values.size(); i++) {
				combination.push_back(values[i]);
				if (i < values.size() - 1) {
					combination.push_back(1);
				}
			}
			output.push_back(combination);
			return output;
		}

		for (int i = offset > 0 ? 1 : 0; i <= size - potentialSize; i++) {
			std::vector<int> combination;
			combination.push_back(i);
			combination.push_back(values[offset]);
			auto result = getCombinationsFor(offset + 1, values, size - (i + values[offset]));
			if (result.empty()) {
				output.push_back(combination);
			}
			for (auto& r : result) {
				r.insert(r.begin(), combination.begin(), combination.end());
				output.push_back(r);
			}
		}

		return output;
	}

	std::vector<std::vector<int>> getCombinations(std::vector<int> values, int size) {
		int potentialSize = 0;
		for (unsigned int i = 0; i < values.size(); i++) {
			potentialSize += values[i] + (i < values.size() - 1 ? 1 : 0);
		}
		return Solver::getCombinationsFor(0, values, size);
	}

	std::vector<std::vector<int>> filterCombinations(std::vector<std::vector<int>> combinations, State** map, int x, int y, int size) {
		std::vector<int> toRemove;
		for (int k = 0; k < combinations.size(); k++) {
			for (int i = 0, pos = 0; i < combinations[k].size() && pos < size; i++) {
				if (i % 2 == 1) {
					for (int j = pos; j < pos + combinations[k][i]; j++) {
						if ((map[x != -1 ? x : j][y != -1 ? y : j] & State::MarkedNot) != State::None) {
							toRemove.insert(toRemove.begin(), k);
							break;
						}
					}
				}
				pos += combinations[k][i];
			}
		}
		for (auto& i : toRemove) {
			combinations.erase(combinations.begin() + i);
		}
		return combinations; 
	}

	std::vector<std::vector<int>> getFilled(std::vector<std::vector<int>> combinations, int size) {
		std::vector<std::vector<int>> allFilled;
		for (auto& combination : combinations) {
			std::vector<int> filled;
			for (int i = 0, pos = 0; i < combination.size() && pos < size; i++) {
				if (i % 2 == 1) {
					for (int j = pos; j < pos + combination[i]; j++) {
						filled.push_back(j);
					}
				}
				pos += combination[i];
			}
			allFilled.push_back(filled);
		}

		if (allFilled.empty()) {
			return allFilled;
		}

		for (int i = allFilled.front().size() - 1; i >= 0; i--) {
			for (int j = 1; j < allFilled.size(); j++) {
				if (std::find(allFilled[j].begin(), allFilled[j].end(), allFilled[0][i]) == allFilled[j].end()) {
					allFilled[0][i] = -1;
				}
			}
		}

		return allFilled;
	}

	void solve(Board* board) {
		for (int y = 0; y < board->height; y++) {
			auto combinations = Solver::getCombinations(board->getHorizontalValuesFor(y), board->width);

			if (combinations.empty()) {
				return;
			}

			//combinations = Solver::filterCombinations(combinations, board->getMap(), -1, y, board->width);
			auto filled = Solver::getFilled(combinations, board->width);

			for (int i = 0; i < filled[0].size(); i++) {
				if (filled[0][i] >= 0 && filled[0][i] < board->width) {
					board->setAt(filled[0][i], y, State::Selected);
				}
			}
		}

		for (int x = 0; x < board->width; x++) {
			auto combinations = Solver::getCombinations(board->getVerticalValuesFor(x), board->height);

			if (combinations.empty()) {
				return;
			}

			//combinations = Solver::filterCombinations(combinations, board->getMap(), x, -1, board->height);
			auto filled = Solver::getFilled(combinations, board->height);

			for (int i = 0; i < filled[0].size(); i++) {
				if (filled[0][i] >= 0 && filled[0][i] < board->height) {
					board->setAt(x, filled[0][i], State::Selected);
				}
			}
		}
	}
}