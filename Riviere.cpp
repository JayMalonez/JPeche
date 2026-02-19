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

	_joueur = new Raft(2, getLignes()-1);
	int x = _joueur->getX();
	int y = _joueur->getY();
	_map[y][x].setRaft(_joueur);
}

vector<Case> Riviere::newLine()
{
	vector<Case> ligne;

	do {

		for (int i = 0; i < getColonnes(); i++)
		{
			Case newCase;
			newCase.setPositionX(i);

			ligne.push_back(newCase);
		}

		for (int i = 0; i < getColonnes(); i++) {
			// 10% d’obstacles 
			int r = rand() % 20;
			if (r == 0) {
				ligne[i].setObstacle(new Roche());
			}
			else if (r == 1) {
				ligne[i].setObstacle(new Arbre());
			}
		}
	} while (!validline(ligne));

	return ligne;
}

bool Riviere::validline(vector<Case> ligne) {
	for (Case& c : ligne) {
		if (c.isEmpty()) {
			// une case libre 
			return true;
		}
	} 
	return false;
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

	updateRaft();
}

void Riviere::updateRaft() {
	int x = _joueur->getX();
	int y = _joueur->getY();
	_map[y][x].setRaft(_joueur);
	if (y < 19)
	{
		_map[y + 1][x].removeRaft();
	}
}

void Riviere::deplacerDroite() {
	int x = _joueur->getX();
	int y = _joueur->getY();
	if (x != getColonnes() -1)
	{
		_joueur->setPosition(x + 1, y);
		int newx = _joueur->getX();
		int newy = _joueur->getY();
		_map[newy][newx].setRaft(_joueur);
		_map[y][x].removeRaft();
	}
}

void Riviere::deplacerGauche() {
	int x = _joueur->getX();
	int y = _joueur->getY();
	if (x != 0)
	{
		_joueur->setPosition(x - 1, y);
		int newx = _joueur->getX();
		int newy = _joueur->getY();
		_map[newy][newx].setRaft(_joueur);
		_map[y][x].removeRaft();
	}
}

void Riviere::deplacerHaut() {
	int x = _joueur->getX();
	int y = _joueur->getY();
	if (y != 0)
	{
		_joueur->setPosition(x, y - 1);
		int newx = _joueur->getX();
		int newy = _joueur->getY();
		_map[newy][newx].setRaft(_joueur);
		_map[y][x].removeRaft();
	}
}

void Riviere::deplacerBas() {
	int x = _joueur->getX();
	int y = _joueur->getY();
	if (y != getLignes() -1)
	{
		_joueur->setPosition(x, y + 1);
		int newx = _joueur->getX();
		int newy = _joueur->getY();
		_map[newy][newx].setRaft(_joueur);
		_map[y][x].removeRaft();
	}
}

bool Riviere::validMove()
{
	int x = _joueur->getX();
	int y = _joueur->getY();

	if (_map[y][x].isEmpty())
	{
		return true;
	}
	return false;
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
