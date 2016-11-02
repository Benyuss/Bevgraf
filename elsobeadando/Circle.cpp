#include "Circle.h"

Circle::Circle() {
}
/*
step -> gyorsas�g (l�p�sk�z)
x -> 0-600(windowWidth main.cpp) -> TODO
y -> 0-800(windowHeight main.cpp) -> TODO
*/
Circle::Circle(Point origo, double radius, double step) {
	this->radius = radius;
	this->origo = origo;
	destination.xCord = origo.xCord > 600 / 2 ? -step : step;
	destination.yCord = origo.yCord > 800 / 2 ? -step : step;
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
