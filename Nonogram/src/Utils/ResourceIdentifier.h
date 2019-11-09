#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"

namespace Textures {
	enum ID {
		Background,
		BoardTile,
		BoardTileSelected,
		BoardTileWin,
		BoardTileLost,
		BoardTileMarked,
		BoardTileMarkedNot,
		BoardTileMarkedExpand,
		BoardTileHovered,
		BottomMenu,
		MarkExpandMenu,
		ButtonMarkedToSelected,
		ButtonMarkedToNot,
		ButtonMarkedToEmpty,
		Heart,
		HearBroken,
		Circle
	};
}

namespace Fonts {
	enum ID {
		Arcon
	};
}

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

struct Context {
	Context(sf::RenderWindow* window) {
		this->window = window;
	}

	sf::RenderWindow* window;
	TextureHolder textures;
	FontHolder fonts;
};