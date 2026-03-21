#include <iostream>
#include "Riviere.h"
#include "Game.h"
#include "Input.h"
#include "InputConfig.h"
#include <conio.h>
#include <thread>
#include <chrono>

void testInput() {
	InputConfig config = InputConfigManager::load("input_config.json");
	COM_Serial input("COM7");
	if (!input.isConnected()) {
		std::cout << "Input non connecté sur COM3. Mode clavier activé. Appuyez sur q pour quitter.\n";
		while (true) {
			if (_kbhit()) {
				char c = _getch();
				if (c == 'q' || c == 'Q') break;
				std::cout << "Clavier détecté: " << c << "\n";
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		return;
	}

	std::cout << "Input connecté sur COM3. Lecture status precitee...\n";


	int x_status = 0; // -1 left, +1 right
	int y_status = 0; // -1 down, +1 up

	while (true) {
		input.askMSG();
		int x_status= input.joystickPotX();
		int y_status = input.joystickPotY();
		int enc = input.encodeur();
		bool b1 = input.bouton1();
		bool b2 = input.bouton2();
		bool b3 = input.bouton3();
		bool b4 = input.bouton4();
		int castVal = input.cast();

		bool detected = false;
		if (y_status < config.joystickCenter-config.joystickDeadzone) {
			std::cout << "Joystick droite\n";
			detected = true;
		}
		else if (y_status > config.joystickCenter + config.joystickDeadzone) {
			std::cout << "Joystick gauche \n";
			detected = true;
		}
		if (x_status > config.joystickCenter + config.joystickDeadzone) {
			std::cout << "Joystick haut\n";
			detected = true;
		}
		else if (x_status < config.joystickCenter - config.joystickDeadzone) {
			std::cout << "Joystick bas\n";
			detected = true;
		}

		if (!b1) {
			std::cout << "Bouton1 appuyé\n";
			detected = true;
		}
		if (!b2) {
			std::cout << "Bouton2 appuyé\n";
			detected = true;
		}
		if (!b3) {
			std::cout << "Bouton3 appuyé\n";
			detected = true;
		}
		if (!b4) {
			std::cout << "Bouton4 appuyé\n";
			detected = true;
		}

		if (enc == 1) {
			std::cout << "Encodeur mouvement unitaire : +" << enc << "\n";
			detected = true;
		}
		else if (enc == -1) {
			std::cout << "Encodeur mouvement unitaire : -" << enc << "\n";
			detected = true;
		}

		this_thread::sleep_for(std::chrono::milliseconds(5));
		 
	}
	
}

int main() {
	char start = ' ';
	int highScore = 0;

	/*while (start != '2') {
		cout << "WOW!! " << highScore << " est le score � battre!!\n"
				"\n"
				"choisir une option : \n"
				"1 - commencer\n"
				"2 - quitter\n";
		cin >> start;
			if (start == '2')
				break;
			if (start == '1')
			{
				system("cls");
				Game game;
				game.run();
				game.newHighScore(&highScore);
			}
		system("cls");
	}*/

	testInput();

}



