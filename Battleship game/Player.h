#pragma once
#include <iostream>
#include "Ships.h"
#include "Map.h"
#include "HitMap.h"
#include <vector>
#include <cctype>
#include <random>

class Player {
protected:
	std::vector<Ship> list;
	Map map;
	HitMap hit_map;

public:
	Player() {
		add_ships();
	}

	void add_ships() {
		list.push_back(*(new Ship(5)));
		list.push_back(*(new Ship(4)));
		list.push_back(*(new Ship(3)));
		list.push_back(*(new Ship(2)));
		list.push_back(*(new Ship(2)));
		list.push_back(*(new Ship(1)));
		list.push_back(*(new Ship(1)));
	}

	void print_map() {
		std::cout << map;
	}
	

	void place_ship() {
		int choice = 0;
		bool rotation = 1;
		char char_row = 0;
		int column = 0;
		int row = 0;
		bool flag = 1;
		
		for (int k = 0; k < list.size(); k++) {
			std::cout << map << "\033[40m\033[37m";
			std::cout << "ship apperance :\n";
			for (int l = 0; l < list[k].get_size(); l++) {
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
				std::cout << "type in a row(A-J)\n";
				std::cin >> char_row;

				std::cout << "type in a column(1-10)\n";
				std::cin >> column;

				char_row = toupper(char_row);
				row = char_row - 'A';
				
				column--;

				if (rotation) {
					if (column + list[k].get_size() > 10 || row > 10) {
						k--;
						continue;
					}
				}
				else {
					if (row + list[k].get_size() > 10 || column > 10) {
						k--;
						continue;
					}
				}
				
				flag = 1;

				if (rotation) {
					for (int i = column; i < column + list[k].get_size(); i++) {
						if (map.matrix[row][i] != ' ') {
							k--;
							flag = 0;
							break;
						}
					}
					if (flag) {
						for (int i = column; i < column + list[k].get_size(); i++) {
							map.matrix[row][i] = k + '0';
						}
					}
				}
				else {
					for (int i = row; i < row + list[k].get_size(); i++) {
						if (map.matrix[i][column] != ' ') {
							k--;
							flag = 0;
							break;
						}
					}if (flag) {
						for (int i = row; i < row + list[k].get_size(); i++) {
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
		bool flag = 1;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis_c(0, 9);
		std::uniform_int_distribution<int> dis_r(0, 1);

		for (int k = 0; k < list.size(); k++) {

			rotation = dis_r(gen);

			column = dis_c(gen);
			row = dis_c(gen);

			if (rotation) {
				if (column + list[k].get_size() > 10 || row > 10) {
					k--;
					continue;
				}
			}
			else {
				if (row + list[k].get_size() > 10 || column > 10) {
					k--;
					continue;
				}
			}

			flag = 1;

			if (rotation) {
				for (int i = column; i < column + list[k].get_size(); i++) {
					if (map.matrix[row][i] != ' ') {
						k--;
						flag = 0;
						break;
					}
				}
				if (flag) {
					for (int i = column; i < column + list[k].get_size(); i++) {
						map.matrix[row][i] = k + '0';

					}
				}
			}
			else {
				for (int i = row; i < row + list[k].get_size(); i++) {
					if (map.matrix[i][column] != ' ') {
						k--;
						flag = 0;
						break;
					}
				}if (flag) {
					for (int i = row; i < row + list[k].get_size(); i++) {
						map.matrix[i][column] = k + '0';
					}
				}
			}
		}

	}

};

