// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// BOUNDINGBOX.HPP
// Class represents the bounding box by setting topleft and bottomright 
// coordinates
//
// Author: Thomas Brüggemann
// ---------------------------------------------------------------------------

#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include "coordinate.hpp"
#include "patches.hpp"
#include <string>

class BoundingBox
{
private:

public:
	BoundingBox();
	BoundingBox(Coordinate topLeft, Coordinate bottomRight);
	Coordinate topLeft;
	Coordinate bottomRight;
	std::string toString();
	std::vector<Coordinate> getCoordinates();
};

// CONSTRUCTOR
BoundingBox::BoundingBox()
{

};

// CONSTRUCTOR
BoundingBox::BoundingBox(Coordinate topLeft, Coordinate bottomRight)
{
	this->topLeft = topLeft;
	this->bottomRight = bottomRight;
};

// TO STRING
std::string BoundingBox::toString() 
{
	std::string result = "[" + topLeft.toString() + ", " + bottomRight.toString() + "]";
	return result;
};

// GET COORDINATES
std::vector<Coordinate> BoundingBox::getCoordinates()
{
	std::vector<Coordinate> coordinates;

	// top left
	coordinates.push_back(this->topLeft);

	// top right
	Coordinate topRight(this->bottomRight.longitude, this->topLeft.latitude);
	coordinates.push_back(topRight);

	// bottom right
	coordinates.push_back(bottomRight);

	// bottom left
	Coordinate bottomLeft(this->topLeft.longitude, this->bottomRight.latitude);
	coordinates.push_back(bottomLeft);

	return coordinates;
};

#endif