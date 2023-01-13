#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#include "world.h"
#include "display.h"

void gameLoop(Display* disp){
	// Got help for this from http://jbwyatt.com/ncurses.html#input which is very useful for ncurses programming
	int ch;
	while(true){
		// First need to get keys pressed if any and handle them
		if ((ch = getch()) == ERR){
			continue;
		} else {
			// Trying to find if someone hit escape
			if (ch == 27){
				if ((ch = getch()) == ERR){
					break;
				}
			}

			disp->handleKey(ch);
		}

		// Then we need to render a new frame... Actually we can probably get away with only doing this after an update or key press
		disp->drawFrame();
	}
}

int main(){
	World curWorld;
	curWorld.init(10);

	Display curDisplay = Display(&curWorld);
	curDisplay.init();

	curDisplay.drawFrame();
	gameLoop(&curDisplay);

	endwin();
	return 0;
}
