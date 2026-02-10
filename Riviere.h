#pragma once
#include "Case.h"
#include <vector>

using namespace std;

class Riviere {
private:
	int _nbLignes;
	int _nbColonnes;

	vector<vector<Case>> _map;

public:
	Riviere();

	void printRiviere();

	int getLignes();
	int getColonnes();
};