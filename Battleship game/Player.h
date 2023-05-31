#pragma once
#include "Players.h"

class Player : public Players {
public:
	void load() override {
		map.load(0);
		hitMap.load(10);
	}
};

