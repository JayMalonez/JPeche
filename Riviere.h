#pragma once
#include "Case.h"
#include <vector>
#include <cassert>

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
	Case& getCase(int ligne, int colonne);
};