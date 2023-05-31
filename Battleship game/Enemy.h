#pragma once
#include "Players.h"


class Enemy : public Players {
public:
	void load() override {
		map.load(20);
		hitMap.load(30);
	}
};
