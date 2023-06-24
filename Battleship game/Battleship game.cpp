#include "Game.h"

int main() {
	
	Game game;

	std::cout << "1 star new game\n";
	std::cout << "2 load saved game\n";
	std::cout << "3. exit\n";


	int choice = 0;
	while (1) {
		if (!(std::cin >> choice) || choice>4) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter a valid choice.\n";
			continue;
		}

		switch (choice) {
		case 1:
			game.newGame();
			break;
		case 2: game.loadGame();
			break;
		case 3: return 0;
		default: continue;
		}

		while (1) {
			game.round();
		}
	}

	return 0;
}