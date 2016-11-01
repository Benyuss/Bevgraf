#pragma once

class Point {
public:
	
	Point(double x, double y) : xCord(x), yCord(y) {
		//inicializációs lista, konstruktor törzse elõtt fut, mint egy static blokk
	}

	double xCord;
	double yCord;

};