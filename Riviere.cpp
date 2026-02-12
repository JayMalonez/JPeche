#include "Riviere.h"

Riviere::Riviere() {
	_nbColonnes = 5;
	_nbLignes = 20; //temporaire

	vector<Case> ligne;

	for (int i = 0; i < getLignes(); i++) {

		vector<Case> ligne;

		for (int j = 0; j < getColonnes(); j++) {

			Case caseVide;
			caseVide.setPositionX(j);
			caseVide.setPositionY(i);

			ligne.push_back(caseVide);
		}

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

Case& Riviere::getCase(int ligne, int colonne)
{
	assert(ligne >= 0 && colonne >= 0 && ligne < getLignes() && colonne < getColonnes());

	return _map[ligne][colonne];
}
