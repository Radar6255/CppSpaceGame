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

void Display::toDisplayCoords(float* input){
	input[0] = input[0] * (Display::windowWidth / this->curScreenDim[0]) + ((float) Display::windowWidth / 2);
	input[1] = input[1] * (Display::windowHeight / this->curScreenDim[1]) + ((float) Display::windowHeight / 2);
}

void Display::drawFrame(){
	int skippedDraws = 0;

	werase(stdscr);
	int numAsteroids;
	Asteroid** asteroids = this->world->getAsteroids(&numAsteroids);

	for (int i = 0; i < numAsteroids; i++){
		// This is the max radius of the asteroid in window coordinates
		float boundSize = asteroids[i]->getBoundingSize();
		float boundWidth = boundSize * (Display::windowWidth / (2 * this->curScreenDim[0]));
		float boundHeight = boundSize * (Display::windowHeight / (2 * this->curScreenDim[1]));

		// Need to clone the coords and translate them according to the player
		float* absCoords = asteroids[i]->getCoords();
		float coords[2] = {absCoords[0] + this->player->getCoords()[0], absCoords[1] + this->player->getCoords()[1]};
		
		// After we have translated of the player position we need to rotate based on the player rotation
		float rot = this->player->getRotation();
		general::rotate2dCoord(coords, rot);

		this->toDisplayCoords(coords);

		mvaddch((int) round((float) Display::windowHeight / 2), (int) round((float) Display::windowWidth / 2), 'O');

		float xCharSize = (float) this->curScreenDim[0] / Display::windowWidth;
		float yCharSize = (float) this->curScreenDim[1] / Display::windowHeight;

		if (coords[0] - boundWidth > Display::windowWidth || coords[0] + boundWidth < 0){
			skippedDraws++;
			continue;
		}
		if (coords[1] - boundHeight > Display::windowHeight || coords[1] + boundHeight < 0){
			skippedDraws++;
			continue;
		}

		for (float x = -boundWidth; x < boundWidth; x += xCharSize){
			// Could change to using this if performance is bad or something
			//wmove(stdscr, y, x);
			//waddch(this->win, 'X');
			for (float y = -boundHeight; y < boundHeight; y += yCharSize){
				int relCoords[2] = {(int) round(coords[0] + (x * (Display::windowWidth / this->curScreenDim[0]))), (int) round(coords[1] + (y * (Display::windowHeight / this->curScreenDim[1])))};
				// First we need to check to see if the point we have is actually a part of the asteroid
				if (sqrt(pow(x, 2) + pow(y, 2)) < asteroids[i]->getRadius(0)){

					mvaddch(relCoords[1], relCoords[0], 'X');
				}
				if (x == -boundWidth && y == -boundHeight){
					//mvaddch(relCoords[1], relCoords[0], '#');
				}

			}
		}
	}
	wmove(stdscr, 0, 0);
	printw("Skipped: %d", skippedDraws);
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
