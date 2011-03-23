
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "glut.h"

#include "GrilaCarteziana.h"

// dimensiunea ferestrei in pixeli
#define dim 600

unsigned char prevKey;

// concoida lui Nicomede (concoida dreptei)
// $x = a + b \cdot cos(t), y = a \cdot tg(t) + b \cdot sin(t)$. sau
// $x = a - b \cdot cos(t), y = a \cdot tg(t) - b \cdot sin(t)$. unde
// $t \in (-\pi / 2, \pi / 2)$
void Display1() {
	GrilaCarteziana grila(100, 100);
	//grila.writePixel(0, 3);

	//grila.writeLine(1, 9, 15, 10);
	grila.writePixel(10, 10, true, 1);

	grila.writeLine(25, 25, 15, 10);
	grila.writeLine(25, 25, 35, 10);
	grila.writeLine(25, 25, 15, 40, 1);
	grila.writeLine(25, 25, 35, 40);

	grila.display();
}


void Display2() {
	GrilaCarteziana grila(5, 5);


	grila.writePixel(2, 2, true, 1);

	grila.display();
}


void Init(void) {

   glClearColor(1.0,1.0,1.0,1.0);

   glLineWidth(1);

//   glPointSize(4);

   glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
   glClear(GL_COLOR_BUFFER_BIT);

   switch(prevKey) {
   case '1':
      Display1();
      break;
   case '2':
      Display2();
      break;
   default:
      break;
   }

   glFlush();
}

void Reshape(int w, int h) {
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
   prevKey = key;
   if (key == 27) // escape
      exit(0);
   glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

   glutInit(&argc, argv);
   
   glutInitWindowSize(dim, dim);

   glutInitWindowPosition(100, 100);

   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

   glutCreateWindow (argv[0]);

   Init();

   glutReshapeFunc(Reshape);
   
   glutKeyboardFunc(KeyboardFunc);
   
   glutMouseFunc(MouseFunc);

   glutDisplayFunc(Display);
   
   glutMainLoop();

   return 0;
}
