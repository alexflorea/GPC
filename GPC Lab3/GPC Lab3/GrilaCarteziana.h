#pragma once
#include <math.h>
#include <algorithm>

#include "glut.h"

 struct segment{
int y,x0,x;
} ;

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
	void fillElipse(int x0,int y0,int a,int b);
	void adaugaSegment(int y,int x0,int x);
	void setSegment(int y,int x0,int x);
	void vidareSegment();
	void drawSegment(); // Deseneaza cadranul III
	void mirrorSegment(int x,int y,int x_orig,int y_orig); // In baza punctelor din ssm, se obtin in reflexie cadranele I,II,IV
private:
	//Cate linii pe fiecare dimensiune
	//Setate din constructor
	int sizeX;
	int sizeY;
	segment ssm[200];
	int n;

	//Dimensiunea unei casute
	float gridSize;
	int** grid;
};