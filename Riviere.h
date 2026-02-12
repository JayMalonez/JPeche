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
	vector<Case> newLine();

	void printRiviere();
	void printLine(vector<Case> ligne);
	void update();

	int getLignes();
	int getColonnes();
	Case& getCase(int ligne, int colonne);
};