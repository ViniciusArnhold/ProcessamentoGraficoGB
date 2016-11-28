#ifndef Texture_H
#define  Texture_H

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Image.h"
#include "PTMReader.h"

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
		PTMReader carregador = PTMReader();
		carregador.ler("tile.ptm");
		textures[i++] = &carregador.getImage();
		carregador.ler("bomb.ptm");
		textures[i++] = &carregador.getImage();
		carregador.ler("chest.ptm");
		textures[i++] = &carregador.getImage();
		carregador.ler("parado_norte.ptm");
		textures[i++] = &carregador.getImage();
		carregador.ler("parado_sul.ptm");
		textures[i++] = &carregador.getImage();
		carregador.ler("parado_leste.ptm");
		textures[i++] = &carregador.getImage();
		carregador.ler("parado_oeste.ptm");
		textures[i++] = &carregador.getImage();
		carregador.ler("parado_nordeste.ptm");
		textures[i++] = &carregador.getImage();
		carregador.ler("parado_sudeste.ptm");
		textures[i++] = &carregador.getImage();
		carregador.ler("parado_noroeste.ptm");
		textures[i++] = &carregador.getImage();
		carregador.ler("parado_sudoeste.ptm");
		textures[i++] = &carregador.getImage();
		carregador.ler("dead.ptm");
		textures[i++] = &carregador.getImage();
		carregador.ler("cursor.ptm");
		textures[i++] = &carregador.getImage();
		carregador.ler("explode.ptm");
		textures[i++] = &carregador.getImage();
		bindTextures(idsTiles, textures, NUM_TEX);
	}

private:
	GLuint *idsTiles;
	

};

#endif
