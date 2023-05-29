#include <iostream>
#include "Map.h"
#include "Ships.h"
#include "Player.h"
#include "Enemy.h"


int main() {
	Player player;
	Enemy enemy;


	enemy.place_at_random();
	enemy.print_map();

	std::cout << "1 star new game\n";
	std::cout << "2 load saved game\n";
	std::cout << "3. exit\n";


	int choice = 1;
	switch (choice) {
	case 1: player.place_ship();
		break;
	case 2: // load game
		break;
	case 3: return 0;
		break;
	case 4:
		break;
	case 5:
		break;

	}


	return 0;
}