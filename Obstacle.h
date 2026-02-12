#pragma once

class Obstacle
{
	protected:
		int _x;
		int _y;
		int _taille;
		int _orientation; // 0: horizontal, 1: vertical

	public:
		Obstacle(int x=0, int y=0, int taille=0, int orientation=0);
		virtual ~Obstacle();
		int getX();
		int getY();
		int getTaille();
		int getOrientation();
		virtual char getSymbole() = 0;
};