#include "Models/Game.h"
#include "Models/Screens/ScreenPlay.h"

int main() {
	ScreenPlay screen;
	Game game(screen, "Nonogram");

	game.show();

	return EXIT_SUCCESS;
}