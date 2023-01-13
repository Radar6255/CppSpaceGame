#include <iostream>
#include <ncurses.h>
#include <signal.h>
#include <cmath>

#include "world.h"
#include "asteroid.h"
#include "display.h"

Display::Display(World* world){
	this->world = world;
}

int Display::windowWidth;
int Display::windowHeight;

void Display::resizeHandler(int sig){
	int nh, nw;
	getmaxyx(stdscr, nh, nw);

	Display::windowWidth = nw;
	Display::windowHeight = nh;
}

void Display::handleKey(int ch){
	switch(ch){
		case 'z':
			this->curScreenDim[0] = this->curScreenDim[0] * 0.95;
			this->curScreenDim[1] = this->curScreenDim[1] * 0.95;
			break;
		case 'x':
			this->curScreenDim[0] = this->curScreenDim[0] * 1.05;
			this->curScreenDim[1] = this->curScreenDim[1] * 1.05;
			break;
	}
}

void Display::drawFrame(){
	werase(stdscr);
	int numAsteroids;
	Asteroid** asteroids = this->world->getAsteroids(&numAsteroids);

	for (int i = 0; i < numAsteroids; i++){
		// This is the max radius of the asteroid in window coordinates
		float boundSize = asteroids[i]->getBoundingSize();
		float boundWidth = boundSize / this->curScreenDim[0] / 2;
		float boundHeight = boundSize / this->curScreenDim[1] / 2;

		float* coords = asteroids[i]->getCoords();

		for (float x = -boundWidth; x < boundWidth; x += (float) this->curScreenDim[0] / Display::windowWidth){
			// Could change to using this if performance is bad or something
			//wmove(stdscr, y, x);
			//waddch(this->win, 'X');
			for (float y = -boundHeight; y < boundHeight; y += (float) this->curScreenDim[1] / Display::windowHeight){
				// First we need to check to see if the point we have is actually a part of the asteroid
				if (sqrt(pow(x, 2) + pow(y, 2)) < asteroids[i]->getRadius(0)){
					int relCoords[2] = {
						(int) round(Display::windowWidth * ((coords[0] + x + 10) / this->curScreenDim[0])),
						(int) round(Display::windowHeight * ((coords[1] + y + 10) / this->curScreenDim[1]))
					};

					mvaddch(relCoords[1], relCoords[0], 'X');
				}

			}
		}
	}
	wrefresh(stdscr);
}

void Display::init(){
	this->curScreenDim[0] = 20;
	this->curScreenDim[1] = 11.25;

	initscr();
	cbreak();
	noecho();

	resizeHandler(0);
	//this->win = newwin(Display::windowHeight, Display::windowWidth, 1, 1);

	signal(SIGWINCH, this->resizeHandler);
}
