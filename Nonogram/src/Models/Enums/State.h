#pragma once

enum class State {
	Empty = 0,
	Filled = 1,
	Selected = 2,
	Marked = 4,
	MarkedNot = 8,
	Lost = 16
};

inline State operator|(State a, State b) {
	return static_cast<State>(static_cast<int>(a) | static_cast<int>(b));
}

inline State operator&(State a, State b) {
	return static_cast<State>(static_cast<int>(a) & static_cast<int>(b));
}

inline State operator~(State a) {
	return static_cast<State>(~static_cast<int>(a));
}