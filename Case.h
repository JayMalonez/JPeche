#pragma once
#include <iostream>

using namespace std;

class Case {
private:
	string _symbole;

	bool _isEmpty;
	bool _isWater;

public:
	Case();

	void printCase();

	bool isEmpty();
	bool isWater();
	void setEmptyState(bool state);
	void setWaterState(bool state);
};

