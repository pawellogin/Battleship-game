#pragma once
class Ship {
	int size;
	int hp;
public:
	Ship(int s) {
		size = s;
		hp = size;
	}
	void hit() {
		hp--;
	}
	int get_size() {
		return size;
	}
};
//1x Carier 5 
//1x Battleship 4
//1x Crusier 3
//2x Destroyer 2 
//2x Submarine 1