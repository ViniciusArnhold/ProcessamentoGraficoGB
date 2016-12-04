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

	void bindTextures(GLuint *ids, Image *textures, int numTextures) {
		glGenTextures(numTextures, ids);
		for (int i = 0; i < numTextures; i++) {
			glBindTexture(GL_TEXTURE_2D, ids[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textures[i].getWidth(), textures[i].getHeight(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, textures[i].getPixels());
		}
	}

	void initTextures() {
		Image textures[NUM_TEX];
		int i = 0;

		PTMReader carregador = PTMReader();
		carregador.ler("terra.ptm");
		textures[i++] = carregador.getImage();
		carregador.ler("destroy_stage.ptm");
		textures[i++] = carregador.getImage();
		carregador.ler("diamante_chegada.ptm");
		textures[i++] = carregador.getImage();
		carregador.ler("Personagem-Norte.ptm");
		textures[i++] = carregador.getImage();
		carregador.ler("Personagem-Sul.ptm");
		textures[i++] = carregador.getImage();
		carregador.ler("Personagem-Leste.ptm");
		textures[i++] = carregador.getImage();
		carregador.ler("Personagem-Oeste.ptm");
		textures[i++] = carregador.getImage();
		carregador.ler("Personagem-Nordeste.ptm");
		textures[i++] = carregador.getImage();
		carregador.ler("Personagem-Sudeste.ptm");
		textures[i++] = carregador.getImage();
		carregador.ler("Personagem-Noroeste.ptm");
		textures[i++] = carregador.getImage();
		carregador.ler("Personagem-Sudoeste.ptm");
		textures[i++] = carregador.getImage();
		carregador.ler("Personagem-Morto.ptm");
		textures[i++] = carregador.getImage();
		carregador.ler("cursor_novo.ptm");
		textures[i++] = carregador.getImage();
		carregador.ler("destroy_stage.ptm");
		textures[i++] = carregador.getImage();
		
		
		bindTextures(idsTiles, textures, NUM_TEX);
	}

private:
	GLuint *idsTiles;
	

};

#endif
