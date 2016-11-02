#include <GL\glut.h>
#include "Line.h"
#include "Point.h"
#include "Circle.h"
#define _USE_MATH_DEFINES
#include <cmath> //PI
#include <iostream> //egérkatt log
#include <vector> //köröket tárolásához

const int windowWidth = 800;
const int windowHeight = 600;
int keyStates[256];
double offset = 0.01; //kör rajzolásának lépésköze TODO
double circleRadius = 25; //globálisan ez lesz a körök sugara.
std::vector <Circle> circleContainer; //ez fogja tárolni a köröket

Line verticalLine = Line(Point(400, 0), Point(400, 600)); //függõleges vonal
Line horizontalLine = Line(Point(0, 300), Point(800, 300)); //vízszintes vonal

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	//ha nincs bent, csak a vonalmozgás vagy csak a körmozgás megy. 
	//ezzel a paranccsal egyszerre több mátrixot is tudunk kezelni.
	glLoadIdentity(); 
	gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
}

/*
függõleges vonal rajzolása
*/
void glDrawVerticalLine() {
	glColor3d(1.0, 0.0, 0.0);

	glBegin(GL_LINES);

	glVertex2d(verticalLine.a.xCord, verticalLine.a.yCord); //alsó pont
	glVertex2d(verticalLine.b.xCord, verticalLine.b.yCord); //felsõ pont

	glEnd();
}

/*
vízszintes vonal rajzolása
*/
void glDrawHorizontalLine() {
	glColor3d(0.0, 1.0, 0.0);

	glBegin(GL_LINES);

	glVertex2d(horizontalLine.a.xCord, horizontalLine.a.yCord); //bal szélsõ pont
	glVertex2d(horizontalLine.b.xCord, horizontalLine.b.yCord); //jobb szélsõ pont

	glEnd();

}

/*
lenyomott gombok kezelése
x - y az egérmutató helyét mutatja viszont ez csak a paraméterlista miatt fontos,
az egérkezelésre más fv-t használunk.
*/
void keyPressed(unsigned char key, int x, int y) {
	keyStates[key] = 1;
}

/*
lásd keyPressed fv. leírása
felengedett gombok
*/
void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = 0;
}

/*
a-d, s-w gombok kezelése
a-> függõleges teteje balra
d-> függõleges teteje jobbra

s-> vízszintes bal oldala felfelé
w-> vízszintes bal oldala lefelé
*/
void keyOperations() {

	if (keyStates['a']) {
		if (verticalLine.a.xCord <= 800 && verticalLine.b.xCord >= 0) {
			verticalLine.a.xCord++; //függõleges alsó koordinátája jobbra,
			verticalLine.b.xCord--; //felsõ koordinátája balra.
		}

	}

	if (keyStates['d']) {
		if (verticalLine.a.xCord >= 0 && verticalLine.b.xCord <= 800) {
			verticalLine.a.xCord--; //függõleges alsó koordinátája balra, 
			verticalLine.b.xCord++; //felsõ koordinátája jobbra.
		}
	}

	if (keyStates['s']) {
		if (horizontalLine.a.yCord <= 600 && horizontalLine.b.yCord >= 0) {
			horizontalLine.a.yCord++; //víszintes bal oldali pontja fel,
			horizontalLine.b.yCord--; //jobb oldali pontja le
		}
	}

	if (keyStates['w']) {
		if (horizontalLine.a.yCord >= 0 && horizontalLine.b.yCord <= 600) {
			horizontalLine.a.yCord--; //vízszintes bal oldali pontja le,
			horizontalLine.b.yCord++; //jobb oldali pontja fel
		}
	}

	glutPostRedisplay(); //a main loop minden iterációjában újra kell rajzolni a display tartalmát.
}

/*
elõadásos képlet implementálva
eldönti, hogy egy adott dolog a vonal jobb vagy bal odalán van
*/
bool isPointOnLeftSideOfLine(Point a, Line line)
{
	return (line.b.xCord - line.a.xCord) * (a.yCord - line.a.yCord) - (line.b.yCord - line.a.yCord) * (a.xCord - line.a.xCord) > 0;
}

/*
négy különbözõ szín meghatározása, a négy területre.
*/
void glChangeColors(bool vertical, bool horizontal) {

	if (vertical && horizontal) {
		glColor3d(1.0, 0.0, 0.0);
	}

	else if (!vertical && !horizontal) {
		glColor3d(0, 1.0, 0.0);
	}

	else if (vertical && !horizontal) {
		glColor3d(0.0, 0.0, 1.0);
	}

	else {
		glColor3d(1.0, 1.0, 0.0);
	}
}

/*
meghatározott színek beállítása a pontoknak, attól függõen, hogy a pont és az egyenes milyen viszonyban állnak
*/
void glSetPointsColor(Point p) {
	bool vertical = isPointOnLeftSideOfLine(p, verticalLine);
	bool horizontal = isPointOnLeftSideOfLine(p, horizontalLine);

	glChangeColors(vertical, horizontal);
}

/*
beállított színnel rajzol egy pontot
*/
void glPoint(Point p) {
	glSetPointsColor(p);
	glVertex2d(p.xCord, p.yCord);
}

