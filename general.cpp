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

void general::vectorNorm(float* in, float* out){
	out[0] = -in[1];
	out[1] = in[0];
}

void general::makeUnitVector(float* in, float* out){
	float mag = pointDistance(in, in);

	out[0] = in[0] / mag;
	out[1] = in[1] / mag;
}

void general::solveSystem(float a, float b, float c, float out[2]){
	float rad = sqrt(pow(b, 2) - (4 * a * c));

	out[0] = (-b + rad) / (2 * a);
	out[1] = (-b - rad) / (2 * a);
}
