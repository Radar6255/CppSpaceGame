#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>
#include <memory>

#include "world.h"
#include "debug.h"

class Display{
public:
	static int windowWidth, windowHeight;
	static void resizeHandler(int sig);
	static Debug debug;

	explicit Display(World*);
	Display(const Display&) = delete;
	Display& operator=(const Display&) = delete;
	~Display();

	void drawFrame();
	void init();
	void handleKey(int ch);
private:
	void toDisplayCoords(float* input);

	World* world;
	WINDOW* win;
	float curScreenDim[2];
	std::unique_ptr<Ship> player;
};

#endif
