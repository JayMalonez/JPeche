#include "Game.h"

Game::Game() : _riviere(), _input("COM3"), _config(InputConfigManager::load("input_config.json")) {

}

void Game::run() {
	_riviere.printRiviere();
	while (_running == true) {
		if (_input.isConnected()) {
			int x = _input.joystickPotX();
			int enc = _input.encodeur();

			int leftThreshold = _config.joystickLeftLimit();
			int rightThreshold = _config.joystickRightLimit();

			// joystick left/right control
			if (x > rightThreshold) {
				_riviere.deplacerDroite();
				checkloss();
			}
			else if (x < leftThreshold) {
				_riviere.deplacerGauche();
				checkloss();
			}

			// encodeur up/down control
			if (enc >= _config.encoderThreshold) {
				_riviere.deplacerBas();
				checkloss();
			}
			else if (enc <= -_config.encoderThreshold) {
				_riviere.deplacerHaut();
				checkloss();
			}
		}
		else {
			// fallback: keyboard controls when serial control unavailable
			if (_kbhit()) {
				char c = _getch();
				switch (c) {
					case 'd':
						_riviere.deplacerDroite();
						checkloss();
						break;
					case 'a':
						_riviere.deplacerGauche();
						checkloss();
						break;
					case 'w':
						_riviere.deplacerHaut();
						checkloss();
						break;
					case 's':
						_riviere.deplacerBas();
						checkloss();
						break;
				}
			}
		}

		_riviere.update();
		checkloss();

		std::cout << "\033[H";
		// Réaffiche toute la rivière par-dessus l'ancienne 
		_riviere.printRiviere();

		this_thread::sleep_for(std::chrono::milliseconds(_config.pollIntervalMs));
	}
}

void Game::checkloss() {
	if (!_riviere.validMove())
	{
		_running = false;
	}
}

void Game::newHighScore(int* highScore) {
	_riviere.newHighScore(highScore);
}
