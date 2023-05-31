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
	int getSize() {
		return size;
	}
};
