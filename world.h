#ifndef WORLD_H
#define WORLD_H
#include "asteroid.h"

class World{
public:
	void init(int numAsteroids);
	Asteroid** getAsteroids(int*);
	~World();
private:
	Asteroid** asteroids;
	int numAsteroids;
};
#endif
