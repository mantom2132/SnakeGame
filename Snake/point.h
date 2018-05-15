#pragma once
class point
{
private:
	double Xcoord;
	double Ycoord;
public:
	point();
	point(double newX, double newY);
	double getX();
	double getY();
	void setX(double x);
	void setY(double y);
};
#endif


