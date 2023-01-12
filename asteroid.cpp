#include <iostream>
#include <cstdlib>
#include "asteroid.h"

// Get the current coords of this asteroid
// Warning this is not a clone of the coords so modifications will affect real coords
float* Asteroid::getCoords(){
	return coords;
}

float Asteroid::getBoundingSize(){
	return this->boundSize;
}

Asteroid::Asteroid(float x, float y, int seed){
	this->coords[0] = x;
	this->coords[1] = y;
	this->seed = seed;

	// Going to use the seed to generate 1D perlin noise to get the shape of the asteroid at some point
	// Should generate the array used for perlin noise in the constructor so we don't need to use the seed again
	std::srand(seed);

	// TODO Get this to be accurate
	this->boundSize = (std::rand() % 7) + 3;
}

float Asteroid::getRadius(float theta){
	return this->boundSize;
}

Asteroid::~Asteroid(){
	//std::cout << "Deallocating asteroid\n";
}
