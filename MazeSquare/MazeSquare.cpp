// MazeSquare.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include "pch.h"
#include <iostream>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <cstdlib>
#include <ctime>
#include <vector>


typedef struct square {
	GLint   x1;
	GLint	y1;
	GLint width;
}square;

std::vector<square> mazeVector;
std::vector<square> mazeWallVector;
std::vector<square> wallVector;
std::vector<square> mazeRoadVector;


GLint squareWidth = 3;
GLint width = 36;
GLint height = 60;

square p;
bool anwser = false;


void glDrawSquare(GLint xD, GLint yD) {

	glBegin(GL_POLYGON);
	//czarny
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2i(xD, yD);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2i(xD, yD - squareWidth);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2i(xD - squareWidth, yD - squareWidth);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2i(xD - squareWidth, yD);
	glEnd();


}
void drawMaze() {

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex2f(-3, -3);
	glColor3f(1.0f, 0.0f, 1.0f);
	//glVertex2f((0 + width-3), 0);
	glVertex2f((0 + width), -3);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex2f((0 + width), (0 + height));
	//glVertex2f((0 + width-3), (0 + height-3));
	glColor3f(1.0f, 0.0f, 1.0f);
	//glVertex2f(0, (0 + height-3));
	glVertex2f(-3, ( + height));
	glEnd();


	/*
	glLineWidth(6);

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2i(-1, -2);
	glVertex2i(-1, height - 2);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f); 
	glVertex2i(-2, height - 3);
	glVertex2i(width - 1, height - 3);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2i(width - 2, height - 3);
	glVertex2i(width - 2, -2);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2i(width - 1, -1);
	glVertex2i(-1, -1);
	glEnd();

	*/
	/*
	for (unsigned int i = 0; i < mazeWallVector.size(); i++) {
		glColor3f(1.0f, 0.0f, 1.0f);
		glDrawSquare(mazeWallVector[i].x1, mazeWallVector[i].y1);
	}

	*/
	for (unsigned int i = 0; i < mazeRoadVector.size(); i++) {
		glColor3f(1.0f, 0.0f, 1.0f);
		glDrawSquare(mazeRoadVector[i].x1, mazeRoadVector[i].y1);
	}
	int w = rand() % width;

	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2i(w, 0);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2i(w, 0 - squareWidth);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2i(w - squareWidth, 0 - squareWidth);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2i(w - squareWidth, 0);
	glEnd();

}
void checkPoints(square &s) 
{
	int counter = -1;
	square k = s;
	int counterMaze = 0;

	k.x1 = s.x1 - 3;

	if ( (k.x1 >p.x1) && (k.x1 < (p.x1 + width)))
		if ((k.y1 > p.y1) && (k.y1 < (p.y1 + height))) {

			for (int h = 0; h < mazeVector.size(); h++) {
				if ((mazeVector[h].x1 == k.x1) && (mazeVector[h].y1 == k.y1))counterMaze++;
			}

			if (counterMaze == 0) {
				for (int i = 0; i < wallVector.size(); i++)
				{
					counter = 0;
					if ((k.x1 == wallVector[i].x1) && (wallVector[i].y1 == k.y1)) {

						mazeWallVector.push_back(wallVector[i]);
						mazeVector.push_back(wallVector[i]);

						wallVector.erase(wallVector.begin() + i);
						counter = -1;
						break;
					}
				}
				if (counter != -1) wallVector.push_back(k);
			}
			else
			{
				counterMaze = 0;
			}
		}

	//2nd neighbour
	k.x1 = s.x1 + 3;
	counter = -1;

	if ((k.x1 > p.x1) && (k.x1 < (p.x1 + width)))
		if ((k.y1 > p.y1) && (k.y1 < (p.y1 + height))) {

			for (int h = 0; h < mazeVector.size(); h++) {
				if ((mazeVector[h].x1 == k.x1) && (mazeVector[h].y1 == k.y1))counterMaze++;
			}

			if (counterMaze == 0) {
				counter = 0;
				for (int i = 0; i < wallVector.size(); i++)
				{
					counter = 0;
					if ((k.x1 == wallVector[i].x1) && (wallVector[i].y1 == k.y1)) {

						mazeWallVector.push_back(wallVector[i]);
						mazeVector.push_back(wallVector[i]);

						wallVector.erase(wallVector.begin() + i);
						counter = -1;
						break;
					}
				}
				if (counter != -1) wallVector.push_back(k);
			}
			else
			{
				counterMaze = 0;
			}
		}
	//3rd neighbour
	k.x1 = s.x1;
	k.y1 = s.y1 + 3;
	counter = -1;


	if ((k.x1 > p.x1) && (k.x1 < (p.x1 + width)))
		if ((k.y1 > p.y1) && (k.y1 < (p.y1 + height))) {

			for (int h = 0; h < mazeVector.size(); h++) {
				if ((mazeVector[h].x1 == k.x1) && (mazeVector[h].y1 == k.y1))counterMaze++;
			}

			if (counterMaze == 0) {
				counter = 0;
				for (int i = 0; i < wallVector.size(); i++)
				{
					counter = 0;
					if ((k.x1 == wallVector[i].x1) && (wallVector[i].y1 == k.y1)) {

						mazeWallVector.push_back(wallVector[i]);
						mazeVector.push_back(wallVector[i]);

						wallVector.erase(wallVector.begin() + i);
						counter = -1;
						break;
					}
				}
				if (counter != -1) wallVector.push_back(k);
			}
			else
			{
				counterMaze = 0;
			}
		}

	//4 neighbour
	k.y1 = s.y1 - 3;
	counter = -1;


	if ((k.x1 > p.x1) && (k.x1 < (p.x1 + width)))
		if ((k.y1 > p.y1) && (k.y1 < (p.y1 + height))) {

			for (int h = 0; h < mazeVector.size(); h++) {
				if ((mazeVector[h].x1 == k.x1) && (mazeVector[h].y1 == k.y1))counterMaze++;
			}

			if (counterMaze == 0) {
				counter = 0;
				for (int i = 0; i < wallVector.size(); i++)
				{
					counter = 0;
					if ((k.x1 == wallVector[i].x1) && (wallVector[i].y1 == k.y1)) {

						mazeWallVector.push_back(wallVector[i]);
						mazeVector.push_back(wallVector[i]);

						wallVector.erase(wallVector.begin() + i);
						counter = -1;
						break;
					}
				}
				if (counter != -1) wallVector.push_back(k);
			}
			else
			{
				counterMaze = 0;
			}
		}
}
void countMaze(square c, GLint width) {

	square s;
	s.x1 = c.x1;
	s.y1 = c.y1 + squareWidth;
	s.width = c.width;

	int size;

	mazeVector.push_back(s);
	mazeRoadVector.push_back(s);

	checkPoints(s);

		do {
			if (wallVector.size() == 0)break;
			int number = rand() % wallVector.size();
			
			s = wallVector[number];
			
			wallVector.erase(wallVector.begin() + number);

			mazeRoadVector.push_back(s);
			mazeVector.push_back(s);

			checkPoints(s);

			size = wallVector.size();

		} while (size != 0);

	drawMaze();
}


