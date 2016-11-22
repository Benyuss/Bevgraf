#include "Utility.h"

Point sumPoints(Point origo, Point point)
{
	double xResult = origo.xCord + point.xCord;
	double yResult = origo.yCord + point.yCord;

	return Point(xResult, yResult);
}
