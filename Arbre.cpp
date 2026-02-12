#include "Arbre.h"

Arbre::Arbre(int x, int y, int taille, int orientation) : Obstacle(x, y, taille, orientation)
{
}

Arbre::~Arbre()
{
}

int Arbre::getX()
{
	return _x;
}

int Arbre::getY()
{
	return _y;
}

int Arbre::getTaille()
{
	return _taille;
}

int Arbre::getOrientation()
{
	return _orientation;
}

char Arbre::getSymbole() {
	return _symbole;
}