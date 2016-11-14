#include <stdlib.h>
#include "Image.h"
#include <algorithm>
#include "Tile.h"
#include <string>
#include <iostream>
#include "Element.h"
#include "Texture.h"
#ifndef Tilemap_H
#define Tilemap_H
#define NORTH 1
#define EAST 2
#define WEST 3
#define SOUTH 4
#define NORTHEAST 5
#define SOUTHEAST 6
#define NORTHWEST 7
#define SOUTHWEST 8
#define GAME_WIN 2
#define GAME_LOSS 1
#define GAME_RUNNING 0
#define INIT_NUMBER_OF_CLICKS 2
GLuint BOMB_TEXTURE = 2;
GLuint CHEST_TEXTURE = 3;

int tileSelectedX;
int tileSelectedY;
int tileSelected;
int GAME_STATE = 0;

class Tilemap {
public:
	Tilemap() {

	}
	Tilemap(int gameWidth, int gameHeight) {
		this->gameWidth = gameWidth;
		this->gameHeight = gameHeight;
		loadCharacter();
		loadExplosion();
		explosion.setState(1);
		numberOfClicks = INIT_NUMBER_OF_CLICKS;
		outOfBounds = 0;
	}
	void loadCharacter() {
		Element character();
	}
	void loadExplosion() {
		Element explosion();
	}

	void drawRect(float x, float y, float w, float h){
		glTexCoord2f(0, 0);
		glVertex2d(x, y);
		glTexCoord2f(0, 1);
		glVertex2d(x, y + h);
		glTexCoord2f(1, 1);
		glVertex2d(x + w, y + h);
		glTexCoord2f(1, 0);
		glVertex2d(x + w, y);
	}

