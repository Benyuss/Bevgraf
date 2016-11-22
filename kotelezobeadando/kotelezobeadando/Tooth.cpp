#include "Tooth.h"
#include "GL\glut.h"

void Tooth::draw() {
	glColor3f(1.0, 0.5, 0.0);
	glBegin(GL_POLYGON);

	glVertex2d(first.x1 / first.x3, first.x2 / first.x3); //így kapom vissza az eredeti pontot, ami a 2 dimenziós síkon van
	glVertex2d(second.x1 / second.x3, second.x2 / second.x3);
	glVertex2d(third.x1 / third.x3, third.x2 / third.x3);
	glVertex2d(fourth.x1 / fourth.x3, fourth.x2 / fourth.x3);

	glEnd();
}