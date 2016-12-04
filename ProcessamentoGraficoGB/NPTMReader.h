#pragma once
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include "NImage.h"

class NPTMReader
{
	NImage img;
public:
	NPTMReader();
	char* nextLine();
	NImage getImage();
	void ler(char* caminho);
};