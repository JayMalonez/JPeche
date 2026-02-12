#include "Obstacle.h"


class Arbre: public Obstacle {
protected:
	
	char _symbole = 'A';

public:
	Arbre(int x = 0, int y = 0, int taille = 1, int orientation = 0);
	~Arbre();
	int getX();
	int getY();
	int getTaille();
	int getOrientation();
	virtual char getSymbole();
};
