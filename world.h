#ifndef WORLD_HEADER
#define WORLD_HEADER
#include <vector>

#include "asteroid.h"
#include "ship.h"
#include "updateable.h"

#define WORLD_W 20
#define WORLD_H 20

class World: public Updateable{
//class World{
public:
	// Function to initalize the world with a specific number of asteroids
	void init(int numAsteroids);

	// Get the asteroids currently in the world
	std::vector<Asteroid> getAsteroids();

	Ship* placeShip();

	// Cleans up asteroids
	~World();

	void tick();
private:
	std::vector<Asteroid> asteroids;
	int numAsteroids;
	std::vector<Ship*> ships;
};
#endif
