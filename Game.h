#pragma once
#include "Riviere.h"
#include "Input.h"
#include "InputConfig.h"
#include <chrono>
#include <thread>
#include <conio.h>

using namespace std;

class Game
{
private:
	Riviere _riviere;
	COM_Serial _input;
	InputConfig _config;
	bool _running = true;

public:
	Game();
	void run();

	void checkloss();
	void newHighScore(int *highScore);
};
