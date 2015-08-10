// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// COORDINATE.HPP
// Represents a latitude / longitude coordinate
//
// Author: Thomas Brüggemann
// ---------------------------------------------------------------------------

#ifndef COORDINATE_HPP
#define COORDINATE_HPP

class Coordinate
{
public:
	double longitude;
	double latitude;
	Coordinate();
	Coordinate(double lon, double lat);
};

Coordinate::Coordinate()
{

};

Coordinate::Coordinate(double lon, double lat)
{
	this->longitude = lon;
	this->latitude = lat;
};

#endif