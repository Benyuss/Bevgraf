#include "Circle.h"

Circle::Circle() {
}
/*
step -> gyorsas�g (l�p�sk�z)
x -> 0-600(windowWidth main.cpp) -> TODO
y -> 0-800(windowHeight main.cpp) -> TODO
*/
Circle::Circle(Point origo, double radius, double speed) {
	this->radius = radius;
	this->origo = origo;
	destination.xCord = origo.xCord > 600 / 2 ? -speed : speed;
	destination.yCord = origo.yCord > 800 / 2 ? -speed : speed;
}

/*
 x-et vagy y-t invert�ljuk, �gy megfordul az ir�ny. 
 att�l f�gg, hogy a k�r, az oldals� vagy a fels�/als� sz�lekhez �tk�zik.
*/
void Circle::invertDestination(char b) {
	switch (b) {
	case 'y': destination.yCord *= -1;
	case 'x': destination.xCord *= -1;
	}
}

/*
feladatos pdf alapj�n k�sz�lt t�kr�z� fv.
*/
Point Circle::mirroring(Point hasToBeMirror, Point mirror)
{
	double t = (hasToBeMirror.xCord*mirror.xCord + hasToBeMirror.yCord*mirror.yCord) / (mirror.xCord*mirror.xCord + mirror.yCord*mirror.yCord);
	Point c = Point(mirror.xCord*t, mirror.yCord*t);
	Point ac = Point(c.xCord - hasToBeMirror.xCord, c.yCord - hasToBeMirror.yCord);
	Point mirrored = Point(hasToBeMirror.xCord + 2 * ac.xCord, hasToBeMirror.yCord + 2 * ac.yCord);
	return mirrored;
}
