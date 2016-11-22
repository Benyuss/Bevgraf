#include "pumpkin.h"
#include <vector>
#include <GL\glut.h>
#include <random>

const int windowWidth = 800;
const int windowHeight = 600;
int keyStates[256];

std::vector<Pumpkin> pumpkinContainer; //ez fogja tárolni a tököket

//Coordinates to start with

//outline
Point A = Point(0, 0.512);
Point B = Point(0.454, 0.565);
Point C = Point(0.815, 0.33);
Point D = Point(0.907, -0.313);
Point E = Point(0.411, -0.7);
Point F = Point(0, -0.7);
Point G = Point(-0.411, -0.7);
Point H = Point(-0.907, -0.313);
Point I = Point(-0.815, 0.33);
Point J = Point(-0.454, 0.565);

//eyeLeft
Point K = Point(-0.473, 0.045);
Point L = Point(-0.155, 0.028);
Point M = Point(-0.208, 0.32);

//eyeRight
Point N = Point(0.196, 0.038);
Point O = Point(0.52, 0.055);
Point P = Point(0.312, 0.356);

Outline outline = Outline(A, B, C, D, E, F, G, H, I, J);
Eye eyeLeft = Eye(K, L, M);
Eye eyeRight = Eye(N, O, P);


void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
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

void glDrawOutline(Outline outLineToDraw) {

	glColor3d(1.0, 1.0, 1.0);
	glBegin(GL_LINES);

	glVertex2d(outLineToDraw.A.xCord, outLineToDraw.A.yCord);
	glVertex2d(outLineToDraw.B.xCord, outLineToDraw.B.yCord);
	glVertex2d(outLineToDraw.C.xCord, outLineToDraw.C.yCord);
	glVertex2d(outLineToDraw.D.xCord, outLineToDraw.D.yCord);
	glVertex2d(outLineToDraw.E.xCord, outLineToDraw.E.yCord);
	glVertex2d(outLineToDraw.F.xCord, outLineToDraw.F.yCord);
	glVertex2d(outLineToDraw.G.xCord, outLineToDraw.G.yCord);
	glVertex2d(outLineToDraw.H.xCord, outLineToDraw.H.yCord);
	glVertex2d(outLineToDraw.I.xCord, outLineToDraw.I.yCord);
	glVertex2d(outLineToDraw.J.xCord, outLineToDraw.J.yCord);
	
	glEnd();
}

void glDrawEyes(Eye eyeToDraw) {

	glColor3d(1.0, 1.0, 1.0);
	glBegin(GL_LINES);

	glVertex2d(eyeToDraw.first.xCord, eyeToDraw.first.yCord);
	glVertex2d(eyeToDraw.second.xCord, eyeToDraw.second.yCord);
	glVertex2d(eyeToDraw.third.xCord, eyeToDraw.third.yCord);

	glEnd();
}

void glDrawPumpkin(Pumpkin pumpkin) {
	glDrawOutline(outline);
	glDrawEyes(eyeLeft);
	glDrawEyes(eyeRight);
}

Pumpkin initOutline() {
	
}

Pumpkin initPumpkin(Point origo) {

}


void glMouseControl(int button, int state, int xMouse, int yMouse) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		Point origo = Point(xMouse, yMouse);

		initPumpkin(origo);


		pumpkinContainer.push_back( Pumpkin(origo, outline, eyeLeft , eyeRight) );
	}
}

/*
mivel a mainLoop folyamatosan fut, ez is folyamatosan futni fog.
Ez jeleníti meg a rajzolt dolgokat, illetve felel a köröket tartalmazó vectorok tárolásáért.
*/
void display() {

	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < pumpkinContainer.size(); i++) {
		glDrawPumpkin(pumpkinContainer[i]);
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

	glutDisplayFunc(display);

	glutMouseFunc(glMouseControl);

	glutMainLoop();

	return 0;
}