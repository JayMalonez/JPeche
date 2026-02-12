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

vector<Case> Riviere::newLine()
{
	vector<Case> ligne;

	for (int i = 0; i < getColonnes(); i++)
	{
		Case caseVide;
		caseVide.setObstacle();  //temporaire
		caseVide.setPositionX(i);

		ligne.push_back(caseVide);
	}
	return ligne;
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

	/*for (int i = 0; i < getLignes(); i++) {
		for (int j = 0; j < getColonnes(); j++) {
			cout << _map[i][j].positionX() << "," << _map[i][j].positionY() << " ";
			if (j == getColonnes() - 1) {
				cout << endl;
			}
		}
	}*/
}

void Riviere::printLine(vector<Case> ligne) {
	for (int i = 0; i < getColonnes(); i++) {
		ligne[i].printCase();
		if (i == getColonnes() - 1) {
			cout << endl;
		}
	}
}

void Riviere::update() {
	// Décale toutes les lignes vers le bas 
	for (int i = getLignes() - 1; i > 0; i--) {
		_map[i] = _map[i - 1]; 

		for (int j = 0; j < getColonnes(); j++) { 
			_map[i][j].setPositionY(i); 
		}
	}
	
	_map[0] = newLine();
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
