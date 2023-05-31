#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

const int SIZE = 10;

class Map {
	std::ofstream ofile;
	std::ifstream ifile;
public:
	char matrix[SIZE][SIZE];
	friend class Player;

	Map() {
		clearMatrix();
	}

	void clearMatrix() {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				matrix[i][j] = ' ';
			}
		}
	}

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
		std::ofstream outputFile("saveFile.txt",std::ios::app); 

		if (outputFile.is_open()) { 
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					outputFile << matrix[i][j]; 
				}
				outputFile << "\n"; 
			}

			outputFile.close(); 
			std::cout << "Array saved successfully." << std::endl;
		}
		else {
			std::cout << "Unable to open the file." << std::endl;
		}
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
					continue;
				}
			
			for (char ch : line) {
				if (ch == '\n') {
					break;
				}
				matrix[row][col] = ch;
				col++;
			}
			row++;
			col = 0;
		}
	}

	
};
