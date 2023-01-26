#include <cmath>

#include "general.h"

void general::rotate2dCoord(float* coords, float rot){
	float tmp[2] = {coords[0]*cos(rot) - coords[1]*sin(rot),
		coords[0]*sin(rot) + coords[1]*cos(rot)};

	coords[0] = tmp[0];
	coords[1] = tmp[1];
}

float general::pointDistance(float* c1, float* c2){
	return sqrt(pow(c1[0] - c2[0], 2) + pow(c1[1] - c2[1], 2));
}