	void drawTile(float x, float y, float w, float h) {

		glTexCoord2f(0, 0);
		glVertex2d(x, y);
		glTexCoord2f(0, 1);
		glVertex2d(x + w / 2, y - h / 2);
		glTexCoord2f(1, 1);
		glVertex2d(x, y - h);
		glTexCoord2f(1, 0);
		glVertex2d(x - w / 2, y - h / 2);

	}
	int drawMap() {
		int x = gameWidth / 2 - (getTile(0).getWidth() / 2);
		int y = gameHeight;
		setStartCoords(x, y);
		int screenx = 0;
		int screeny = 0;
		int cont = 0;
		int multiplier = 1;
		int n = sqrt(getSize());
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				screenx = x + (j - i) * (getTile(0).getWidth() / 2);
				screeny = y - (j + i) * (getTile(0).getHeight() / 2);
				int tilew = getTile(cont).getWidth();
				int tileh = getTile(cont).getHeight();
				if (getTile(cont).isVisible()) {
					glBindTexture(GL_TEXTURE_2D, getTile(cont).getTextura());
				}
				else {
					glBindTexture(GL_TEXTURE_2D, textures.getIds()[0]);
				}
				glBegin(GL_QUADS);
				drawTile(screenx + tilew / 2, screeny, tilew, tileh);
				glEnd();
				cont++;
			}
		}
		if (tiles[tileSelected].getTextura() == BOMB_TEXTURE) {
			character.setTexture(12);
			drawExplosion();
			GAME_STATE = GAME_LOSS;
		}
		else if (tiles[tileSelected].getTextura() == CHEST_TEXTURE) {
			GAME_STATE = GAME_WIN;
		}
		drawCursors();
		drawCharacter();
		return GAME_STATE;
	}
	void setTextures(Texture textures) {
		this->textures = textures;
	}
	void explode(){

		int state = explosion.getState();
		if (state > 15) {
			state = 15;
		}
		explosion.setState(++state);
	}
	void drawExplosion() {
		int state = explosion.getState();
		int x = tileSelectedX - 50;
		int y = starty - tileSelectedY - 25;
		int w = 100;
		int h = 100;
		double coordy = ((state - 1) / 4)*0.25;
		double coordx = ((state - 1) % 4)*0.25;
		glBindTexture(GL_TEXTURE_2D, 14);
		glBegin(GL_QUADS);
		glTexCoord2f(coordx, coordy);
		glVertex2d(x, y);
		glTexCoord2f(coordx, coordy + 0.25);
		glVertex2d(x, y + h);
		glTexCoord2f(coordx + 0.25, coordy + 0.25);
		glVertex2d(x + w, y + h);
		glTexCoord2f(coordx + 0.25, coordy);
		glVertex2d(x + w, y);
		glEnd();
	}
	Tile getTile(int index) {
		return tiles[index];
	}
	void setStartCoords(double startx, double starty) {
		this->startx = startx;
		this->starty = starty;
	}
	void setSize(int size) {
		this->size = size;
		tiles = new Tile[size];
	}

	void setTiles(float w, float h) {
		for (int i = 0; i < size; i++) {
			GLuint *a = textures.getIds();
			Tile tile(w, h, textures.getIds()[rand()%2]);
			tiles[i] = tile;
		}
		setToCenterTile();
		setTreasure();
		tiles[size / 2].setTexture(textures.getIds()[0]);
	}
	void setTreasure() {
		int tilenumber;
		do {
			tilenumber = rand() % size;
		} while (tilenumber == size / 2);
		tiles[rand() % size].setTexture(textures.getIds()[2]);
	
	}
	void setToCenterTile() {
		tileSelectedX = tiles[0].getWidth() * (sqrt(size) / 2);
		tileSelectedY = tiles[0].getHeight() * (sqrt(size) / 2);
		tileSelected = size / 2;
		tiles[size / 2].setVisited();
	}

	void drawCharacter(){
		glBindTexture(GL_TEXTURE_2D, character.getTexture());
		glBegin(GL_QUADS);
		drawRect(tileSelectedX - 30, starty - tileSelectedY - tiles[0].getHeight()/2, 60,120);
		glEnd();
	}
	int wouldGoOutOfBounds(int DIRECTION) {
		int w = tiles[0].getWidth();
		int h = tiles[0].getHeight();
		double newTileX = 0;
		double newTileY = 0;
		switch (DIRECTION) {
			
		case NORTH:
			newTileY = tileSelectedY - h ;
			newTileX = tileSelectedX;
			break;
		case SOUTH:
			newTileX = tileSelectedX;
			newTileY = tileSelectedY + h ;
			break;
		case EAST:
			newTileX = tileSelectedX + w ;
			newTileY = tileSelectedY;
			break;
		case WEST:
			newTileX = tileSelectedX - w ;
			newTileY = tileSelectedY;
			break;
		case NORTHEAST:
			newTileX = tileSelectedX + (w / 2) ;
			newTileY = tileSelectedY - (h / 2) ;
			break;
		case SOUTHEAST:
			newTileX = tileSelectedX + (w / 2) ;
			newTileY = tileSelectedY + (h / 2) ;
			break;
		case NORTHWEST:
			newTileX = tileSelectedX - (w / 2) ;
			newTileY = tileSelectedY - (h / 2) ;
			break;
		case SOUTHWEST:
			newTileX = tileSelectedX - (w / 2) ;
			newTileY = tileSelectedY + (h / 2) ;
			break;
		}
		int tilenumber = whatTileIs(newTileX, newTileY);
		if (tilenumber == -1) {	
			return 1;
		}
		return 0;
	}
	int tilewalk(int DIRECTION, int firstPassing) {
		if (firstPassing == 1) {
			if ((wouldGoOutOfBounds(DIRECTION)) == 1) {
				outOfBounds = 1;
				return outOfBounds;
			}
		}
		if (outOfBounds == 0) {
			int w = tiles[0].getWidth();
			int h = tiles[0].getHeight();
			int newTileX = 0;
			int newTileY = 0;
			switch (DIRECTION) {
			case NORTH:
				newTileY = tileSelectedY - h / 5;
				newTileX = tileSelectedX;
				character.setTexture(4);
				break;
			case SOUTH:
				newTileX = tileSelectedX;
				newTileY = tileSelectedY + h / 5;
				character.setTexture(5);
				break;
			case EAST:
				newTileX = tileSelectedX + w / 5;
				newTileY = tileSelectedY;
				character.setTexture(6);
				break;
			case WEST:
				newTileX = tileSelectedX - w / 5;
				newTileY = tileSelectedY;
				character.setTexture(7);
				break;
			case NORTHEAST:
				newTileX = tileSelectedX + (w / 2) / 5;
				newTileY = tileSelectedY - (h / 2) / 5;
				character.setTexture(8);
				break;
			case SOUTHEAST:
				newTileX = tileSelectedX + (w / 2) / 5;
				newTileY = tileSelectedY + (h / 2) / 5;
				character.setTexture(9);
				break;
			case NORTHWEST:
				newTileX = tileSelectedX - (w / 2) / 5;
				newTileY = tileSelectedY - (h / 2) / 5;
				character.setTexture(10);
				break;
			case SOUTHWEST:
				newTileX = tileSelectedX - (w / 2) / 5;
				newTileY = tileSelectedY + (h / 2) / 5;
				character.setTexture(11);
				break;
			}
			int tilenumber = whatTileIs(newTileX, newTileY);
			if (tilenumber != -1) {
				tileSelectedX = newTileX;
				tileSelectedY = newTileY;
				tileSelected = tilenumber;
			}
			if (!tiles[tileSelected].isVisited()) {
				numberOfClicks = INIT_NUMBER_OF_CLICKS;
			}
			tiles[tileSelected].setVisited();
			tiles[tileSelected].setVisible();
			return outOfBounds;
		}
	}
	int getSize() {
		return size;
	}
	
	void selectTile(int x, int y) {
		int tilenumber = whatTileIs(x, y);
		if (tilenumber != -1) {
			tileSelectedX = x;
			tileSelectedY = y;
			tileSelected = tilenumber;
		}
	}

	void mouseMap(int x, int y) {
		if (numberOfClicks > 0){
			int tilenumber = whatTileIs(x, y);
		if (tilenumber != -1) {
			tiles[tilenumber].setVisible();
		}
		numberOfClicks--;
	}		
	}
	void drawCursors() {
		for (int i = 1; i <= numberOfClicks; i++) {
			glBindTexture(GL_TEXTURE_2D, 13);
			glBegin(GL_QUADS);
			drawRect(30*i, 0, 30, 45);
			glEnd();
		}
	}
	void reSetOutOfBounds() {
		outOfBounds = 0;
	}
	int whatTileIs(int x, int y) {
		double halfwidth = tiles[0].getWidth() / 2;
		double halfheight = tiles[0].getHeight() / 2;
		double realx = (double)x;
		double realy = (double)y;
		double mapx = ((((startx + halfwidth) - x) / halfwidth) + ((y / halfheight))) / 2;
		double mapy = ((y / halfheight) - (((startx + halfwidth) - x) / halfwidth)) / 2;
		int smapx = floor(mapx);
		int smapy = floor(mapy);
		int tilenumber = smapx * sqrt(size) + smapy;
		if (smapy >= sqrt(size) || smapx >= sqrt(size) || smapx < 0 || smapy < 0) {
			return -1;
		}
		else {
			return tilenumber;
			printf("posição X: %d  Y: %d", smapx, smapy);
		}
	}
private:
	Tile * tiles;
	Texture textures;
	int size;
	int outOfBounds;
	double startx;
	double starty;
	int gameWidth;
	int gameHeight;
	int numberOfClicks;
	Element explosion;
	Element character;
};

#endif