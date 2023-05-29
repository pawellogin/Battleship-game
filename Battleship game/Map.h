#pragma once
#include <iostream>
#include <cstring>

class Map {
public:
	char matrix[10][10];

public:
	Map() {
		clear_matrix();
	}

	void clear_matrix() {
		memset(matrix, ' ', sizeof(matrix));
	}

	friend std::ostream& operator<<(std::ostream& os, const Map m) {

		for (int i = -1; i < 10; i++) {
			if (i == -1) {
				std::cout << "  ";
				for (int h = 1; h <= 10; h++) {
					os <<"\033[47m\033[30m"<< h << " \033[40m\033[37m";
				}
			}
			else {
				for (int j = -1; j < 10; j++) {
					if (j == -1) {

						os <<"\033[47m\033[30m"<< static_cast<char>('A' + i)<< " \033[40m\033[37m";
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
};
