#ifndef WORLD_HEADER
#define WORLD_HEADER
#include "asteroid.h"
#include "ship.h"

#define WORLD_W 20
#define WORLD_H 20

class World{
public:
	// Function to initalize the world with a specific number of asteroids
	void init(int numAsteroids);

	// Get the asteroids currently in the world
	Asteroid** getAsteroids(int*);

	Ship* placeShip();

	// Cleans up asteroids
	~World();
private:
	Asteroid** asteroids;
	int numAsteroids;
};
#endif
