#ifndef _RECTANGLE_
#define _RECTANGLE_

#include "position.hpp"

class Rect{
public:
	Rect() : Rect(0, 0){}

	Rect(int w, int h){
		this->w = w;
		this->h = h;
	}

	bool isInside(Position& at, Position& test)const{
		return ((test.x > at.x && test.x < at.x + w) && (test.y > at.y && test.y < at.y + h));
	}

	int w, h;
};

#endif