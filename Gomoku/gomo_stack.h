//Author: Nels Numan
//Stdnr: 1459929
//File: numangomo_board.h
//Description:
//Dit bestand is de header-file voor numangomo_stack.cpp
//Compiler: gcc 4.2.1 IDE: Xcode 5.0.2, Mac OS X
//Date: 6 december 2013

#ifndef __Gomoku__gomo_stack__
#define __Gomoku__gomo_stack__

#include <iostream>

struct gomo_stack_element {
public:
	gomo_stack_element *next;
	int x, y;
	gomo_stack_element();
};

class gomo_stack {
private:
	gomo_stack_element *top;
public:
	void push(int x, int y);
	void pop(int &x, int &y);
	bool empty();
};

#endif /* defined(__Gomoku__gomo_stack__) */
