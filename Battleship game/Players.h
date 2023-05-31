#pragma once
#include <iostream>
#include "Ships.h"
#include "Map.h"
#include "HitMap.h"
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

	void addShips() {
		list.push_back(*(new Ship(5)));
		list.push_back(*(new Ship(4)));
		list.push_back(*(new Ship(3)));
		list.push_back(*(new Ship(2)));
		list.push_back(*(new Ship(2)));
		list.push_back(*(new Ship(1)));
		list.push_back(*(new Ship(1)));
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



	bool shot(int row, int column, Map* map) {
		int temp = 0;

		if (map->matrix[row][column] != ' ') {
			hitMap.matrix[row][column] = 'X';
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (map->matrix[i][j] == map->matrix[row][column]) {
						temp++;
					}
				}
			}
			if (temp > 1) {
				map->matrix[row][column] = 'X';
				std::cout << "hit!\n";
				std::this_thread::sleep_for(std::chrono::seconds(1));
				return 1;
			}
			else if (temp == 1) {
				map->matrix[row][column] = 'X';
				std::cout << "hit and sank!\n";
				std::this_thread::sleep_for(std::chrono::seconds(1));
				return 1;
			}
			temp = 0;
		}
		else {
			hitMap.matrix[row][column] = '*';
			std::cout << "miss\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			return 0;

		}
	}

	bool getCords(int& row, int& column) {
		char charRow;
		std::cout << "type in a row(A-J),'S' if you want to save\n";
		std::cin >> charRow;
		
		charRow = toupper(charRow);

		if (charRow == 'S') {
			return 1;
		}

		std::cout << "type in a column(1-10)\n";
		std::cin >> column;

		

		

		row = charRow - 'A';

		column--;

		return 0;
	}

	void place_ship() {
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
			std::cin >> choice;

			switch (choice) {
			case 1:
				for (int i = 0; i < 3; i++) {
					std::cout << "\033[2K\033[1A";
				}

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
	void place_at_random() {
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

	void save() {
		hitMap.save();
		map.save();
	}

	virtual void load() = 0;
};
