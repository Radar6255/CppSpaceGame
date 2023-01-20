#ifndef ASTEROID_H
#define ASTEROID_H

#include "updateable.h"

class Asteroid: public Updateable{
//class Asteroid{
public:
	Asteroid(float x, float y, int seed);
	~Asteroid();

	float* getCoords();
	float getBoundingSize();
	float getRadius(float theta);

	void tick();
private:
	float coords[2];
	float rotation;
	int seed;
	float boundSize;
};

#endif
