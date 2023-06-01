#pragma once
#include <iostream>
#include "Ships.h"
#include "Map.h"
#include "HitMap.h"
#include "Game.h"
#include <vector>
#include <cctype>
#include <random>
#include <chrono>
#include <thread>

class Players {

protected:
	std::vector<Ship> list;
	Map map;
	HitMap hitMap;

public:
	Players() {
		addShips();
	}

	bool shot(int row, int column, Map* map) {
		int counter = 0;

		if (map->matrix[row][column] != ' ') {
			hitMap.matrix[row][column] = 'X';
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (map->matrix[i][j] == map->matrix[row][column]) {
						counter++;
					}
				}
			}
			if (counter > 1) {
				map->matrix[row][column] = 'X';
				std::cout << "hit!\n";
				return 1;
			}
			else if (counter == 1) {
				map->matrix[row][column] = 'X';
				std::cout << "hit and sank!\n";
				return 1;
			}
			counter = 0;
		}
		else {
			hitMap.matrix[row][column] = '*';
			std::cout << "miss\n";
			return 0;
		}
	}

	bool getCords(int& row, int& column) {
		while (1) {
			char charRow;
			std::cout << "Type in a row (A-J), 'S' if you want to save: ";
			std::cin >> charRow;

			charRow = std::toupper(charRow);

			if (charRow == 'S') {
				return true;
			}

			if (charRow < 'A' || charRow > 'J') {
				std::cout << "Invalid row input. Please enter a character between 'A' and 'J'." << std::endl;
				std::cout << '\b' << ' ' << '\b';
				clearLines(2);
				continue;
			}

			std::cout << "Type in a column (1-10): ";
			std::cin >> column;

			if (column < 1 || column > 10) {
				std::cout << "Invalid column input. Please enter a number between 1 and 10." << std::endl;
				std::cout << '\b' << ' ' << '\b';
				clearLines(2);
				continue;
			}

			row = charRow - 'A';
			column--;

			return false;
		}
	}

	void placeShips() {
		int choice = 0;
		bool rotation = 1;
		char charRow = 0;
		int column = 0;
		int row = 0;
		bool flag = 1;

		for (int k = 0; k < list.size(); k++) {
			std::cout << map << "\033[40m\033[37m";
			std::cout << "ship apperance :\n";
			for (int l = 0; l < list[k].getSize(); l++) {
				if (rotation) {
					std::cout << "# ";
				}
				else {
					std::cout << "#\n";
				}
			}
			std::cout << "\n";
			std::cout << "1. place ship\n";
			std::cout << "2. rotate ship\n";

			std::cout << "choose option\n";
			if (!(std::cin >> choice) && choice!=1 && choice!=2) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid input. Please enter a valid choice.\n";
				k--;
				std::this_thread::sleep_for(std::chrono::seconds(1));
				clearScreen();
				continue;
			}

			switch (choice) {
			case 1:
				clearLines(3);

				getCords(row, column);

				if (rotation) {
					if (column + list[k].getSize() > 10 || row > 10) {
						k--;
						continue;
					}
				}
				else {
					if (row + list[k].getSize() > 10 || column > 10) {
						k--;
						continue;
					}
				}

				flag = 1;

				if (rotation) {
					for (int i = column; i < column + list[k].getSize(); i++) {
						if (map.matrix[row][i] != ' ') {
							k--;
							flag = 0;
							break;
						}
					}
					if (flag) {
						for (int i = column; i < column + list[k].getSize(); i++) {
							map.matrix[row][i] = k + '0';
						}
					}
				}
				else {
					for (int i = row; i < row + list[k].getSize(); i++) {
						if (map.matrix[i][column] != ' ') {
							k--;
							flag = 0;
							break;
						}
					}if (flag) {
						for (int i = row; i < row + list[k].getSize(); i++) {
							map.matrix[i][column] = k + '0';
						}
					}
				}
				break;

			case 2:
				rotation = !rotation;
				k--;
				break;
			default: break;
			}
			std::cout << "\033[2J";
		}
	}
	void placeAtRandom() {
		bool rotation = 1;
		int column = 0;
		int row = 0;
		bool isEmpty = 1;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis_c(0, 9);
		std::uniform_int_distribution<int> dis_r(0, 1);

		for (int k = 0; k < list.size(); k++) {

			rotation = dis_r(gen);

			column = dis_c(gen);
			row = dis_c(gen);

			if (rotation) { // 0 0 0 0 
				if (column + list[k].getSize() > 10 || row > 10) {
					k--;
					continue;
				}
			}
			else {
				if (row + list[k].getSize() > 10 || column > 10) {
					k--;
					continue;
				}
			}

			isEmpty = 1;

			if (rotation) {
				for (int i = column - 1; i < column + list[k].getSize() + 1; i++) {

					if (map.matrix[row][i] != ' ') {
						k--;
						isEmpty = 0;
						break;
					}
					if (map.matrix[row + 1][i] != ' ') {
						k--;
						isEmpty = 0;
						break;
					}
					if (map.matrix[row - 1][i] != ' ') {
						k--;
						isEmpty = 0;
						break;
					}
				}
				if (isEmpty) {
					for (int i = column; i < column + list[k].getSize(); i++) {
						map.matrix[row][i] = k + '0';

					}
				}
			}
			else {
				for (int i = row - 1; i < row + list[k].getSize() + 1; i++) {
					if (map.matrix[i][column] != ' ') {
						k--;
						isEmpty = 0;
						break;
					}
					if (map.matrix[i][column + 1] != ' ') {
						k--;
						isEmpty = 0;
						break;
					}
					if (map.matrix[i][column - 1] != ' ') {
						k--;
						isEmpty = 0;
						break;
					}
				}

				if (isEmpty) {
					for (int i = row; i < row + list[k].getSize(); i++) {
						map.matrix[i][column] = k + '0';
					}
				}
			}
		}
	}

	void addShips() {
		list.push_back(*(new Ship(5)));
		list.push_back(*(new Ship(4)));
		list.push_back(*(new Ship(3)));
		list.push_back(*(new Ship(2)));
		list.push_back(*(new Ship(2)));
		list.push_back(*(new Ship(1)));
		list.push_back(*(new Ship(1)));
	}

	void save() {
		hitMap.save();
		map.save();
	}

	static void clearScreen() {
		std::cout << "\033[2J\033[1;1H";
	}

	void printMap() {
		std::cout << map;
	}

	void printHitMap() {
		std::cout << hitMap;
	}

	Map* getMapPtr() {
		return &(map);
	}

	Map* getHitMapPtr() {
		return &(hitMap);
	}

	void clearLines(int n) {
		for (int i = 0; i < n; i++) {
			std::cout << "\033[2K\033[1A";
		}
	}

	virtual void load() = 0;
};
