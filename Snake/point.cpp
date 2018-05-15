#include "point.h"
#include "stdafx.h"



point::point()
{
}


double point::getX()
{
	double x = Xcoord;
	return x;
}

double point::getY()
{
	double y = Ycoord;
	return y;
}

void point::setX(double x)
{
	Xcoord = x;
}

void point::setY(double y)
{
	Ycoord = y;
}






