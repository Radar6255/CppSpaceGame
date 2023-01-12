#include <iostream>
#include <cstdlib>
#include <memory>

#include "world.h"
#include "asteroid.h"

float randFloat(int min, int range){
	return ((float) std::rand() / RAND_MAX) * range + min;
}

void World::init(int numAsteroids){
	this->numAsteroids = numAsteroids;
	this->asteroids = new Asteroid*[numAsteroids];

	std::srand((unsigned) time(NULL));

	// Need to generate and store the asteroids
	// TODO: Make sure that these don't overlap or collide with each other...
	// Currently we can't do this but in the future it might be nice to do
	for (int i = 0; i < numAsteroids; i++){
		this->asteroids[i] = new Asteroid(randFloat(-10, 20), randFloat(-10, 20), std::rand());
		//std::cout << "X: " << this->asteroids[i].getCoords()[0] << "\n";
	}
}

World::~World(){
	for (int i = 0; i < this->numAsteroids; i++){
		delete this->asteroids[i];
	}
	delete[] this->asteroids;
}

Asteroid** World::getAsteroids(int* size){
	*size = this->numAsteroids;
	return this->asteroids;
}
