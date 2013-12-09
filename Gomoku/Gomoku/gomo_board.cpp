//Author: Nels Numan
//Stdnr: 1459929
//File: numangomo_board.cpp
//Description:
//In dit bestand staan de klassen: "gomo_board" en "gomo_board_cell"
//Compiler: gcc 4.2.1 IDE: Xcode 5.0.2, Mac OS X
//Date: 6 december 2013

#include "gomo_board.h"

using namespace std;

//Dit is de constructor van de klasse "gomo_board_cell"
gomo_board_cell::gomo_board_cell () {
	for (int i = 0; i < 8; i++) {
		neighbors[i] = NULL;
	}
	color = '-';
}

//Dit is de constructor van de klasse "gomo_board"
gomo_board::gomo_board(int height, int width, char color1, char color2, char gameMode) {
	this->height = height;
	this->width = width;
	this->color1 = color1;
	this->color2 = color2;
	this->gameMode = gameMode;
	moveCount = 0;
	entrance = new gomo_board_cell;
	srand(time(NULL));
	constructBoard();
}

//Dit is de destructor van de klasse "gomo_board". De pointerlijst wordt
//in deze functie afgebroken
gomo_board::~gomo_board() {
	gomo_board_cell *temp = entrance;
	gomo_board_cell *first = NULL;
	gomo_board_cell *help = NULL;
	for (int i = 1; i <= height; i++) {
		first = temp->neighbors[4];
		for (int j = 1; j <= width; j++) {
			help = temp->neighbors[2];
			delete temp;
			temp = help;
		}
		temp = first;
	}
}

//Deze methode returnt een "gomo_board_cell" op basis van coördinaten
gomo_board_cell *gomo_board::getCell(int x, int y) {
	gomo_board_cell *temp = entrance;
	for (int j = 1; j < x; j++) {
		temp = temp->neighbors[2];
	}
	for (int i = 1; i < y; i++) {
		temp = temp->neighbors[4];
	}
	return temp;
}

//Deze methode geeft de breedte van het bord
int gomo_board::getWidth() {
	return width;
}

//Deze methode geeft de hoogte van het bord
int gomo_board::getHeight() {
	return height;
}

//Deze methode maakt de laatste zet van de speler en de computer
//ongedaan
void gomo_board::undoMove() {
	int x, y;
	moves.pop(x, y);
	gomo_board_cell *temp = getCell(x, y);
	temp->color = '-';
	moves.pop(x, y);
	temp = getCell(x, y);
	temp->color = '-';
}

//Deze methode bouwt de pointerstructuur op
void gomo_board::constructBoard() {
	gomo_board_cell *upper = NULL;
	gomo_board_cell *lower = NULL;
	for (int i = 1; i <= height; i++) {
		createRow(upper, lower);
		if (i == 1) {
			entrance = lower;
		}
		else if (i > 1) {
			conjoinRows(upper, lower);
		}
	}
}

//Deze methode wordt gebruikt bij het opbouwen van de pointerstructuur.
//Er wordt een rij van pointers gemaakt
void gomo_board::createRow(gomo_board_cell *&upper, gomo_board_cell *&lower) {
	int j = 0;
	gomo_board_cell *temp;
	temp = new gomo_board_cell;
	temp->neighbors[6] = NULL;
	upper = lower;
	lower = temp;
	for (j = 1; j < width; j++) {
		temp->neighbors[2] = new gomo_board_cell;
		(temp->neighbors[2])->neighbors[6] = temp;
		temp = temp->neighbors[2];
	}
}

//Deze methode wordt gebruikt om twee rijen pointers met elkaar te verbinden
void gomo_board::conjoinRows(gomo_board_cell *upper, gomo_board_cell *lower) {
	for (int i = 1; i <= width; i++) {
		upper->neighbors[3] = lower->neighbors[2];
		upper->neighbors[4] = lower;
		upper->neighbors[5] = lower->neighbors[6];
		lower->neighbors[0] = upper;
		lower->neighbors[1] = upper->neighbors[2];
		lower->neighbors[7] = upper->neighbors[6];
		upper = upper->neighbors[2];
		lower = lower->neighbors[2];
	}
}