void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	p.x1 = 0;
	p.y1 = 0;
	p.width = squareWidth;

	square c;
	c.x1 = 0;
	c.y1 = 0;
	c.width = squareWidth;

	glColor3f(0.0f, 1.0f, 0.0f);

	countMaze(c, width);

	glFlush();
}

void MyInit(void)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	// Kolor okna wnętrza okna - ustawiono na szary
}

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio określającej proporcję wymiarów okna
	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0
		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkościokna okna urządzenia (Viewport) W tym przypadku od (0,0) do (horizontal, vertical)

	glMatrixMode(GL_PROJECTION);
	// Określenie układu współrzędnych obserwatora

	glLoadIdentity();
	// Określenie przestrzeni ograniczającej

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie współczynnika proporcji okna
	// Gdy okno na ekranie nie jest kwadratem wymagane jest określenie okna obserwatora. 
	// Pozwala to zachować właściwe proporcje rysowanego obiektu Do określenia okna obserwatora służy funkcja glOrtho(...)
	if (horizontal <= vertical)
		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	// Określenie układu współrzędnych    

	glLoadIdentity();
}
/*************************************************************************************/
// Główny punkt wejścia programu. Program działa w trybie konsoli

void main(void)
{
	srand(time(NULL));

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wyświetlania GLUT_SINGLE - pojedynczy bufor wyświetlania GLUT_RGBA - model kolorów RGB

	glutCreateWindow("Maze drawing in OpenGL");
	// Utworzenie okna i określenie treści napisu w nagłówku okna

	glutDisplayFunc(RenderScene);
	// Określenie, że funkcja RenderScene będzie funkcją zwrotną (callback) Biblioteka GLUT będzie wywoływała tą funkcję za każdym razem, gdy
	// trzeba będzie przerysować okno

	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną za zmiany rozmiaru okna

	MyInit();
	// Funkcja MyInit (zdefiniowana powyżej) wykonuje wszelkie inicjalizacje konieczneprzed przystąpieniem do renderowania

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
}