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

Asteroid::Asteroid(float x, float y, float maxRadius, int seed){
	this->coords[0] = x;
	this->coords[1] = y;
	this->seed = seed;

	// Going to use the seed to generate 1D perlin noise to get the shape of the asteroid at some point
	// Should generate the array used for perlin noise in the constructor so we don't need to use the seed again
	std::srand(seed);

	this->boundSize = maxRadius;
}

void Asteroid::tick(){
	// TODO Need to apply velocity here
	std::cout << "Test";
}

// TODO Make this use 1D perlin noise to generate smooth but varied shaped asteroids
float Asteroid::getRadius(float theta){
	return this->boundSize;
}

Asteroid::~Asteroid(){
	//std::cout << "Deallocating asteroid\n";
}