//Deze methode kijkt of het maximale aantal zetten van dit specifieke
//spel al is bereikt. Ofwel, het kijken of er gelijkspel is opgetreden
bool gomo_board::detectTie() {
	return ((moveCount == (width * height)) ? true : false);
}

//Deze methode kijkt of in elke richting rondom een vakje of er een
//serie aan vakjes met dezelfde kleur van minimaal zes bestaat.
//Als dit waar is, heeft de speler met de desbetreffende kleur gewonnen
bool gomo_board::detectWinner(int x, int y) {
	gomo_board_cell *start = getCell(x, y);
	gomo_board_cell *temp;
	int counter = 1;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j += 4) {
			temp = start->neighbors[i + j];
			while (temp != NULL && temp->color == start->color) {
				counter++;
				temp = temp->neighbors[i + j];
			}
		}
		if (counter >= 5)
			return true;
		counter = 1;
	}
	return 0;
}

//Deze methode doet een willekeurige zet voor de computer. Deze methode
//returnt true als de computer na deze zet gewonnen heeft.
bool gomo_board::cpuMove() {
	int randomX, randomY;
	bool succesful = false;
	while (!succesful) {
		randomX = rand() % width + 1;
		randomY = rand() % height + 1;
		if ((gameMode == 'c') && (moveCount % 2 == 0)) {
			succesful = colorCell(randomX, randomY, color1);
		}
		else {
			succesful = colorCell(randomX, randomY, color2);
		}
	}
	if (detectWinner(randomX, randomY)) {
		return true;
	}
	moveCount++;
	return false;
}

//Deze methode stuurt de simulatie van het speltype computer tegen computer
//aan.
void gomo_board::simulateCPUgame() {
	bool victory = false;
	int i = 0;
	while (i < (width * height) && !victory) {
		victory = cpuMove();
		print();
		if (moveCount % 2 == 0 && victory) {
			cout << "CPU 1 has won the game in " << moveCount << " turns!" << endl;
			return;
		}
		else if (moveCount % 2 == 1 && victory) {
			cout << "CPU 2 has won the game in " << moveCount << " turns!" << endl;
			return;
		}
		i++;
	}
	cout << "Tie after " << moveCount << " turns!" << endl;
}

//Deze methode kleurt een vakje in op basis van coördinaten en een kleur
bool gomo_board::colorCell(int x, int y, char color) {
	gomo_board_cell *temp = getCell(x, y);
	if (temp->color != '-') {
		return false;
	}
	temp->color = color;
	moves.push(x, y);
	return true;
}

//Deze methode kleurt een vakje in op basis van gegeven coördinaten
bool gomo_board::humanMove(int x, int y) {
	return colorCell(x, y, color1);
	moveCount++;
}

//Deze methode print een horizontale lijn van '+' op het scherm
void gomo_board::printHorizontalLine() {
	cout << ' ';
	for (int i = 0; i < width + 2; i++) {
		cout << '+' << ' ';
	}
	cout << endl;
}

//Deze methode print de huidige stand van het spel op het scherm
void gomo_board::print() {
	gomo_board_cell *temp = entrance;
	gomo_board_cell *help = entrance;
	printHorizontalLine();
	for (int i = 1; i <= height; i++) {
		help = temp;
		cout << " +";
		for (int j = 1; j <= width; j++) {
			cout << " ";
			cout << help->color;
			help = help->neighbors[2];
		}
		cout << " + " << i << endl;
		temp = temp->neighbors[4];
	}
	printHorizontalLine();
	cout << "  ";
	for (int i = 1; i <= width; i++) {
		cout << ' ' << i;
	}
	cout << endl;
}
