#pragma once
#include "Players.h"

class Enemy : public Players {
public:
	void load() override {
		map.load(30);
		hitMap.load(0);
		
	}
};
