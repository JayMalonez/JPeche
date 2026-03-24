#pragma once
#include "Case.h"
#include "Raft.h"
#include "Roche.h"
#include "Arbre.h"
#include <vector>
#include <cassert>
#include "input.h"

using namespace std;

class Riviere {
private:
	int _nbLignes;
	int _nbColonnes;

	vector<vector<Case>> _map;
	Raft* _joueur;

	int score = 0;

	void scorePlus();
	void scoreMoins();

public:
	Riviere();
	vector<Case> newLine();
	bool validline(vector<Case> ligne);

	void printRiviere();
	void printLine(vector<Case> ligne);
	void update();

	void updateRaft();
	void deplacerDroite();
	void deplacerGauche();
	void deplacerHaut();
	void deplacerBas();
	void deplacerSaut();
	bool validMove();

	int getLignes();
	int getColonnes();
	Case& getCase(int ligne, int colonne);
	int getScore();

	void newHighScore(int* highScore);
};