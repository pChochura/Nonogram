#include "Models/Game.h"
#include "Models/Screens/ScreenMenu.h"

int main() {
	ScreenMenu screen;
	Game game(screen, "Nonogram");

	game.show();

	return EXIT_SUCCESS;
}