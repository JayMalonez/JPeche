#pragma once
#include "Riviere.h"
#include <chrono>
#include <thread>
#include <conio.h>

using namespace std;

class Game
{
private:
	Riviere _riviere;
	bool _running = true;

public:
	Game();
	void run();

	void checkloss();
};

