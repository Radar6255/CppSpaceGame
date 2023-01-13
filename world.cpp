#define _USE_MATH_DEFINES

#include <iostream>
#include <cstdlib>
#include <memory>
#include <math.h>

#include "world.h"
#include "asteroid.h"
#include "ship.h"

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
		this->asteroids[i] = new Asteroid(randFloat(-WORLD_W / 2, WORLD_W), randFloat(-WORLD_H / 2, WORLD_H), std::rand());
		//std::cout << "X: " << this->asteroids[i].getCoords()[0] << "\n";
	}
}

Ship* World::placeShip(){
	// TODO: Need to check to see if the place that we are putting the ship is not colliding with anything
	std::srand((unsigned) time(NULL));

	return new Ship(randFloat(-WORLD_W / 2, WORLD_W), randFloat(-WORLD_H / 2, WORLD_H), ((float) std::rand() / RAND_MAX) * M_PI);
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
