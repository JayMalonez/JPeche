#pragma once
#include "Obstacle.h"
#include "Raft.h"
#include <iostream>

using namespace std;

class Case {
private:
	string _symbole;
	Obstacle* _obstacle;

	int _x;
	int _y;
	bool _isEmpty;
	bool _isWater;

public:
	Case();

	void printCase();

	int positionX();
	int positionY();
	bool isEmpty();
	bool isWater();

	void setPositionX(int x);
	void setPositionY(int y);
	void setEmptyState(bool state);
	void setWaterState(bool state);
	void setObstacle(Obstacle* obstacle);
	void setRaft(Raft* joueur);
	void removeRaft();
};

