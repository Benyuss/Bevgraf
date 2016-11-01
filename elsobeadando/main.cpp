#include <GL\glut.h>
#include "Line.h"
#include "Point.h"

const int windowWidth = 800;
const int windowHeight = 600;
int keyStates[256];

Line verticalLine = Line(Point(400, 0), Point(400, 600));
Line horizontalLine = Line(Point(0, 300), Point(800, 300));

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
}

bool isPointOnLeftSideOfLine(Point a, Line line)
{
	return (line.a.xCord - line.a.xCord) * (a.yCord - line.a.yCord) - (line.b.yCord - line.a.yCord) * (a.xCord - line.a.xCord) > 0;
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
			glPoint(Point(x,y));
		}
	}

	glEnd();
}

void display() {

	keyOperations();

	glClear(GL_COLOR_BUFFER_BIT);
	
	glDrawVerticalLines();
	glDrawHorizontalLines();

	glDrawPoints();

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

	glutMainLoop();

	return 0;
}