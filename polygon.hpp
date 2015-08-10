// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// POLYGON.HPP
// A class representing a polygon with some utility functions to modify and
// query the polygons condition
//
// Author: Thomas Brüggemann
// ---------------------------------------------------------------------------

#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "coordinate.hpp"
#include "boundingbox.hpp"

class Polygon
{
private:
	std::vector<Coordinate> coordinates;

public:
	Polygon(std::vector<Coordinate> coordinates);
	inline Coordinate getCentroid();
	inline std::vector<BoundingBox> getCoveringRectangles();
};

// CONSTRUCTOR
Polygon::Polygon(std::vector<Coordinate> coordinates) 
{
	this->coordinates = coordinates;
};

// GET CENTROID
inline Coordinate Polygon::getCentroid()
{
	Coordinate centroid(0.0, 0.0);

    double signedArea = 0.0;

    double x0 = 0.0; // Current vertex X
    double y0 = 0.0; // Current vertex Y
    double x1 = 0.0; // Next vertex X
    double y1 = 0.0; // Next vertex Y
    double a = 0.0;  // Partial signed area

    // For all vertices except last
    int i = 0;
    for (; i < this->coordinates.size() - 1; i++)
    {
        x0 = this->coordinates[i].longitude;
        y0 = this->coordinates[i].latitude;

        x1 = this->coordinates[i + 1].longitude;
        y1 = this->coordinates[i + 1].latitude;

        a = x0 * y1 - x1 * y0;
        signedArea += a;

        centroid.longitude += (x0 + x1) * a;
        centroid.latitude += (y0 + y1) * a;
    }

    // do last vertex
    x0 = this->coordinates[i].longitude;
    y0 = this->coordinates[i].latitude;

    x1 = this->coordinates[0].longitude;
    y1 = this->coordinates[0].latitude;

    a = x0 * y1 - x1 * y0;
    signedArea += a;

    centroid.longitude += (x0 + x1) * a;
    centroid.latitude += (y0 + y1) * a;

    signedArea *= 0.5;
    centroid.longitude /= (6.0 * signedArea);
    centroid.latitude /= (6.0 * signedArea);

    return centroid;
};

// GET COVERING RECTANGLES
inline std::vector<BoundingBox> getCoveringRectangles()
{
	std::vector<BoundingBox> results;

	// center of polygon
	Coordinate center = this->getCentroid();

	// TOP RIGHT CORNER
	std::vector<Coordinate> topRightCorner;

	// find all points, that are within the top right corner
	// from the centroid onwards
	double maxLatitude = 0.0;
	double maxLongitude = 0.0;

	for(Coordinate point : this->coordinates)
	{
		if (point.latitude >= center.latitude &&
			point.longitude >= center.longitude)
		{
			topRightCorner.push_back(point);

			// set maximum latitude
			if(maxLatitude >= point.latitude) 
			{
				maxLatitude = point.latitude;
			}

			// set maximum longitude
			if(maxLongitude >= point.longitude)
			{
				maxLongitude = point.longitude;
			}
		}
	}

	// calculate a bounding box for the top right corner
	Coordinate trcTopLeft(center.longitude, maxLatitude);
	Coordinate trcBottomRight(maxLongitude, center.latitude);

	BoundingBox trcBox(trcTopLeft, trcBottomRight);
	results.push_back(trcBack);

	// BOTTOM RIGHT CORNER

	return results;
};

#endif