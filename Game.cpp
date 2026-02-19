#include "Game.h"

Game::Game() : _riviere() {

}

void Game::run() {
	_riviere.printRiviere();
	while (_running == true) {
		if (_kbhit()) {
			char c = _getch();
			switch (c) {
				case 'd':
					_riviere.deplacerDroite();
					checkloss();
					break;
				case 'a' :
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
		_riviere.update();
		checkloss();

		std::cout << "\033[H";
		// Réaffiche toute la rivière par-dessus l’ancienne 
		_riviere.printRiviere();

		this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}

void Game::checkloss() {
	if (!_riviere.validMove())
	{
		_running = false;
	}
}
