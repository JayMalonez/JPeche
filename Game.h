#pragma once
#include "Riviere.h"

using namespace std;

class Game
{
private:
	Riviere _riviere;
	bool running = true;

public:
	Game();
	void run();

};

