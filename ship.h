#ifndef SHIP_H
#define SHIP_H

class Ship{
	public:
		float* getCoords();
		float getRotation();
		void handleKey(int ch);
		~Ship();
		Ship(float x, float y, float rot);
	private:
		float coords[2];
		float rot;
};

#endif
