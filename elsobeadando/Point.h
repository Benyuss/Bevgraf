#pragma once

class Point {
public:
	
	Point(double x, double y) : xCord(x), yCord(y) {
		//inicializ�ci�s lista, konstruktor t�rzse el�tt fut, mint egy static blokk
	}

	double xCord;
	double yCord;

};