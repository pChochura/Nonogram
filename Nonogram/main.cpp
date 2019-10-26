#include <vector>
#include "StageBackground.h"
#include "Screen.h"

int main() {
	std::vector<Stage*> stages;

	StageBackground stageBg;
	stages.push_back(&stageBg);

	Screen screen(stages, "Nonogram");

	screen.show();

	return EXIT_SUCCESS;
}