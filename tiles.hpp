// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// TILES.H
// Tiles class can map geocoordinates to x and y coordinates, given a certain
// zoomlevel in order to open ZXY tiles from tileservers.
//
// Author: Thomas Brüggemann
// ---------------------------------------------------------------------------

#ifndef TILES_HPP
#define TILES_HPP

#include <math.h>
#include <utility>
#include <vector>

typedef std::pair<double, double> Coordinate;
typedef std::pair<int, int> XY;

class Tiles
{
private:
	inline int long2TileX(double lon, int z);
	inline int lat2TileY(double lat, int z);

public:
	inline XY fromCoordinate(int zoom, Coordinate coord);
	inline XY fromCoordinate(int zoom, double lon, double lat);
	inline std::vector<XY> fromBoundingBox(int zoom, Coordinate topLeft, Coordinate bottomRight);
};

// LONG 2 TILE X
inline int Tiles::long2TileX(double lon, int z) 
{ 
	// return the X part of a XY coordinate from a longitude geocoordinate value
	return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, z))); 
};
 
// LAT 2 TILE Y
inline int Tiles::lat2TileY(double lat, int z)
{ 
	// return the Y part of a XY coordinate from a latitude geocoordinate value
	return (int)(floor((1.0 - log( tan(lat * M_PI/180.0) + 1.0 / cos(lat * M_PI/180.0)) / M_PI) / 2.0 * pow(2.0, z))); 
};

// FROM COORDINATE
inline XY Tiles::fromCoordinate(int zoom, Coordinate coord)
{
	return this->fromCoordinate(zoom, coord.first, coord.second);
};

inline XY Tiles::fromCoordinate(int zoom, double lon, double lat)
{
	// map latitude and longitude to XY coordinates
	int x = this->long2TileX(lon, zoom);
	int y = this->lat2TileY(lat, zoom);

	// return the result
	std::pair<int, int> result(x, y);

	return result;
};

// FROM BOUNDING BOX
inline std::vector<XY> Tiles::fromBoundingBox(int zoom, Coordinate topLeft, Coordinate bottomRight)
{
	// map bounding box coordinates to xy
	XY topLeftXY = this->fromCoordinate(zoom, topLeft);
	XY bottomRightXY = this->fromCoordinate(zoom, bottomRight);

	std::vector<XY> results;

	// loop the x values from left to right
	for(int x = topLeftXY.first; x <= bottomRightXY.first; x++) 
	{
		// loop the y values from top to bottom
		for(int y = topLeftXY.second; y <= bottomRightXY.second; y++) {

			// add XY coordinate to results vector
			XY xyValue(x, y);
			results.push_back(xyValue);
		}
	}

	return results;
};

#endif