//Author: Nels Numan
//Stdnr: 1459929
//File: numangomo_board.h
//Description:
//Dit bestand is de header-file voor numangomo_board.cpp
//Compiler: gcc 4.2.1 IDE: Xcode 5.0.2, Mac OS X
//Date: 6 december 2013

#ifndef __Gomoku__gomo_board__
#define __Gomoku__gomo_board__

#include <iostream>
#include <cstdlib>
#include "gomo_stack.h"

//     7 0 1
//     6 - 2
//     5 4 3

struct gomo_board_cell {
public:
	char color;
	gomo_board_cell *neighbors[8];
	gomo_board_cell();
};

class gomo_board {
private:
	gomo_board_cell *entrance;
	void createRow(gomo_board_cell *&upper, gomo_board_cell *&lower);
	void conjoinRows(gomo_board_cell *top, gomo_board_cell *bottom);
	void printHorizontalLine();
	void constructBoard();
	gomo_board_cell *getCell(int x, int y);
    
	int height, width;
	int moveCount;
	char color1, color2;
	char gameMode;
	gomo_stack moves;
    
public:
	gomo_board(int height, int width, char color1, char color2, char gameMode);
	~gomo_board();
	void print();
	void undoMove();
	void simulateCPUgame();
	int getWidth();
	int getHeight();
	char getGameMode();
	bool cpuMove();
	bool humanMove(int x, int y);
	bool colorCell(int x, int y, char color);
	bool detectWinner(int x, int y);
	bool detectTie();
};

#endif /* defined(__Gomoku__gomo_board__) */
