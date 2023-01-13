#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>
#include <memory>

#include "world.h"

class Display{
public:
	static int windowWidth, windowHeight;
	static void resizeHandler(int sig);

	explicit Display(World*);
	Display(const Display&) = delete;
	Display& operator=(const Display&) = delete;
	~Display();

	void drawFrame();
	void init();
	void handleKey(int ch);
private:
	World* world;
	WINDOW* win;
	float curScreenDim[2];
	std::unique_ptr<Ship> player;
};

#endif
