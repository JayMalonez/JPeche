#include "Raft.h"

Raft::Raft(int x, int y)
{
	_x = x;
	_y = y;
}

Raft::~Raft()
{
}

int Raft::getX()
{
	return _x;
}
	
int Raft::getY()
{
	return _y;
}

void Raft::setPosition(int x, int y)
{
	_x = x;
	_y = y;
}

char Raft::getSymbole()
{
	return _symbole;
}