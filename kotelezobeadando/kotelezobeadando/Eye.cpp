#include "Eye.h"

void Eye::draw() {
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);

		glVertex2d(first.x1 / first.x3, first.x2 / first.x3); //�gy kapom vissza az eredeti pontot, ami a 2 dimenzi�s s�kon van
		glVertex2d(second.x1 / second.x3, second.x2 / second.x3);
		glVertex2d(third.x1 / third.x3, third.x2 / third.x3);

		glEnd();
}