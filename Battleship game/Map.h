#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

class Map {
	std::ofstream ofile;
	std::ifstream ifile;
	const int size = 10;
public:
	char matrix[10][10];
	friend class Player;
public:
	friend std::ostream& operator<<(std::ostream& os, const Map& m) {

		for (int i = -1; i < 10; i++) {
			if (i == -1) {
				std::cout << "  ";
				for (int h = 1; h <= 10; h++) {
					os << "\033[47m\033[30m" << h << " \033[40m\033[37m";
				}
			}
			else {
				for (int j = -1; j < 10; j++) {
					if (j == -1) {

						os << "\033[47m\033[30m" << static_cast<char>('A' + i) << " \033[40m\033[37m";
					}
					else {
						if ((i + j) % 2 == 0) {
							os << "\033[30m\033[44m" << m.matrix[i][j] << " \033[40m\033[37m";
						}
						else {
							os << "\033[30m\033[46m" << m.matrix[i][j] << " \033[40m\033[37m";
						}
					}
				}
			}
			os << "\n";
		}
		return os;
	}

	void save() {
		ofile.open("saveFile.txt");

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				ofile << matrix[i][j];
			}
			ofile << "\n";
		}

		ofile.close();
	}

	void load(int startLine) {
		char ch=' ';
		int row = 0;
		int col = 0;
		int lineCount = 0;
		std::string line;

		ifile.open("saveFile.txt");

		while (std::getline(ifile, line)) {
			lineCount++;
			if (lineCount <= startLine) {
				continue; // Skip the first 10 lines
			}
			for (char ch : line) {
				if (ch == '\n') {
					break; // Break if a newline character is encountered
				}
				matrix[row][col] = ch;
				col++;
			}
			row++;
			col = 0;
		}

	}

	Map() {
		clear_matrix();
	}

	void clear_matrix() {
		memset(matrix, ' ', sizeof(matrix));
	}

	
};
