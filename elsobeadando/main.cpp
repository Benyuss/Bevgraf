#include <gl\glut.h>
#include "Line.h"
#include "Point.h"
#include "Circle.h"
#define _USE_MATH_DEFINES
#include <cmath> //PI
#include <iostream> //egérkatt log
#include <vector> //köröket tárolásához
#include <random>


const int windowWidth = 800;
const int windowHeight = 600;
int keyStates[256];
double offset = 0.01; //kör rajzolásának lépésköze TODO
double circleRadius = 25; //globálisan ez lesz a körök sugara.
std::vector <Circle> circleContainer; //ez fogja tárolni a köröket

Line verticalLine = Line(Point(400, 0), Point(400, 600)); //függõleges vonal
Line horizontalLine = Line(Point(0, 300), Point(800, 300)); //vízszintes vonal

Line topBorder = Line(Point(0, windowHeight), Point(windowWidth, windowHeight));
Line botBorder = Line(Point(0, 0), Point(windowWidth, 0));
Line rightBorder = Line(Point(windowWidth, 0), Point(windowWidth, windowHeight));
Line leftBorder = Line(Point(0, 0), Point(0, windowHeight));

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
double distanceOfPointsFromLine(Line l, Point p)
{
	double abyDiff = l.a.yCord - l.b.yCord;
	double baxDiff = l.b.xCord - l.a.xCord;

	return fabs(((abyDiff)*l.a.xCord + (baxDiff)*l.a.yCord - (abyDiff)*p.xCord - (baxDiff)*p.yCord) / sqrt((abyDiff)*(abyDiff)+(baxDiff)*(baxDiff)));
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
		/*if (circleContainer[i].origo.xCord - circleRadius < 0 || circleContainer[i].origo.xCord + circleRadius > windowWidth)
		{
			circleContainer[i].invertDestination('x');
		}
		else if (circleContainer[i].origo.yCord - circleRadius < 0 || circleContainer[i].origo.yCord + circleRadius > windowHeight)
		{
			circleContainer[i].invertDestination('y');
		}*/

		if (distanceOfPointsFromLine(topBorder, circleContainer[i].origo) < circleRadius) {
			circleContainer[i].destination = circleContainer[i].mirroring(circleContainer[i].destination, Point(topBorder.a.xCord - topBorder.b.xCord, topBorder.a.yCord - topBorder.b.yCord));
		}
		if (distanceOfPointsFromLine(botBorder, circleContainer[i].origo) < circleRadius) {
			circleContainer[i].destination = circleContainer[i].mirroring(circleContainer[i].destination, Point(botBorder.a.xCord - botBorder.b.xCord, botBorder.a.yCord - botBorder.b.yCord));
		}
		if (distanceOfPointsFromLine(rightBorder, circleContainer[i].origo) < circleRadius) {
			circleContainer[i].destination = circleContainer[i].mirroring(circleContainer[i].destination, Point(rightBorder.a.xCord - rightBorder.b.xCord, rightBorder.a.yCord - rightBorder.b.yCord));
		}
		if (distanceOfPointsFromLine(leftBorder, circleContainer[i].origo) < circleRadius) {
			circleContainer[i].destination = circleContainer[i].mirroring(circleContainer[i].destination, Point(leftBorder.a.xCord - leftBorder.b.xCord, leftBorder.a.yCord - leftBorder.b.yCord));
		}


		if (distanceOfPointsFromLine(verticalLine, circleContainer[i].origo) < circleRadius)
		{
			circleContainer[i].destination = circleContainer[i].mirroring(circleContainer[i].destination, Point(verticalLine.b.xCord - verticalLine.a.xCord, verticalLine.b.yCord - verticalLine.a.yCord));
		}
		else if (distanceOfPointsFromLine(horizontalLine, circleContainer[i].origo) < circleRadius)
		{
			circleContainer[i].destination = circleContainer[i].mirroring(circleContainer[i].destination, Point(horizontalLine.a.xCord - horizontalLine.b.xCord, horizontalLine.a.yCord - horizontalLine.b.yCord));
		}
		circleContainer[i].origo.xCord += circleContainer[i].destination.xCord;
		circleContainer[i].origo.yCord += circleContainer[i].destination.yCord;
	}
}

/*
Ellenõrzi a kattintott lokációt. Amennyiben olyan helyre kattintunk, 
ahol a koordináta és sugár összege(vagy épp különbsége):
	- az ablakon kívülre, 
	- az ablak szélére,
	- egy vonalra,
esik, akkor a kör nem jön létre.
*/
bool isCirclePositionValid(Point p) {
	std::cout << "distance from lines" << std::endl;
	std::cout << "horizontal: " << distanceOfPointsFromLine(horizontalLine, p) << std::endl;
	std::cout << "vertical: " << distanceOfPointsFromLine(verticalLine, p) << std::endl;

	double distanceFromHorizontal = distanceOfPointsFromLine(horizontalLine, p);
	double distanceFromVertical = distanceOfPointsFromLine(verticalLine, p);

	if ((p.xCord - circleRadius) < 0 || (p.xCord + circleRadius) > windowWidth) {
		return false;
	}
	else if ((p.yCord - circleRadius) < 0 || (p.yCord + circleRadius) > windowHeight) {
		return false;
	}
	else if (distanceFromHorizontal - circleRadius <= 0 ) {
		return false;
	}
	else if (distanceFromVertical - circleRadius <= 0) {
		return false;
	}
	else {
		return true;
	}
}


double distanceBetween(Point p, Circle c) {
	return sqrt(pow(p.xCord - c.origo.xCord, 2) + pow(p.yCord - (windowHeight - c.origo.yCord), 2));
}

void deleteCircles(Point click) {
	for (int i = 0; i < circleContainer.size(); i++) {

		double distance = distanceBetween(click, circleContainer[i]);

		//inside
		if (distance < circleContainer[i].radius) {
			circleContainer.erase(circleContainer.begin() + i);
		}
	}
}


/*
http://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
*/
double randomGenerator() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1.5);
	return dis(gen);
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

		int containerSize = circleContainer.size();

		std::cout << xMouse << "\t" << yMouse << "\t" << containerSize << std::endl;

		double speed = randomGenerator();

		bool validPosition = isCirclePositionValid(Point(xMouse, yMouse));

		if (validPosition == true && containerSize <= 20) {
			Circle circle = Circle(Point(xMouse, windowHeight - yMouse), circleRadius, speed);
			circleContainer.push_back(circle);
			std::cout << "Circle created with ID: " << containerSize << std::endl;
		}
		else if (containerSize > 20) {
			std::cout << "circle container is full." << std::endl;
		}
		else {
			std::cout << "INVALID POSITION" << std::endl;
		}
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		deleteCircles(Point(xMouse, yMouse));
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