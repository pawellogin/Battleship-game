#include "Game.h"

int main() {
	
	Game game;

	std::cout << "1 star new game\n";
	std::cout << "2 load saved game\n";
	std::cout << "3. exit\n";


	int choice = 0;
	std::cin >> choice;
	switch (choice) {
	case 1: 
		game.newGame();
		break;
	case 2: // load game
		break;
	case 3: return 0;
	default: break;
	}

	while (1) {
		game.round();
	}


	return 0;
}