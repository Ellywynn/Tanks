#include "Game.h"

int main(int argc, char* argv[]) {
	std::srand(static_cast<unsigned>(std::time(0)));

	Game game;
	game.run();
	return 0;
}