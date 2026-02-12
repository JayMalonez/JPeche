#include "Obstacle.h"

Obstacle::Obstacle(int x, int y, int taille, int orientation
)
{
	_x = x;
	_y = y;
	_taille = taille;
	_orientation = orientation;
}

Obstacle::~Obstacle()
{
}

int Obstacle::getX()
{
	return _x;
}

int Obstacle::getY()
{
	return _y;
}

int Obstacle::getTaille()
{
	return _taille;
}

int Obstacle::getOrientation()
{
	return _orientation;
}
