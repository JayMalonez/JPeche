#include "Game.h"
#include <chrono>
#include <thread>

Game::Game() : _riviere() {

}

void Game::run() {
	_riviere.printRiviere();
	while (true) {
		_riviere.update();

		std::cout << "\033[H";
		// Réaffiche toute la rivière par-dessus l’ancienne 
		_riviere.printRiviere();

		this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}
