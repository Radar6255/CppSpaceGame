#ifndef SHIP_H
#define SHIP_H

#include "updateable.h"

class Ship: public Updateable{
//class Ship{
	public:
		float* getCoords();
		float getRotation();
		void handleKey(int ch);
		~Ship();
		Ship(float x, float y, float rot);

		void tick();
	private:
		float coords[2];
		float velocity[2];
		float rot;
		float acceleration;
};

#endif
