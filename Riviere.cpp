#include "Riviere.h"

Riviere::Riviere() {
	_nbColonnes = 5;
	_nbLignes = 10; //temporaire

	vector<Case> ligne;
	Case caseVide;

	for (int i = 0; i < getColonnes(); i++) {
		ligne.push_back(caseVide);
	}

	for (int i = 0; i < getLignes(); i++) {
		_map.push_back(ligne);
	}
}

void Riviere::printRiviere() {
	for (int i = 0; i < getLignes(); i++) {
		for (int j = 0; j < getColonnes(); j++) {
			_map[i][j].printCase();
			if (j == getColonnes() - 1) {
				cout << endl;
			}
		}
	}
}

int Riviere::getLignes()
{
	return _nbLignes;
}

int Riviere::getColonnes()
{
	return _nbColonnes;
}
