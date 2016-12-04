#pragma once
class NImage
{
	unsigned int *pixels;
	int width = 0;
	int height = 0;
public:
	NImage(int w, int h);
	NImage(char* caminho);
	NImage();

	//Core
	void plot(NImage* sobreposta, int posicaoX, int posicaoY);
	void subImage(NImage* dest, int startx, int starty);
	void plotInto(NImage* sobreposta, int posicaoX, int posicaoY, char *zBuffer, char z);

	//Helpers
	void calcular();
	int calcularPixels(int sobreposta, int fundo);
	NImage clone();

	//Getters & Setters
	int getPixel(int x, int y);
	void setPixel(int rgb, int x, int y);
	void setPixel(int a, int r, int g, int b, int x, int y);
	unsigned int* getPixels();
	int getWidth();
	void setWidth(int w);
	int getHeight();
	void setHeight(int h);
};