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

#include <string>
#include "patches.hpp"

class Coordinate
{
public:
	double longitude;
	double latitude;
	Coordinate();
	Coordinate(double lon, double lat);
	inline std::string toString();
	inline int isLeft(Coordinate startLine, Coordinate endLine);
};

Coordinate::Coordinate()
{

};

Coordinate::Coordinate(double lon, double lat)
{
	this->longitude = lon;
	this->latitude = lat;
};

// TO STRING
inline std::string Coordinate::toString()
{
	std::string result = "(" + patches::to_string(this->longitude) + ", " + patches::to_string(this->latitude) + ")";
	return result;
};

// IS LEFT
// Return: >0 for point left of the line through start and end
//         =0 for point on the line
//         <0 for point right of the line
inline int Coordinate::isLeft(Coordinate startLine, Coordinate endLine)
{
	return ((endLine.longitude - startLine.longitude) * (this->latitude - startLine.latitude)
            - (this->longitude -  startLine.longitude) * (endLine.latitude - startLine.latitude));
};

#endif