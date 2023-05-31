#pragma once
#include "Player.h"
#include "Enemy.h"
#include "HitMap.h"
#include "Map.h"



class Game {
	Player player;
	Enemy enemy;

public:
	void newGame() {
		int choice = 0;
		Player::clearScreen();
		std::cout << "1. random start\n";
		std::cout << "2. place ships by yourself\n";
		std::cin >> choice;

		switch (choice) {
		case 1:
			player.placeAtRandom();
			enemy.placeAtRandom();
			break;
		case 2:
			player.placeShips();
			enemy.placeAtRandom();
			break;
		default: break;

		}
	}

	void round() {
		int row = 0;
		int column = 0;
		bool skipPlayer = 0;

		while (1) {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> dis(0, 9);

			Player::clearScreen();
			player.printHitMap();
			player.printMap();

			if (!skipPlayer) {
				std::cout << "type where to shot\n";
				if (player.getCords(row, column)) {
					clearSaveFile();
					saveGame();
					Player::clearScreen();
					std::cout << "Game saved\n";
					std::this_thread::sleep_for(std::chrono::seconds(1));
					continue;
				}

				if (player.shot(row, column, enemy.getMapPtr())) {
					std::this_thread::sleep_for(std::chrono::seconds(1));
					continue;
				}
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
			skipPlayer = 0;

			Player::clearScreen();

			std::cout << "enemy turn\n";

			if (enemy.shot(dis(gen), dis(gen), player.getMapPtr())) {
				enemy.printHitMap();
				skipPlayer = 1;
				std::this_thread::sleep_for(std::chrono::seconds(1));
				continue;
			}

			enemy.printHitMap();
			std::this_thread::sleep_for(std::chrono::seconds(1));

		}
	}

	void saveGame() {
		player.save();
		enemy.save();
	}

	void loadGame() {
		enemy.load();
		player.load();
		
	}

	void clearSaveFile() {
		std::ofstream outputFile("saveFile.txt", std::ios::out | std::ios::trunc);
		outputFile.close();
	}

};