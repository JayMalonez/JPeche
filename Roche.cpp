#include "Roche.h"

Roche::Roche(int x, int y, int taille, int orientation) : Obstacle(x, y, taille, orientation)
{
}

Roche::~Roche()
{
}

int Roche::getX()
{
	return _x;
}

int Roche::getY()
{
	return _y;
}

