#include <iostream>
#include <ncurses.h>
#include <signal.h>
#include <cmath>

#include "world.h"
#include "asteroid.h"
#include "display.h"
#include "general.h"

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
		default:
			this->player->handleKey(ch);
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
		float boundWidth = boundSize / this->curScreenDim[0];
		float boundHeight = boundSize / this->curScreenDim[1];

		// Need to clone the coords and translate them according to the player
		float* absCoords = asteroids[i]->getCoords();
		float coords[2] = {absCoords[0] + this->player->getCoords()[0], absCoords[1] + this->player->getCoords()[1]};
		
		// After we have translated of the player position we need to rotate based on the player rotation
		float rot = this->player->getRotation();
		general::rotate2dCoord(coords, rot);

		// Need to translate the coordinates to get us to the middle of the screen
		coords[0] = coords[0] + ((float) this->curScreenDim[0] / 2);
		coords[1] = coords[1] + ((float) this->curScreenDim[1] / 2);

		mvaddch((int) round((float) Display::windowHeight / 2), (int) round((float) Display::windowWidth / 2), 'O');

		for (float x = -boundWidth; x < boundWidth; x += (float) this->curScreenDim[0] / Display::windowWidth){
			// Could change to using this if performance is bad or something
			//wmove(stdscr, y, x);
			//waddch(this->win, 'X');
			for (float y = -boundHeight; y < boundHeight; y += (float) this->curScreenDim[1] / Display::windowHeight){
				// First we need to check to see if the point we have is actually a part of the asteroid
				//std::cout << sqrt(pow(x, 2) + pow(y, 2)) << " ";
				if (sqrt(pow(x * this->curScreenDim[0], 2) + pow(y * this->curScreenDim[1], 2)) < asteroids[i]->getRadius(0)){
					int relCoords[2] = {
						(int) round(Display::windowWidth * ((coords[0] + x) / this->curScreenDim[0])),
						(int) round(Display::windowHeight * ((coords[1] + y) / this->curScreenDim[1]))
					};

					mvaddch(relCoords[1], relCoords[0], 'X');
				}

			}
		}
	}
	wrefresh(stdscr);
}

void Display::init(){
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);

	resizeHandler(0);

	this->curScreenDim[0] = 20;
	this->curScreenDim[1] = 11.25;

	// Need to generate the ship that the display is following
	this->player = std::unique_ptr<Ship>(this->world->placeShip());

	//std::cout << "Finished generating ship\n";

	signal(SIGWINCH, this->resizeHandler);
}

Display::~Display(){
	std::cout << "Deconstucting display\n";
}
