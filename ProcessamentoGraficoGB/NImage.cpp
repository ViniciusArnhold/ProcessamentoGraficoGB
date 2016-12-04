/* ___                                                        _            ___            __ _                       ___   _
/ _ \_ __ ___   ___ ___  ___ ___  __ _ _ __ ___   ___ _ __ | |_ ___     / _ \_ __ __ _ / _(_) ___ ___             / _ \ /_\
/ /_)/ '__/ _ \ / __/ _ \/ __/ __|/ _` | '_ ` _ \ / _ \ '_ \| __/ _ \   / /_\/ '__/ _` | |_| |/ __/ _ \   _____   / /_\///_\\
/ ___/| | | (_) | (_|  __/\__ \__ \ (_| | | | | | |  __/ | | | || (_) | / /_\\| | | (_| |  _| | (_| (_) | |_____| / /_\\/  _  \
\/    |_|  \___/ \___\___||___/___/\__,_|_| |_| |_|\___|_| |_|\__\___/  \____/|_|  \__,_|_| |_|\___\___/          \____/\_/ \_/
Unisinos 2016 - Vinicius Pegorini Arnhold e Reni Steffenon
*/
#include "NImage.h"
#include "NPTMReader.h"

NImage::NImage(int largura, int altura) {
	width = largura;
	height = altura;
	pixels = new unsigned int[width*height];
}

NImage::NImage(char* caminho) {
	NImage* thiz = NPTMReader().ler(caminho);
	this->height = thiz->getHeight();
	this->width = thiz->getWidth();
	this->pixels = thiz->getPixels();
}

NImage::NImage() {

}


void NImage::setWidth(int w) {
	width = w;
}

void NImage::setHeight(int h) {
	height = h;
}


void NImage::calcular() {
	pixels = new unsigned int[width*height];
}

void NImage::setPixel(int rgb, int x, int y) {
	pixels[x + y*width] = rgb;
}

int NImage::getPixel(int x, int y) {
	return pixels[x + y*width];
}

void NImage::setPixel(int a, int r, int g, int b, int x, int y) {
	pixels[x + y*width] = (a << 24) | (r << 16) | (g << 8) | (b);
}
unsigned int* NImage::getPixels() {
	return pixels;
}

int NImage::getWidth() {
	return width;
}

int NImage::getHeight() {
	return height;
}

NImage NImage::clone() {
	NImage aux(getWidth(), getHeight());

	for (int x = 0; x < getWidth(); x++) {
		for (int y = 0; y < getHeight(); y++) {
			aux.setPixel(getPixel(x, y), x, y);
		}
	}
	return aux;

}

void NImage::subImage(NImage *src, int startx, int starty) {

	int memoryStartY = starty;
	for (int x = 0; x < src->getWidth(); x++) {
		for (int y = 0; y < src->getHeight(); y++) {
			src->setPixel(getPixel(startx, starty), x, y);
			starty++;
		}
		startx++;
		starty = memoryStartY;
	}
}

void NImage::plotInto(NImage* ref, int posicaoX, int posicaoY, char* zBuffer, char z)
{
	int xRef = 0;
	int yRef = 0;

	for (int x = posicaoX; x < ref->getWidth() + posicaoX && x < this->width; x++) {

		for (int y = posicaoY; y < ref->getHeight() + posicaoY && y < this->height; y++) {
			int alfa = (getPixel(x, y) >> 24) & 0xff;
			if (alfa != 0) {
				if (!alfa == 255) {
					if (z < zBuffer[xRef*yRef]) {
						ref->setPixel(calcularPixels(getPixel(x, y), ref->getPixel(xRef, yRef)), xRef, yRef);
					}
				}
				else {
					if (z < zBuffer[xRef*yRef]) {
						ref->setPixel(getPixel(x, y), xRef, yRef);
					}
				}
			}
			yRef++;
		}
		yRef = 0;
		xRef++;
	}

}

void NImage::plot(NImage* sobreposta, int posicaoX, int posicaoY) {

	int xSobreposta = 0;
	int ySobreposta = 0;

	for (int x = posicaoX; x < sobreposta->width + posicaoX; x++) {
		for (int y = posicaoY; y < posicaoY + sobreposta->height; y++) {
			int pixelSobreposta = sobreposta->getPixel(xSobreposta, ySobreposta);
			int alfa = (pixelSobreposta >> 24) & 0xff;
			if (alfa == 0) {
			}
			else {
				if (alfa == 255) {
					setPixel(pixelSobreposta, x, y);
				}
				else {
					setPixel(calcularPixels(pixelSobreposta, getPixel(x, y)), x, y);
				}
			}
			ySobreposta++;

		}
		ySobreposta = 0;
		xSobreposta++;
	}

}

int NImage::calcularPixels(int sobreposta, int fundo) {
	int aSobreposta = (sobreposta >> 24) & 0xff;
	int rSobreposta = (sobreposta >> 16) & 0xff;
	int gSobreposta = (sobreposta >> 8) & 0xff;
	int bSobreposta = sobreposta & 0xff;

	int aFundo = (fundo >> 24) & 0xff;
	int rFundo = (fundo >> 16) & 0xff;
	int gFundo = (fundo >> 8) & 0xff;
	int bFundo = fundo & 0xff;

	double alfa = aSobreposta / 255;
	int r = 0;
	int g = 0;
	int b = 0;

	r = rFundo*(1 - alfa) + rSobreposta*alfa;
	g = gFundo*(1 - alfa) + gSobreposta*alfa;
	b = bFundo*(1 - alfa) + bSobreposta*alfa;

	int resultado = (255 << 24) | (r << 16) | (g << 8) | (b);

	return resultado;
}