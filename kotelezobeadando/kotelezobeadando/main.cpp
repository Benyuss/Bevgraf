#include "pumpkin.h"
#include <vector>
#include <GL\glut.h>
#include <random>

std::vector<Pumpkin> pumpkinContainer; //ez fogja tárolni a tököket

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
}

void update(int n) {
	Pumpkin current;
	pumpkinContainer.push_back(current);

	glutPostRedisplay();
	glutTimerFunc(1000, update, 0);
}

/*
mivel a mainLoop folyamatosan fut, ez is folyamatosan futni fog.
Ez jeleníti meg a rajzolt dolgokat, illetve felel a köröket tartalmazó vectorok tárolásáért.
*/
void display() {

	glClear(GL_COLOR_BUFFER_BIT);

	for (auto it = pumpkinContainer.begin(); it != pumpkinContainer.end(); it++) {
		(*it).draw();
	}

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowPosition(50, 100);

	glutInitWindowSize(windowWidth, windowHeight);

	glutCreateWindow("kotelezobeadando");

	init();

	glutTimerFunc(1000, update, 0);

	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}