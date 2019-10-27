#pragma once

enum class State {
	Empty = 0,
	Filled = 1,
	Correct = 2,
	Wrong = 4,
	Mark = 8
};

inline State operator|(State a, State b) {
	return static_cast<State>(static_cast<int>(a) | static_cast<int>(b));
}

inline State operator&(State a, State b) {
	return static_cast<State>(static_cast<int>(a) & static_cast<int>(b));
}