#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#include "world.h"
#include "display.h"

int main(){
	World curWorld;
	curWorld.init(10);

	Display curDisplay = Display(&curWorld);
	curDisplay.init();

	curDisplay.drawFrame();

	sleep(5);

	endwin();
	return 0;
}
