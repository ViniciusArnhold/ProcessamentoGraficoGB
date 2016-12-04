#include <Windows.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <fstream>
#include "Tile.h"
#include "Tilemap.h"
#include "Textures.h"
#include "Image.h"


#define gameWidth 900
#define gameHeight 450
#define NUMBER_OF_TILES 81
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

int animating = 0;
int DIRECTION = 0;
int steps = 0;

Image lastScreen(gameWidth, gameHeight);
Tilemap tilemap[1];
Textures textures;

void drawTileMap();

void restart() {
	
	Tilemap map(gameWidth, gameHeight);
	tilemap[0] = map;
	GAME_STATE = 0;
	animating = 0;
	tilemap[0].setTextures(textures);
	tilemap[0].setSize(NUMBER_OF_TILES);
	tilemap[0].setTiles(100, 50);
	tilemap[0].drawMap();
	drawTileMap();
}

void display(void)
{
		glClear(GL_COLOR_BUFFER_BIT);
		GAME_STATE = tilemap[0].drawMap();
		glFlush();

}

void init(void)
{
	Tilemap map(gameWidth, gameHeight);
	tilemap[0] = map;
	GAME_STATE = 0;
	textures.init_textures();
	tilemap[0].setTextures(textures);
	tilemap[0].setSize(NUMBER_OF_TILES);
	tilemap[0].setTiles(100, 50);
	tilemap[0].drawMap();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, gameWidth, gameHeight);
	gluOrtho2D(0, gameWidth, 0, gameHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	drawTileMap();
}

void drawTileMap() {

	glutPostRedisplay();

}
void timer(int value)
{
	int outOfBounds;
	glutPostRedisplay();
	if (value < 5 && GAME_STATE == GAME_RUNNING) {
		outOfBounds = tilemap[0].tilewalk(DIRECTION,value + 1);
		if (outOfBounds == 1) {
			value = 5;
			tilemap[0].reSetOutOfBounds();
			animating = 0;
		}
		glutTimerFunc(120, timer, ++value);
	}
	if (value >= 5) {
		animating = 0;
	}
	if (GAME_STATE == GAME_LOSS) {
		if (value < 19) {
			tilemap[0].explode();
			glutTimerFunc(100, timer, ++value);		
		}
	}
	
}


void keyboard(unsigned char key, int x, int y) {
	if (GAME_STATE == GAME_RUNNING && animating == 0) {
		switch (key) {
		case 'w':
			DIRECTION = NORTH;
			animating = 1;
			timer(0);
			break;
		case 'x':
			DIRECTION = SOUTH;
			animating = 1;
			timer(0);
			break;
		case 'd':
			DIRECTION = EAST;
			animating = 1;
			timer(0);
			break;
		case 'a':
			DIRECTION = WEST;
			animating = 1;
			timer(0);
			break;
		case 'e':
			DIRECTION = NORTHEAST;
			animating = 1;
			timer(0);
			break;
		case 'c':
			DIRECTION = SOUTHEAST;
			animating = 1;
			timer(0);
			break;
		case 'q':
			DIRECTION = NORTHWEST;
			animating = 1;
			timer(0);
			break;
		case 'z':
			DIRECTION = SOUTHWEST;
			animating = 1;
			timer(0);
			break;
		default:
			break;
		}
		drawTileMap();
	}
	if (key == '0') {
		restart();
	}
}

void mouse(int button, int state, int x, int y) {
	if (GAME_STATE == GAME_RUNNING) {
		if (GLUT_LEFT_BUTTON == button && state == GLUT_DOWN) {
			tilemap[0].mouseMap(x, y);
			drawTileMap();
		}
	}
}


int main(int argc, char** argv) {
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(gameWidth, gameHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tiles");
	init();
	//glutTimerFunc(100, timer, 0);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}