/*
Feltöljük ezekkel a színes pontokkal az egész képernyõt.
*/
void glDrawPoints() {
	glEnable(GL_POINT_SMOOTH); //kör alakú pontok rajzolása
	glPointSize(2.0);

	glBegin(GL_POINTS);

	/*
	8 pixelenként tesszük le a pontokat.
	*/
	for (double x = 0; x < windowWidth; x += 8) {
		for (double y = 0; y < windowHeight; y += 8) {
			glPoint(Point(x, y));
		}
	}

	glEnd();
}
//TODO
/*
TODO
*/
void glDrawCircle(Circle circle) {
	glColor3d(1.0, 1.0, 0.0);
	glBegin(GL_TRIANGLE_FAN); //telt kör

	for (double x = 0; x < 2 * M_PI; x += offset) {
		glVertex2d(circle.origo.xCord + circleRadius * cos(x), circle.origo.yCord + circleRadius * sin(x)); //TODO
	}

	glEnd();
}
//TODO
/*
elõadásos képlet
*/
float distanceOfPointsFromLine(Line l, Point p)
{
	float abyDiff = l.a.yCord - l.b.yCord;
	float baxDiff = l.b.xCord - l.a.xCord;

	return fabs(((abyDiff)*l.a.xCord + (baxDiff)*l.a.yCord - (abyDiff)*p.xCord - (baxDiff)*p.yCord) / sqrt((abyDiff)*(abyDiff)+(baxDiff)*(baxDiff)));
}

/*
feladatos pdf alapján készült tükrözõ fv.
*/
Point mirroring(Point hasToBeMirror, Point mirror)
{
	double t = (hasToBeMirror.xCord*mirror.xCord + hasToBeMirror.yCord*mirror.yCord) / (mirror.xCord*mirror.xCord + mirror.yCord*mirror.yCord);
	Point c = Point(mirror.xCord*t, mirror.yCord*t);
	Point ac = Point(c.xCord - hasToBeMirror.xCord, c.yCord - hasToBeMirror.yCord);
	Point mirrored = Point(hasToBeMirror.xCord + 2 * ac.xCord, hasToBeMirror.yCord + 2 * ac.yCord);
	return mirrored;
}

/*
Feladat szövegébõl idézve:
"...egy kör akkor pattan el egy egyenesrõl, ha a
középpontjának az egyenestõl mért távolsága sugárnyi."
Tehát ez a függvény a mozgásért felel. Ha elér egy szélt vagy vonalat, akkor visszapattan.
*/
void move() {

	for (int i = 0; i < circleContainer.size(); i++)
	{
		if (circleContainer[i].origo.xCord - circleRadius < 0 || circleContainer[i].origo.xCord + circleRadius > windowWidth)
		{
			circleContainer[i].invertDestination('x');
		}
		else if (circleContainer[i].origo.yCord - circleRadius < 0 || circleContainer[i].origo.yCord + circleRadius > windowHeight)
		{
			circleContainer[i].invertDestination('y');
		}
		if (distanceOfPointsFromLine(verticalLine, circleContainer[i].origo) < circleRadius)
		{
			circleContainer[i].destination = mirroring(circleContainer[i].destination, Point(verticalLine.b.xCord - verticalLine.a.xCord, verticalLine.b.yCord - verticalLine.a.yCord));
		}
		else if (distanceOfPointsFromLine(horizontalLine, circleContainer[i].origo) < circleRadius)
		{
			circleContainer[i].destination = mirroring(circleContainer[i].destination, Point(horizontalLine.a.xCord - horizontalLine.b.xCord, horizontalLine.a.yCord - horizontalLine.b.yCord));
		}
		circleContainer[i].origo.xCord += circleContainer[i].destination.xCord;
		circleContainer[i].origo.yCord += circleContainer[i].destination.yCord;
	}
}

/*
Ha az egér bal gombját lenyomjuk, kilogolja a terminálra a mutató koordinátáit,
majd generál egy random számot 1 és 0.6 közt.
Ezt követõen létrehoz egy kört, aminek a középpontja a kurzor helye lesz,
a hozzá tartozó sebesség, pedig ez a generált szám.
A létrehozott kört, majd a konténerben tároljuk.
*/
void glMouseControl(int button, int state, int xMouse, int yMouse) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		std::cout << xMouse << "\t" << yMouse << std::endl;

		double step = rand() % 1 + 0.6;

		Circle circle = Circle(Point(xMouse, windowHeight - yMouse), circleRadius, step);
		circleContainer.push_back(circle);
	}
}

/*
mivel a mainLoop folyamatosan fut, ez is folyamatosan futni fog.
Ez jeleníti meg a rajzolt dolgokat, illetve felel a köröket tartalmazó vectorok tárolásáért.
*/
void display() {

	keyOperations();

	glClear(GL_COLOR_BUFFER_BIT);

	glDrawVerticalLine();
	glDrawHorizontalLine();

	glDrawPoints();

	for (auto it = circleContainer.begin(); it != circleContainer.end(); it++) {
		glDrawCircle(*it);
	}

	move();

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowPosition(50, 100);

	glutInitWindowSize(windowWidth, windowHeight);

	glutCreateWindow("elsobeadandowazze");

	init();

	glutDisplayFunc(display);

	glutKeyboardFunc(keyPressed);

	glutKeyboardUpFunc(keyUp);

	glutMouseFunc(glMouseControl);

	glutMainLoop();

	return 0;
}