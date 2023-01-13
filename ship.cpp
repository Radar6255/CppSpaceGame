#include <iostream>

#include "ship.h"

float* Ship::getCoords(){
	return this->coords;
}

void Ship::handleKey(int ch){
	switch(ch){
	case 'w':
		// TODO Need to move forward in relation to the current rotation
		break;
	case 'a':
		this->rot -= 0.1;
		break;
	case 'd':
		this->rot += 0.1;
		break;
	}
}

Ship::~Ship(){
	std::cout << "Deconstructing ship\n";
}

Ship::Ship(float x, float y, float rot){
	this->coords[0] = x;
	this->coords[1] = y;

	this->rot = rot;
}
