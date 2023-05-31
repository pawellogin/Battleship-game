#pragma once
#include "Player.h"
#include "Enemy.h"
#include "HitMap.h"
#include "Map.h"

void clearScreen() {
	std::cout << "\033[2J\033[1;1H";
}

class Game {
	Player player;
	Enemy enemy;

public:
	void newGame() {
		int choice=0;
		clearScreen();
		std::cout << "1. random start\n";
		std::cout << "2. place ships by yourself\n";
		std::cout << "3. save game\n";
		std::cout << "4. exit\n";
		std::cin >> choice;

		switch (choice) {
		case 1: 
			player.place_at_random();
			enemy.place_at_random();
			break;
		case 2: 
			player.place_ship();
			enemy.place_at_random();
			break;
		case 3:
			break;
		case 4: 
			break;
		default: break;

		}
	}

	void round() {
		int row=0;
		int column=0;
		bool skipPlayer = 0;

		while (1) {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> dis(0, 9);

			clearScreen();
			player.printHitMap();
			player.printMap();

			if (!skipPlayer) {
				std::cout << "type where to shot\n";
				if (player.getCords(row, column)) {
					clearSaveFile();
					saveGame();
					clearScreen();
					std::cout << "Game saved\n";
					std::this_thread::sleep_for(std::chrono::seconds(1));
					continue;
				}

				if (player.shot(row, column, enemy.getMapPtr())) {
					continue;
				}
			}
			skipPlayer = 0;

			clearScreen();

			std::cout << "enemy turn\n";
			enemy.printHitMap();
			if (enemy.shot(dis(gen), dis(gen), player.getMapPtr())) {
				skipPlayer = 1;
				continue;
			}
		}
	}

	void saveGame() {
		player.save();
		enemy.save();
	}

	void loadGame() {
		player.load();
		enemy.load();
	}

	void clearSaveFile() {
		std::ofstream outputFile("saveFile.txt", std::ios::out | std::ios::trunc);
		outputFile.close();
	}

};