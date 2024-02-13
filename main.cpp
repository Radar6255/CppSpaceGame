#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <chrono>
#include <thread>

#include "world.h"
#include "display.h"

void gameLoop(Display* disp, World* world){
	// Got help for this from http://jbwyatt.com/ncurses.html#input which is very useful for ncurses programming
	int ch;
	while(true){
		// First need to get keys pressed if any and handle them
		if ((ch = getch()) != ERR){
			// Trying to find if someone hit escape
			if (ch == 27){
				if ((ch = getch()) == ERR){
					break;
				}
			}

			disp->handleKey(ch);
		}


		world->tick();

		// Then we need to render a new frame
		disp->drawFrame();

		// Then we need to wait for some time before displaying the next frame
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}

int main(){
	World curWorld;
	curWorld.init(10);

	Display curDisplay = Display(&curWorld);
	curDisplay.init();

	curDisplay.drawFrame();
	gameLoop(&curDisplay, &curWorld);

	endwin();
	return 0;
}
