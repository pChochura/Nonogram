#pragma once

////////////////////////////////////////////////////////////
//	States of map tiles with binary operators to stack them. 
//	Thus they have to be powers of 2.
////////////////////////////////////////////////////////////
enum class State {
	None		=	0,
	Empty		=	(1 << 1),
	Filled		=	(1 << 2),
	Selected	=	(1 << 3),
	Marked		=	(1 << 4),
	MarkedNot	=	(1 << 5),
	Lost		=	(1 << 6),
	Const		=	(1 << 7)
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