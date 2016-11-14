#ifndef Texture_H
#define  Texture_H

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Image.h"

#define NUM_TEX 14

class Texture {


public:
	void init_textures() {
		idsTiles = new GLuint[NUM_TEX];
		Texture::initTextures();

	}

	GLuint *getIds() {
		return idsTiles;
	}


private:

	void bindTextures(GLuint *ids, Image **textures, int numTextures) {
		glGenTextures(numTextures, ids);
		for (int i = 0; i < numTextures; i++) {
			glBindTexture(GL_TEXTURE_2D, ids[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textures[i]->getWidth(), textures[i]->getHeight(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, textures[i]->getPixels());
		}
	}

	void initTextures() {
		Image *textures[NUM_TEX];
		int i = 0;
		textures[i++] = &Image("tile.ptm");
		textures[i++] = &Image("bomb.ptm");
		textures[i++] = &Image("chest.ptm");
		textures[i++] = &Image("parado_norte.ptm");
		textures[i++] = &Image("parado_sul.ptm");
		textures[i++] = &Image("parado_leste.ptm");
		textures[i++] = &Image("parado_oeste.ptm");
		textures[i++] = &Image("parado_nordeste.ptm");
		textures[i++] = &Image("parado_sudeste.ptm");
		textures[i++] = &Image("parado_noroeste.ptm");
		textures[i++] = &Image("parado_sudoeste.ptm");
		textures[i++] = &Image("dead.ptm");
		textures[i++] = &Image("cursor.ptm");
		textures[i++] = &Image("explode.ptm");
		bindTextures(idsTiles, textures, NUM_TEX);
	}

private:
	GLuint *idsTiles;
	

};

#endif
