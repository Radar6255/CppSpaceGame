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
	float curSpeed;
	switch(ch){
	case 'w':
		//offset[0] = 1;
		offset[1] = this->acceleration;
		general::rotate2dCoord(offset, -this->rot);

		//this->coords[0] += offset[0];
		//this->coords[1] += offset[1];
		this->velocity[0] += offset[0];
		this->velocity[1] += offset[1];
		break;
	case 's':
		//offset[0] = -1;
		curSpeed = sqrt(pow(this->velocity[0], 2) + pow(this->velocity[1], 2));
		//general::rotate2dCoord(offset, this->rot);

		//this->coords[0] += offset[0];
		//this->coords[1] += offset[1];
		this->velocity[0] -= this->acceleration * 0.75 / curSpeed * this->velocity[0];
		this->velocity[1] -= this->acceleration * 0.75 / curSpeed * this->velocity[1];
		break;
	case 'a':
		this->rot += 0.1;
		break;
	case 'd':
		this->rot -= 0.1;
		break;
	}
}

void Ship::tick(){
	this->coords[0] += this->velocity[0];
	this->coords[1] += this->velocity[1];
}

Ship::~Ship(){
	std::cout << "Deconstructing ship\n";
}

Ship::Ship(float x, float y, float rot){
	this->coords[0] = x;
	this->coords[1] = y;

	this->velocity[0] = 0;
	this->velocity[1] = 0;

	this->rot = rot;
//	this->rot = 0;
	this->acceleration = 0.004;
}
