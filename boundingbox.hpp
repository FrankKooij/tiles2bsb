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

class BoundingBox
{
private:

public:
	BoundingBox();
	BoundingBox(Coordinate topLeft, Coordinate bottomRight);
	Coordinate topLeft;
	Coordinate bottomRight;
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

#endif