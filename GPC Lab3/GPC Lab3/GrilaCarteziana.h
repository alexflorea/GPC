#pragma once
#include <math.h>
#include <algorithm>

#include "glut.h"

using namespace std;

class GrilaCarteziana
{
public:
	GrilaCarteziana(int sizeX, int sizeY);
	~GrilaCarteziana(void);

public:
	//Afiseaza grila
	void display();

	//Recalculeaza dimensiunile in cazul redimensionarii
	//TODO
	void recomputeSize(int h, int w);
	void writeLine(int, int, int, int, int width = 0);
	void writePixel(int, int, bool, int width = 0);
	void drawPixel(float x, float y, float size);

private:
	//Cate linii pe fiecare dimensiune
	//Setate din constructor
	int sizeX;
	int sizeY;


	//Dimensiunea unei casute
	float gridSize;
	int** grid;
};

