#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

#include "ship.h"
#include "general.h"

float* Ship::getCoords(){
	return this->coords;
}

float Ship::getRotation(){
	return this->rot;
}

void Ship::handleKey(int ch){
	float offset[2] = {0, 0};
	switch(ch){
	case 'w':
		//offset[0] = 1;
		offset[1] = 0.4;
		general::rotate2dCoord(offset, -this->rot);

		this->coords[0] += offset[0];
		this->coords[1] += offset[1];
		break;
	case 's':
		offset[0] = -1;
		general::rotate2dCoord(offset, this->rot);

		this->coords[0] += offset[0];
		this->coords[1] += offset[1];
		break;
	case 'a':
		this->rot += 0.1;
		break;
	case 'd':
		this->rot -= 0.1;
		break;
	}
}

Ship::~Ship(){
	std::cout << "Deconstructing ship\n";
}

Ship::Ship(float x, float y, float rot){
	this->coords[0] = x;
	this->coords[1] = y;

	//this->rot = rot;
	this->rot = 0;
}
