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
	inline std::vector<Coordinate> getCoordinates();
};

// CONSTRUCTOR
Polygon::Polygon(std::vector<Coordinate> coordinates) 
{
	this->coordinates = coordinates;
};

// GET COORDINATES
inline std::vector<Coordinate> Polygon::getCoordinates()
{
	return this->coordinates;
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
inline std::vector<BoundingBox> Polygon::getCoveringRectangles()
{
	std::vector<BoundingBox> results;

	// center of polygon
	Coordinate center = this->getCentroid();

	// TOP RIGHT CORNER
	// find all points, that are within the top right corner
	// from the centroid onwards
	double maxLatitude = center.latitude;
	double maxLongitude = center.longitude;

	for (Coordinate point : this->coordinates)
	{
		if (point.latitude >= center.latitude && point.longitude >= center.longitude)
		{
			// set maximum latitude
			if (point.latitude >= maxLatitude) 
			{
				maxLatitude = point.latitude;
			}

			// set maximum longitude
			if (point.longitude >= maxLongitude)
			{
				maxLongitude = point.longitude;
			}
		}
	}

	if (maxLongitude != 0.0 && maxLatitude != 0.0)
	{
		// calculate a bounding box for the top right corner
		Coordinate trcTopLeft(center.longitude, maxLatitude);
		Coordinate trcBottomRight(maxLongitude, center.latitude);

		BoundingBox trcBox(trcTopLeft, trcBottomRight);
		results.push_back(trcBox);
	}

	// BOTTOM RIGHT CORNER
	// find all points, that are within the bottom right corner
	// from the centroid onwards
	maxLatitude = center.latitude;
	maxLongitude = center.longitude;

	for (Coordinate point : this->coordinates)
	{
		if (point.latitude <= center.latitude && point.longitude >= center.longitude)
		{
			// set maximum latitude
			if (point.latitude <= maxLatitude) 
			{
				maxLatitude = point.latitude;
			}

			// set maximum longitude
			if (point.longitude >= maxLongitude)
			{
				maxLongitude = point.longitude;
			}
		}
	}

	if (maxLongitude != 0.0 && maxLatitude != 0.0)
	{
		// calculate a bounding box for the bottom right corner
		Coordinate brcTopLeft(center.longitude, center.latitude);
		Coordinate brcBottomRight(maxLongitude, maxLatitude);

		BoundingBox brcBox(brcTopLeft, brcBottomRight);
		results.push_back(brcBox);
	}

	// BOTTOM LEFT CORNER
	// find all points, that are within the bottom left corner
	// from the centroid onwards
	maxLatitude = center.latitude;
	maxLongitude = center.longitude;

	for (Coordinate point : this->coordinates)
	{
		if (point.latitude <= center.latitude && point.longitude <= center.longitude)
		{
			// set maximum latitude
			if (point.latitude <= maxLatitude) 
			{
				maxLatitude = point.latitude;
			}

			// set maximum longitude
			if (point.longitude <= maxLongitude)
			{
				maxLongitude = point.longitude;
			}
		}
	}

	if (maxLongitude != 0.0 && maxLatitude != 0.0)
	{
		// calculate a bounding box for the bottom left corner
		Coordinate blcTopLeft(maxLongitude, center.latitude);
		Coordinate blcBottomRight(center.longitude, maxLatitude);

		BoundingBox blcBox(blcTopLeft, blcBottomRight);
		results.push_back(blcBox);
	}

	// TOP LEFT CORNER
	// find all points, that are within the top left corner
	// from the centroid onwards
	maxLatitude = center.latitude;
	maxLongitude = center.longitude;

	for (Coordinate point : this->coordinates)
	{
		if (point.latitude >= center.latitude && point.longitude <= center.longitude)
		{
			// set maximum latitude
			if (point.latitude >= maxLatitude) 
			{
				maxLatitude = point.latitude;
			}

			// set maximum longitude
			if (point.longitude <= maxLongitude)
			{
				maxLongitude = point.longitude;
			}
		}
	}

	if (maxLongitude != 0.0 && maxLatitude != 0.0)
	{
		// calculate a bounding box for the top left corner
		Coordinate tlcTopLeft(maxLongitude, maxLatitude);
		Coordinate tlcBottomRight(center.longitude, center.latitude);

		BoundingBox tlcBox(tlcTopLeft, tlcBottomRight);
		results.push_back(tlcBox);
	}

	return results;
};

#endif