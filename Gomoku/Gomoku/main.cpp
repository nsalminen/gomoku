//Author: Nels Numan
//Stdnr: 1459929
//File: numanmain.cpp
//Description:
//Dit bestand geeft instructies aan klassen en stuurt daarmee
//het programma aan.
//Compiler: gcc 4.2.1 IDE: Xcode 5.0.2, Mac OS X
//Date: 6 december 2013

#include <iostream>
#include <cstdlib>
#include "gomo_board.h"

using namespace std;

//Deze methode vraagt de coördinaten aan de gebruiker, die gebruikt
//zijn bij het kleuren van een vakje.
void requestCoords(int &x, int &y, int width, int height) {
	x = y = -1;
	while (y <0 || y> height) {
		cout << "Please enter a row number: ";
		cin >> y;
	}
	while (x <0 || x> width) {
		cout << "Please enter a column number: ";
		cin >> x;
	}
}

//Deze methode is het menu voor de gebruiker en wordt aangeroepen
//wanneer het speltype speler tegen computer is.
void mainMenu(gomo_board &gomo) {
	char choice;
	int x, y;
	int width = gomo.getWidth();
	int height = gomo.getHeight();
	do {
		gomo.print();
		cout << "Menu: [C]color cell, [U]undo, [Q]quit" << endl;
		cin >> choice;
		switch (char(tolower(choice))) {
			case 'q':
				cout << "Quiting..." << endl;
				break;
                
			case 'c':
				requestCoords(x, y, width, height);
				gomo.humanMove(x, y);
				if (gomo.cpuMove()) {
					cout << "CPU has won the game!" << endl;
					choice = 'q';
				}
				else if (gomo.detectWinner(x, y)) {
					cout << "You have won the game!" << endl;
					choice = 'q';
				}
				else if (gomo.detectTie()) {
					cout << "The game is tied!" << endl;
					choice = 'q';
				}
				break;
                
			case 'u':
				gomo.undoMove();
				break;
                
			default:
				cout << "Unknown input..." << endl;
		}
	}
	while (choice != 'q');
}

//Deze methode vraagt de gewenste dimensies van het veld aan de gebruiker,
//die gebruikt zijn bij het instantiëren van het spel.
void requestDimensions(int &height, int& width) {
	while (width < 0 || width > 50) {
		cout << "Enter the width of the board (< 50): ";
		cin >> width;
	}
	while (height < 0 || height > 50) {
		cout << "Enter the height of the board (< 50): ";
		cin >> height;
	}
}

//Deze methode vraagt het gewenste speltype van het spel aan de gebruiker,
//die gebruikt zijn bij het instantiëren van het spel.
void requestGameMode(char &mode, char &color1, char &color2) {
	char colorChoice = '\0';
	cout << "Enter 'H' for a Human vs CPU game,";
	cout << "or 'C' for a CPU vs CPU game: ";
	cin >> mode;
	if (char(tolower(mode)) == 'h') {
		while (colorChoice != '1' && colorChoice != '2') {
			cout << "Choose a color. Type '1' for * and '2' for #: ";
			cin >> colorChoice;
		}
		if (colorChoice == '2') {
			color1 = '#';
			color2 = '*';
			cout << "lala" << endl;
		}
	}
}

//Deze methode zorgt ervoor dat alle methodes worden aangeroepen voor het
//achterhalen van de informatie die gebruikt wordt voor het spel.
void gameSetup() {
	int width = -1;
	int height = -1;
	char mode;
	char color1 = '*';
	char color2 = '#';
	requestDimensions(height, width);
	requestGameMode(mode, color1, color2);
	gomo_board gomo(height, width, color1, color2, mode);
	if (mode == 'h') {
		mainMenu(gomo);
	}
	else if (mode == 'c') {
		gomo.simulateCPUgame();
	}
}

//Deze methode print het logo van het programma
void printLogo() {
	cout << "   ____                       _" << endl;
	cout << "  / ___| ___  _ __ ___   ___ | | ___   _" << endl;
	cout << " | |  _ / _ \\| '_ ` _ \\ / _ \\| |/ / | | |" << endl;
	cout << " | |_| | (_) | | | | | | (_) |   <| |_| |" << endl;
	cout << "  \\____|\\___/|_| |_| |_|\\___/|_|\\_\\\\__,_|" << endl << endl;
}

//Deze methode print het 'infoblokje' van het programma
void printInfo() {
	cout << "Author: Nels Numan" << endl;
	cout << "Stdnr: 1459929" << endl;
	cout << "Description:" << endl;
	cout << "Dit bestand geeft instructies aan klassen en stuurt daarmee" << endl;
	cout << "het programma aan." << endl;
	cout << "Compiler: gcc 4.2.1 IDE: Xcode 5.0.2, Mac OS X" << endl;
	cout << "Date: 6 december 2013" << endl;
}

int main(int argc, const char *argv[]) {
	printInfo();
	printLogo();
	gameSetup();
	return 0;
}
