#include <iostream>
#include "Riviere.h"
#include "Game.h"

int main()
{
char start = ' ';
int highScore = 0;
	while (start != '2')
	{
		cout << "WOW!! " << highScore << " Est le score a battre!!\n"
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
	}

}
