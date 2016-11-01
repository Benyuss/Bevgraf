#include "Circle.h"

Circle::Circle() {
}

Circle::Circle(Point origo, double radius, double step) {
	this->radius = radius;
	this->origo = origo;
	destination.xCord = origo.xCord > 600 / 2 ? -step : step;
	destination.yCord = origo.yCord > 800 / 2 ? -step : step;
}

void Circle::invertDestination(char b) {
	switch (b) {
	case 'y': destination.yCord *= -1;
	case 'x': destination.xCord *= -1;
	}
}
