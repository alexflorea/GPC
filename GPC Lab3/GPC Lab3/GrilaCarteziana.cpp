#include "GrilaCarteziana.h"

//TODO
//Pastrarea formei de patrat si in cazul redimensionarii

GrilaCarteziana::GrilaCarteziana(int sizeX, int sizeY)
{
	//O casuta pentru padding;
	this->sizeX = sizeX + 2;
	this->sizeY = sizeY + 2;

	//Daca ecranul are dimensiunea 2.0 (de la -1.0, la 1.0), se calculeaza care este
	//dimensiunea unei singure casute.
	//Se alege min astfel incat casuta sa fie patrata si grila sa incapa pe ecran.
	this->gridSize = min(2.0f / this->sizeX, 2.0f / this->sizeY);

	//Alocam memorie
	//Componenta X va fi constant pe linii si Y va fi constant pe coloane
	this->grid = (int**) malloc (sizeY * sizeof(int*));
	for(int i = 0; i < sizeY; i++) {
		this->grid[i] = (int*) malloc (sizeX * sizeof(int));
		for(int j = 0; j < sizeX; j++) {
			this->grid[i][j] = 0;
		}
	}
}


GrilaCarteziana::~GrilaCarteziana(void)
{
	for(int i = 0; i < sizeY - 2; i++) {
		//free(grid[i]);
	}
	//free(grid);
}


void GrilaCarteziana::display()
{
	//Se calculeaza punctul din dreapta sus al desenarii
	//Ambele trebuie sa fie pozitive
	//Una din ele trebuie sa fie 1.0f
	//Eliminam padding-ul din desenare
	float startX, startY;
	startX = (sizeX - 2) * gridSize / 2;
	startY = (sizeY - 2) * gridSize / 2;

	//Punctele de desenare curente
	float drawX, drawY;
	drawX = startX;
	drawY = startY;

	//Se deseneaza doar primul cadran deoarece liniile se prelungesc in celelalte
	//prin oglindire
	glColor3f(0.8f, 0.8f, 0.8f);
	glBegin(GL_LINES);
		for(int i = 0; i < sizeX / 2; i++) {
			for(int j = 0; j < sizeY / 2; j++) {
				//Se deseneaza de la un capat la altul
				//Bara orizontala
				glVertex2f( startX, drawY);
				glVertex2f(-startX, drawY);

				//Bara verticala
				glVertex2f(drawX,  startY);
				glVertex2f(drawX, -startY);

				//Reactualizarea pozitiei curente
				drawX -= gridSize;
				drawY -= gridSize;
			}
		}
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	//Se deseneaza pixelii
	for(int i = 0; i < sizeY - 2; i++) {
		for(int j = 0; j < sizeX - 2; j++) {
			//Deocamdata ca patrate
			if(grid[i][j] == 1) {
				//Calculam coordonatele
				float drawX, drawY;
				//Desenam de la stanga la dreapta si de sus in jos
				drawX = - (sizeY - 2) * gridSize / 2 + gridSize * i;
				drawY = (sizeX - 2) * gridSize / 2 - gridSize * j;

				//glBegin(GL_POLYGON);
				//	glVertex2f(drawX + gridSize / 4, drawY + gridSize / 4);
				//	glVertex2f(drawX + gridSize / 4, drawY - gridSize / 4);
				//	glVertex2f(drawX - gridSize / 4, drawY - gridSize / 4);
				//	glVertex2f(drawX - gridSize / 4, drawY + gridSize / 4);
				//glEnd();
				drawPixel(drawX, drawY, gridSize / 4);
			}
		}
	}
}

void GrilaCarteziana::recomputeSize(int h, int w)
{

}

void GrilaCarteziana::drawPixel(float x, float y, float size) 
{
	glBegin(GL_POLYGON);
		for(float i = 3.14 * 2; i >= 0 ; i -= 3.14 * 2 / 16) {
			float drawX = x + size * cos(i);
			float drawY = y + size * sin(i);
			glVertex2f(drawX, drawY);
		}
	glEnd();
}

void GrilaCarteziana::writeLine(int p1x, int p1y, int p2x, int p2y, int width)
{
    int F, x, y;

    if (p1x > p2x) { // Schimba punctele daca nu sunt in ordine (se deseneaza de la stanga la dreapta)
        swap(p1x, p2x);
        swap(p1y, p2y);
    }

    // Handle trivial cases separately for algorithm speed up.
    // Trivial case 1: m = +/-INF (Vertical line)
	 //Cazuri triviale
	 //Cazul in care linia este verticala
    if (p1x == p2x) {
        if (p1y > p2y) {  
			  // Schimba punctele daca nu sunt in ordine (se deseneaza de jos in sus,
			  // dupa care se oglindeste pe axa y
            swap(p1y, p2y);
        }
        x = p1x;
        y = p1y;
        while (y <= p2y) {
            writePixel(x, y, true, width);
            y++;
        }
        return;
    }
    // Cazul in care linia este orizontala
    else if (p1y == p2y) {
        x = p1x;
        y = p1y;

        while (x <= p2x) {
            writePixel(x, y, true, width);
            x++;
        }
        return;
    }


    int dy            = p2y - p1y;
    int dx            = p2x - p1x;
    int dy2           = (dy << 1);
    int dx2           = (dx << 1);
    int dy2_minus_dx2 = dy2 - dx2;
    int dy2_plus_dx2  = dy2 + dx2;


    if (dy >= 0) {
        // 0 <= m <= 1
		 if (dy <= dx) {
            F = dy2 - dx;    // initial F

            x = p1x;
            y = p1y;
            while (x <= p2x) {
                writePixel(x, y, true, width);
                if (F <= 0) {
                    F += dy2;
                } else {
                    y++;
                    F += dy2_minus_dx2;
                }
                x++;
            }
        } else {
			  // 1 < m < INF
            F = dx2 - dy;

            y = p1y;
            x = p1x;
            while (y <= p2y) {
                writePixel(x, y, true, width);
                if (F <= 0) {
                    F += dx2;
                } else {
                    x++;
                    F -= dy2_minus_dx2;
                }
                y++;
            }
        }
    } else {
		  // m < 0
        // -1 <= m < 0
        if (dx >= -dy) {
            F = -dy2 - dx;    // initial F

            x = p1x;
            y = p1y;
            while (x <= p2x) {
                writePixel(x, y, true, width);
                if (F <= 0) {
                    F -= dy2;
                } else {
                    y--;
                    F -= dy2_plus_dx2;
                }
                x++;
            }
        } else {
			  // -INF < m < -1
            F = dx2 + dy;    // initial F

            y = p1y;
            x = p1x;
            while (y >= p2y) {
                writePixel(x, y, true, width);
                if (F <= 0) {
                    F += dx2;
                } else {
                    x++;
                    F += dy2_plus_dx2;
                }
                y--;
            }
        }
    }
}



void GrilaCarteziana::writePixel(int x, int y, bool enable, int width)
{
	for(int i = x - width; i <= x + width; i++) {
		if(i < 0 && i > sizeX)
			continue;
		for(int j = y - width; j <= y + width; j++) {
			if(j < 0 && j > sizeY)
				continue;
			grid[i][j] = enable ? 1 : 0;
		}			
	}
}

