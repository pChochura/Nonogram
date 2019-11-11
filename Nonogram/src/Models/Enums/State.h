#pragma once

enum class State {
	None = 0,
	Empty = 1,
	Filled = 2,
	Selected = 4,
	Marked = 8,
	MarkedNot = 16,
	Lost = 32
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

inline State operator>>(State a, int b) {
	return static_cast<State>(static_cast<int>(a) >> b);
}

inline State operator<<(State a, int b) {
	return static_cast<State>(static_cast<int>(a) << b);
}