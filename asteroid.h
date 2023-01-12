#ifndef ASTEROID_H
#define ASTEROID_H

class Asteroid{
public:
	Asteroid(float x, float y, int seed);
	~Asteroid();

	float* getCoords();
	float getBoundingSize();
	float getRadius(float theta);
private:
	float coords[2];
	float rotation;
	int seed;
	float boundSize;
};

#endif
