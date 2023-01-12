#ifndef DISPLAY_H
#define DISPLAY_H

#include "world.h"
#include <ncurses.h>

class Display{
public:
	static int windowWidth, windowHeight;
	static void resizeHandler(int sig);

	void drawFrame();
	Display(World*);
	void init();
private:
	World* world;
	WINDOW* win;
	float curScreenDim[2];
};

#endif
