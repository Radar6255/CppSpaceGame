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
		offset[1] = this->acceleration;
		general::rotate2dCoord(offset, -this->rot);

		this->velocity[0] += offset[0];
		this->velocity[1] += offset[1];
		break;
	case 's':
        // Currently this slows down the ship no matter what direction you are facing
		curSpeed = sqrt(pow(this->velocity[0], 2) + pow(this->velocity[1], 2));

		if (curSpeed < this->acceleration * 0.75){
			this->velocity[0] = 0;
			this->velocity[1] = 0;
			break;
		}

		this->velocity[0] -= this->acceleration * 0.75 * (this->velocity[0] / curSpeed);
		this->velocity[1] -= this->acceleration * 0.75 * (this->velocity[1] / curSpeed);
		break;
	case 'a':
		offset[0] = this->acceleration;
		general::rotate2dCoord(offset, -this->rot);

		this->velocity[0] += offset[0];
		this->velocity[1] += offset[1];
		break;
	case 'd':
		offset[0] = -this->acceleration;
		general::rotate2dCoord(offset, -this->rot);

		this->velocity[0] += offset[0];
		this->velocity[1] += offset[1];
		break;
	case 'q':
		this->rot += 0.1;
		break;
	case 'e':
		this->rot -= 0.1;
		break;

	}
}

void Ship::tick(){
    // Applying the velocity
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
