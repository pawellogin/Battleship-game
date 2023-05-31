#pragma once
#include "Players.h"

class Player : public Players {
public:
	void load() override {
		map.load(10);
		hitMap.load(0);
	}
};

