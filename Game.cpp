#include "Game.h"

Game::Game() : _riviere(), _input("COM4"), _config(InputConfigManager::load("input_config.json")) {

}

void Game::run() {
	int compteur = 0;
	int compteur_cible = 10 / _config.pollIntervalMs; 
	int score_bargraph = 0;
	int val_bargraph = 0;

	_riviere.printRiviere();
	do {
		_input.askMSG();
		this_thread::sleep_for(std::chrono::milliseconds(5));

	} while (_input.cast() == 0);

	while (_running == true) {
		if (_input.isConnected()) {
			_input.askMSG();
			int x = _input.joystickPotX();
			int enc = _input.encodeur();


			// joystick left/right control
			if (x > _config.joystickCenter + _config.joystickDeadzone) {
				_riviere.deplacerGauche();
				checkloss();
				cout << "Joystick droite:" << x;
			}
			else if (x < _config.joystickCenter - _config.joystickDeadzone) {
				_riviere.deplacerDroite();
				checkloss();
				cout << "Joystick gauche:" << x;
			}

			// encodeur up/down control
			if (enc == -1) {
				_riviere.deplacerBas();
				checkloss();
			}
			else if (enc == 1) {
				_riviere.deplacerHaut();
				checkloss();
			}

			if (!_input.bouton1() || !_input.bouton2() || !_input.bouton3() || !_input.bouton4()) {
				cout << "Bouton appuyé, saut active!" << endl;
				_riviere.deplacerSaut();
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

		
		checkloss();

		std::cout << "\033[H";
		// Réaffiche toute la rivière par-dessus l'ancienne 
		
		if (compteur == compteur_cible) {
			_riviere.update();
			_riviere.printRiviere();

			cout << "Rafraîchissement de la rivière!" << compteur << endl;
			compteur = 0;

			score_bargraph = _riviere.getScore() % 2;
			if ( score_bargraph == 0) {
				val_bargraph += 1;
				_input.writeMSG({ {"BARGRAPH", val_bargraph}});
			}

		}
		

		compteur += 1;
		cout << "Compteur: " << compteur << "/" << compteur_cible << "\r" << flush;
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
