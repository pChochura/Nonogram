#include "Models/Game.h"
#include "Models/Screens/ScreenMenu.h"
#include "Models/Screens/ScreenPlay.h"

#ifndef _DEBUG
//Disabling terminal while in realease mode
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main() {
	ScreenMenu screen;
	Game game(&screen, "Nonogram");

	game.show();

	return EXIT_SUCCESS;
}