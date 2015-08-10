// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// XY.HPP
// Represents an XY Coordinate
//
// Author: Thomas Brüggemann
// ---------------------------------------------------------------------------

#ifndef XY_HPP
#define XY_HPP

// XY
class XY
{
public:
	int x;
	int y;
	XY();
	XY(double x, double y);
};

XY::XY() 
{

};

XY::XY(double x, double y)
{
	this->x = x;
	this->y = y;
};

#endif