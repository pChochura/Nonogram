#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
		Circle,
		ButtonTutorial,
		ButtonBabyStyle,
		ButtonDecent,
		ButtonImpresive,
		ButtonWorldClass,
		ButtonFromFile,
		DifficultyMenu,
		WinMenu,
		ButtonExit,
		ButtonPlayAgain
	};
}

namespace Sounds {
	enum ID {
		BoardTap,
		ButtonTap
	};
}

namespace Fonts {
	enum ID {
		Arcon,
		Montserrat
	};
}

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::SoundBuffer, Sounds::ID> SoundHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

////////////////////////////////////////////////////////////
//	Structure holding all necessary components.
////////////////////////////////////////////////////////////
struct Context {
	Context(sf::RenderWindow* window) {
		this->window = window;
	}

	sf::RenderWindow* window;
	TextureHolder textures;
	SoundHolder sounds;
	FontHolder fonts;
};