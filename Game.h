#pragma once
#include "Riviere.h"
#include <chrono>
#include <thread>

using namespace std;

class Game
{
private:
	Riviere _riviere;
	bool running = true;

public:
	Game();
	void run();

	void generateRiver();
};

