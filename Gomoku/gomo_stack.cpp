//Author: Nels Numan
//Stdnr: 1459929
//File: numangomo_stack.cpp
//Description:
//In dit bestand staan de klassen: "gomo_stack" en "gomo_stack_element"
//Compiler: gcc 4.2.1 IDE: Xcode 5.0.2, Mac OS X
//Date: 6 december 2013

#include <cstdlib>
#include "gomo_stack.h"

using namespace std;

//Dit is de constructor van "gomo_stack_element"
gomo_stack_element::gomo_stack_element() {
	x = NULL;
	y = NULL;
}

//Deze methode zet een nieuw element op de stapel
void gomo_stack::push(int x, int y) {
	gomo_stack_element *temp = new gomo_stack_element;
	temp->x = x;
	temp->y = y;
	temp->next = top;
	top = temp;
}

//Deze methode haalt het bovenste element van de stapel
//en returnt deze met behulp van 'call by reference' variabelen
void gomo_stack::pop(int &x, int &y) {
	if (!empty()) {
		gomo_stack_element *temp = top;
		x = top->x;
		y = top->y;
		top = top->next;
		delete temp;
	}
}

//Deze methode kijkt of de stapel op het moment leeg is
bool gomo_stack::empty() {
	return ((top == NULL) ? true : false);
}
