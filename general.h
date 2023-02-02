#ifndef GENERAL_H
#define GENERAL_H

namespace general{
	void rotate2dCoord(float* coords, float rot);
	float pointDistance(float* c1, float* c2);
	void vectorNorm(float* in, float* out);
	void makeUnitVector(float* in, float* out);
	void solveSystem(float a, float b, float c, float out[2]);
}

#endif
