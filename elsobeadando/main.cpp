#include <GL\glut.h>
#include "Line.h"
#include "Point.h"
#include "Circle.h"
#define _USE_MATH_DEFINES
#include <cmath> //PI
#include <iostream> //egérkatt log
#include <vector> //köröket tároljuk benne

const int windowWidth = 800;
const int windowHeight = 600;
int keyStates[256];
double offset = 0.01; //kör rajzolásának lépésköze
double circleRadius = 25;
std::vector <Circle> circleContainer;

Line verticalLine = Line(Point(400, 0), Point(400, 600));
Line horizontalLine = Line(Point(0, 300), Point(800, 300));

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
}

bool isPointOnLeftSideOfLine(Point a, Line line)
{
	return (line.b.xCord - line.a.xCord) * (a.yCord - line.a.yCord) - (line.b.yCord - line.a.yCord) * (a.xCord - line.a.xCord) > 0;
}

void glDrawVerticalLines() {
	glColor3d(1.0, 0.0, 0.0);

	glBegin(GL_LINES);

	glVertex2d(verticalLine.a.xCord, verticalLine.a.yCord);
	glVertex2d(verticalLine.b.xCord, verticalLine.b.yCord);

	glEnd();
}

void glDrawHorizontalLines() {
	glColor3d(0.0, 1.0, 0.0);

	glBegin(GL_LINES);

	glVertex2d(horizontalLine.a.xCord, horizontalLine.a.yCord);
	glVertex2d(horizontalLine.b.xCord, horizontalLine.b.yCord);

	glEnd();

}

void keyPressed(unsigned char key, int x, int y) {
	keyStates[key] = 1;
}

void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = 0;
}

void keyOperations() {

	if (keyStates['a']) {
		if (verticalLine.a.xCord <= 800 && verticalLine.b.xCord >= 0) {
			verticalLine.a.xCord++;
			verticalLine.b.xCord--;
		}

	}

	if (keyStates['d']) {
		if (verticalLine.a.xCord >= 0 && verticalLine.b.xCord <= 800) {
			verticalLine.a.xCord--;
			verticalLine.b.xCord++;
		}
	}

	if (keyStates['s']) {
		if (horizontalLine.a.yCord <= 600 && horizontalLine.b.yCord >= 0) {
			horizontalLine.a.yCord++;
			horizontalLine.b.yCord--;
		}
	}

	if (keyStates['w']) {
		if (horizontalLine.a.yCord >= 0 && horizontalLine.b.yCord <= 600) {
			horizontalLine.a.yCord--;
			horizontalLine.b.yCord++;
		}
	}

	glutPostRedisplay();
}

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
		glColor3d(0.0, 0.0, 0.0);
	}
}

void glSetPointsColor(Point p) {
	bool vertical = isPointOnLeftSideOfLine(p, verticalLine);
	bool horizontal = isPointOnLeftSideOfLine(p, horizontalLine);

	glChangeColors(vertical, horizontal);
}

void glPoint(Point p) {
	glSetPointsColor(p);
	glVertex2d(p.xCord, p.yCord);
}

void glDrawPoints() {
	glEnable(GL_POINT_SMOOTH);
	glPointSize(2.0);

	glBegin(GL_POINTS);

	for (double x = 0; x < windowWidth; x += 8) {
		for (double y = 0; y < windowHeight; y += 8) {
			glPoint(Point(x, y));
		}
	}

	glEnd();
}

void glDrawCircle(Circle circle) {
	glColor3d(1.0, 1.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);

	for (double x = 0; x < 2 * M_PI; x += offset) {
		glVertex2d(circle.origo.xCord + circleRadius * cos(x), circle.origo.yCord + circleRadius * sin(x));
	}

	glEnd();
}

float distanceOfPointsFromLine(Line l, Point p)
{
	float abyDiff = l.a.yCord - l.b.yCord;
	float baxDiff = l.b.xCord - l.a.xCord;

	return fabs(((abyDiff)*l.a.xCord + (baxDiff)*l.a.yCord - (abyDiff)*p.xCord - (baxDiff)*p.yCord) / sqrt((abyDiff)*(abyDiff)+(baxDiff)*(baxDiff)));
}
Point mirroring(Point hasToBeMirror, Point mirror)
{
	float t = (hasToBeMirror.xCord*mirror.xCord + hasToBeMirror.yCord*mirror.yCord) / (mirror.xCord*mirror.xCord + mirror.yCord*mirror.yCord);
	Point c = Point(mirror.xCord*t, mirror.yCord*t);
	Point ac = Point(c.xCord - hasToBeMirror.xCord, c.yCord - hasToBeMirror.yCord);
	Point mirrored = Point(hasToBeMirror.xCord + 2 * ac.xCord, hasToBeMirror.yCord + 2 * ac.yCord);
	return mirrored;
}

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

void glMouseControl(int button, int state, int xMouse, int yMouse) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		std::cout << xMouse << std::endl << yMouse;

		double step = rand() % 1 + 0.6;

		Circle circle = Circle(Point(xMouse, windowHeight - yMouse), circleRadius, step);
		circleContainer.push_back(circle);
	}
}

void display() {

	keyOperations();

	glClear(GL_COLOR_BUFFER_BIT);

	glDrawVerticalLines();
	glDrawHorizontalLines();

	glDrawPoints();

	for (auto it = circleContainer.begin(); it != circleContainer.end(); it++) {
		glDrawCircle(*it);
	}

	move();

	glutSwapBuffers(); //bufferváltás.lel
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