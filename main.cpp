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
	COM_Serial input("COM3");
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
	int x = input.joystickPotX();
	int y = input.joystickPotY();
	int enc = input.encodeur();
	int b1 = input.bouton1();
	int b2 = input.bouton2();
	int b3 = input.bouton3();
	int b4 = input.bouton4();
	int castVal = input.cast();

	std::cout << "Joystick X=" << x << ", Y=" << y << "\n";
	std::cout << "Encodeur=" << enc << "\n";
	std::cout << "Boutons: 1=" << b1 << ", 2=" << b2 << ", 3=" << b3 << ", 4=" << b4 << "\n";
	std::cout << "Accelerateur (cast)=" << castVal << "\n";

	int x_status = 0; // -1 left, +1 right
	int y_status = 0; // -1 down, +1 up

	if (x < config.joystickLeftLimit()) x_status = -1;
	else if (x > config.joystickRightLimit()) x_status = +1;
	if (y < config.joystickLeftLimit()) y_status = -1;  // Note: using same deadzone for Y, assuming symmetric
	else if (y > config.joystickRightLimit()) y_status = +1;

	bool detected = false;
	if (x_status == -1) {
		std::cout << "Joystick gauche\n";
		detected = true;
	}
	else if (x_status == +1) {
		std::cout << "Joystick droite\n";
		detected = true;
	}
	if (y_status == +1) {
		std::cout << "Joystick haut\n";
		detected = true;
	}
	else if (y_status == -1) {
		std::cout << "Joystick bas\n";
		detected = true;
	}

	if (b1) {
		std::cout << "Bouton1 appuyé\n";
		detected = true;
	}
	if (b2) {
		std::cout << "Bouton2 appuyé\n";
		detected = true;
	}
	if (b3) {
		std::cout << "Bouton3 appuyé\n";
		detected = true;
	}
	if (b4) {
		std::cout << "Bouton4 appuyé\n";
		detected = true;
	}

	if (enc >= config.encoderThreshold) {
		std::cout << "Encodeur mouvement unitaire : +" << enc << "\n";
		detected = true;
	}
	else if (enc <= -config.encoderThreshold) {
		std::cout << "Encodeur mouvement unitaire : " << enc << "\n";
		detected = true;
	}

	if (!detected) {
		std::cout << "Aucun input detectable (joystick neutre, boutons non pressés, encodeur 0).\n";
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



