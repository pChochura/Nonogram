#include <vector>
#include "Game.h"
#include "ScreenPlay.h"

int main() {
	Game game("Nonogram");

	game.changeScreen(ScreenPlay());

	game.show();

	return EXIT_SUCCESS;
}