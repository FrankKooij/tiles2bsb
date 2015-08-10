// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// TILES.HPP
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

#include "coordinate.hpp"
#include "boundingbox.hpp"
#include "polygon.hpp"
#include "xy.hpp"

// TILES RESULT
class TilesResult
{
public:
	std::vector<XY> coordinates;
	int width;
	int height;

	Coordinate topLeftEdge;
	Coordinate bottomRightEdge;
};

// TILES
class Tiles
{
private:
	inline int long2TileX(double lon, int z);
	inline int lat2TileY(double lat, int z);

public:
	inline XY fromCoordinate(int zoom, Coordinate coord);
	inline XY fromCoordinate(int zoom, double lon, double lat);
	inline std::vector<TilesResult> fromPolygon(int zoom, std::vector<Coordinate> polygonPoints);
	inline TilesResult fromBoundingBox(int zoom, BoundingBox box);
	inline TilesResult fromBoundingBox(int zoom, Coordinate topLeft, Coordinate bottomRight);
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
	return this->fromCoordinate(zoom, coord.longitude, coord.latitude);
};

inline XY Tiles::fromCoordinate(int zoom, double lon, double lat)
{
	// map latitude and longitude to XY coordinates
	int x = this->long2TileX(lon, zoom);
	int y = this->lat2TileY(lat, zoom);

	// return the result
	XY result(x, y);

	return result;
};

// FROM POLYGON
inline std::vector<TilesResult> Tiles::fromPolygon(int zoom, std::vector<Coordinate> polygonPoints)
{
	std::vector<TilesResult> results;

	// cover the polygon with rectangles
	Polygon p(polygonPoints);
	std::vector<BoundingBox> boxes = p.getCoveringRectangles();

	// get tile frames from boxes
	for(BoundingBox box : boxes)
	{
		results.push_back(this->fromBoundingBox(zoom, box));
	}

	return results;
};

// FROM BOUNDING BOX
inline TilesResult Tiles::fromBoundingBox(int zoom, BoundingBox box)
{
	return this->fromBoundingBox(zoom, box.topLeft, box.bottomRight);
};

inline TilesResult Tiles::fromBoundingBox(int zoom, Coordinate topLeft, Coordinate bottomRight)
{
	// map bounding box coordinates to xy
	XY topLeftXY = this->fromCoordinate(zoom, topLeft);
	XY bottomRightXY = this->fromCoordinate(zoom, bottomRight);

	std::vector<XY> results;

	// loop the x values from left to right
	for(int y = topLeftXY.y; y <= bottomRightXY.y; y++) 
	{
		// loop the y values from top to bottom
		for(int x = topLeftXY.x; x <= bottomRightXY.x; x++) 
		{
			// add XY coordinate to results vector
			XY xyValue(x, y);
			results.push_back(xyValue);
		}
	}

	// try to explore the left bound of longitude of the top left tile
	// because we found the tile (x,y) coordinate, that hosts the given lat/lon
	// coordinate, but we must find the real lat/lon bounds of the tile in order
	// to correctly compute a calibrated .cap file later
	double exploreLeftLon = topLeft.longitude;
	const double pumpingValue = 0.00000001;
	XY exploreLeftX;
	do {
		exploreLeftLon -= pumpingValue;
		exploreLeftX = this->fromCoordinate(zoom, exploreLeftLon, topLeft.latitude);
	}
	while(exploreLeftX.x >= topLeftXY.x);

	// explore top left latitude bound of tile
	double exploreLeftLat = topLeft.latitude;
	XY exploreLeftY;
	do {
		exploreLeftLat += pumpingValue;
		exploreLeftY = this->fromCoordinate(zoom, topLeft.longitude, exploreLeftLat);
	}
	while(exploreLeftY.y >= topLeftXY.y);

	// explore bottom right longitude bound of tile
	double exploreRightLon = bottomRight.longitude;
	XY exploreRightX;
	do {
		exploreRightLon += pumpingValue;
		exploreRightX = this->fromCoordinate(zoom, exploreRightLon, bottomRight.latitude);
	}
	while(bottomRightXY.x >= exploreRightX.x);

	// explore bottm right latitude bound of tile
	double exploreRightLat = topLeft.latitude;
	XY exploreRightY;
	do {
		exploreRightLat -= pumpingValue;
		exploreRightY = this->fromCoordinate(zoom, bottomRight.longitude, exploreRightLat);
	}
	while(bottomRightXY.y >= exploreRightY.y);

	// merge everything together in a tiles result object
	TilesResult tilesResult;
	tilesResult.coordinates = results;
	tilesResult.width = abs(topLeftXY.x - bottomRightXY.x) + 1;
	tilesResult.height = abs(topLeftXY.y - bottomRightXY.y) + 1;

	Coordinate topLeftEdge(exploreLeftLon, exploreLeftLat);
	tilesResult.topLeftEdge = topLeftEdge;

	Coordinate bottomRightEdge(exploreRightLon, exploreRightLat);
	tilesResult.bottomRightEdge = bottomRightEdge;

	return tilesResult;
};

#endif