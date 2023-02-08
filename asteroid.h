#ifndef ASTEROID_H
#define ASTEROID_H

#include "updateable.h"

class Asteroid: public Updateable{
//class Asteroid{
public:
	Asteroid(float x, float y, float maxRadius, int seed);
	~Asteroid();

	float* getCoords();
	float* getVelocity();
	float getBoundingSize();
	float getRadius(float theta);
	float getMass();

	bool checkCollision(Asteroid* asteroid);

	void tick();
private:
	float coords[2];
	float velocity[2];
	float density;
	float rotation;

	int seed;
	float boundSize;
};

#endif
