#include "debug.h"

#include <map>
#include <ncurses.h>

Debug::Debug(){

}

void Debug::setValue(std::string key, float val){
	this->values[key] = val;
	/*if (this->values.find(key) != this->values.end()){

	} else {
	}*/
}

void Debug::draw(){
	wmove(stdscr, 0, 0);
	for (std::pair<std::string, float> pair: this->values){
		printw("%s: %f, ", pair.first.c_str(), pair.second);
	}
	wrefresh(stdscr);
}
