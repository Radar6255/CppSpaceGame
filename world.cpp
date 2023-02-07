#define _USE_MATH_DEFINES

#include <iostream>
#include <cstdlib>
#include <memory>
#include <math.h>

#include "world.h"
#include "asteroid.h"
#include "ship.h"
#include "general.h"

float randFloat(int min, int range){
	return ((float) std::rand() / RAND_MAX) * range + min;
}

void World::init(int numAsteroids){
	this->numAsteroids = numAsteroids;

	std::srand((unsigned) time(NULL));

	// Need to generate and store the asteroids
	// Currently we can't do this but in the future it might be nice to do
	for (int i = 0; i < numAsteroids; i++){
		while(true){
			float x = randFloat(-WORLD_W / 2, WORLD_W);
			float y = randFloat(-WORLD_H / 2, WORLD_H);
			float coords[2] = {x, y};
			int radius = std::rand() % 4;

			bool collision = false;
			//for(std::vector<Asteroid>::iterator asteroid = this->asteroids.begin(); asteroid != this->asteroids.end(); asteroid++){
			for(Asteroid* asteroid: this->asteroids){
				if (radius + asteroid->getBoundingSize() > general::pointDistance(coords, asteroid->getCoords())){
					collision = true;
					break;
				}
			}
			if (collision){
				continue;
			}
			this->asteroids.push_back(new Asteroid(x, y, radius, std::rand()));
			//this->asteroids.push_back(Asteroid(x, y, radius, std::rand()));
			this->updates.push_back(this->asteroids[this->asteroids.size() - 1]);
			//std::cout << "X: " << this->asteroids[i].getCoords()[0] << "\n";
			break;
		}
	}
}

Ship* World::placeShip(){
	// TODO: Need to check to see if the place that we are putting the ship is not colliding with anything
	std::srand((unsigned) time(NULL));

	this->ships.push_back(new Ship(randFloat(-WORLD_W / 2, WORLD_W), randFloat(-WORLD_H / 2, WORLD_H), ((float) std::rand() / RAND_MAX) * 2 * M_PI));
	return this->ships.back();
}

World::~World(){
	for(Asteroid* asteroid: this->asteroids){
		delete asteroid;
	}
	this->asteroids.clear();

	/*
	for(std::vector<Ship*>::iterator ship = this->ships.begin(); ship != this->ships.end(); ship++){
		delete *ship;
	}
	this->ships.clear();
	*/
}

std::vector<Asteroid*> World::getAsteroids(){
	return this->asteroids;
}


void World::doCollisions(){
	long numCollisions = 0;
	for (unsigned long a = 0; a < this->asteroids.size(); a++){
		// Only need to do collisions on the asteroids that haven't been checked together before
		for (unsigned long b = a + 1; b < this->asteroids.size(); b++){
			if (this->asteroids[a]->checkCollision(this->asteroids[b])){
				numCollisions++;
				float* aPos = this->asteroids[a]->getCoords();
				float* bPos = this->asteroids[b]->getCoords();

				// I also need the asteroid velocities so I can tell how they were moving
				float* aVelocity = this->asteroids[a]->getVelocity();
				float* bVelocity = this->asteroids[b]->getVelocity();

				float aSize = this->asteroids[a]->getBoundingSize();
				float bSize = this->asteroids[b]->getBoundingSize();

				// Trying to solve the problem of when the distance between the asteroids is equal to their radius'
				float a = pow(aVelocity[0] - bVelocity[0], 2) + pow(aVelocity[1] - bVelocity[1], 2);
				float b = 2 * ((aVelocity[0] - bVelocity[0])*(aPos[0] - bPos[0]) + (aVelocity[1] - bVelocity[1])*(aPos[1] - bPos[1]));
				float c = pow(aPos[0] - bPos[0], 2) + pow(aPos[1] - bPos[1], 2) - pow(aSize + bSize, 2);

				float out[2];
				general::solveSystem(a, b, c, out);

				// After this we have two collision t values
				// We need to find out which is correct in this case... Actually it should always be the smaller t value
				float t;
				if (!isnan(out[0]) && out[0] < out[1]){
					t = out[0];
				} else {
					t = out[1];
				}

				if (!isnan(t)){
					aPos[0] = t * aVelocity[0] + aPos[0];
					aPos[1] = t * aVelocity[1] + aPos[1];

					bPos[0] = t * bVelocity[0] + bPos[0];
					bPos[1] = t * bVelocity[1] + bPos[1];

					float aMass = 1;
					float bMass = 1;

					// TODO Need to adjust the velocities of the asteroids
					float d = aSize + bSize;
					float nx = (bPos[0] - aPos[0]) / d;
					float ny = (bPos[1] - aPos[1]) / d;

					float p = (2 * (aVelocity[0] * nx + aVelocity[1] * ny - bVelocity[0] * nx - bVelocity[1] * ny)) / (aMass + bMass);

					//aVelocity[0] = aVelocity[0] - p * aMass * nx;
					//aVelocity[1] = aVelocity[1] - p * aMass * ny;

					//bVelocity[0] = bVelocity[0] - p * bMass * nx;
					//bVelocity[1] = bVelocity[1] - p * bMass * ny;
				}
				// Might want to see how many collisions we get that have no valid intersection
			}
			//printf("Collisions: %ld", numCollisions);
		}
	}
}

void World::tick(){
	for(std::vector<Ship*>::iterator ship = this->ships.begin(); ship != this->ships.end(); ship++){
		(*ship)->tick();
	}

	for(Updateable* update: this->updates){
		update->tick();
	}

	// After we do movement we want to correct any collisions that happened
	this->doCollisions();
}
