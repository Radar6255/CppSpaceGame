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
		for (unsigned long b = a; b < this->asteroids.size(); b++){
			if (this->asteroids[a]->checkCollision(this->asteroids[b])){
				numCollisions++;
				// TODO We are going to have to deal this this problem
				// Don't need to store the old velocity if we just have both asteroids go backwards until they don't collide any longer
				float* aPos = this->asteroids[a]->getCoords();
				float* bPos = this->asteroids[b]->getCoords();

				// I also need the asteroid velocities so I can tell how they were moving
				float* aVelocity = this->asteroids[a]->getVelocity();
				float* bVelocity = this->asteroids[b]->getVelocity();

				float aNorm[2];
				float bNorm[2];

				// Finding the normal which will point us in the direction of the point of contact on the asteroid
				general::vectorNorm(aVelocity, aNorm);
				general::vectorNorm(bVelocity, bNorm);

				general::makeUnitVector(aNorm, aNorm);
				general::makeUnitVector(bNorm, bNorm);

				float aSize = this->asteroids[a]->getBoundingSize();
				float bSize = this->asteroids[b]->getBoundingSize();

				aNorm[0] = aNorm[0] * aSize;
				aNorm[1] = aNorm[1] * aSize;
				bNorm[0] = bNorm[0] * bSize;
				bNorm[1] = bNorm[1] * bSize;

				// Finding the slopes of the flight path from the velocity
				float ma = aVelocity[1] / aVelocity[0];
				float mb = bVelocity[1] / bVelocity[0];

				// Finding the y intercept of the flight path
				float ba = (aPos[1] + aNorm[1]) - ma * (aPos[0] + aNorm[0]);
				float bb = (bPos[1] + bNorm[1]) - mb * (bPos[0] + bNorm[0]);

				// Finding where the flight paths intercept
				float interceptX = (bb - ba) / (ma - mb);
				if (ma - mb == 0){
					continue;
				}
				float interceptY = interceptX * ma + ba;

				aPos[0] = interceptX - aNorm[0];
				aPos[1] = interceptY - aNorm[1];

				bPos[0] = interceptX - bNorm[0];
				bPos[1] = interceptY - bNorm[1];

				//printf("%f, %f\n", aPos[0], aPos[1]);
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
