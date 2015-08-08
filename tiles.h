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

#ifndef TILES_H
#define TILES_H

#include <math.h>
#include <utility>

class Tiles
{
private:
	inline int long2TileX(double lon, int z);
	inline int lat2TileY(double lat, int z);

public:
	inline std::pair<int, int> fromCoordinate(int zoom, double lon, double lat);
};

// LONG 2 TILE X
inline int Tiles::long2TileX(double lon, int z) 
{ 
	return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, z))); 
};
 
// LAT 2 TILE Y
inline int Tiles::lat2TileY(double lat, int z)
{ 
	return (int)(floor((1.0 - log( tan(lat * M_PI/180.0) + 1.0 / cos(lat * M_PI/180.0)) / M_PI) / 2.0 * pow(2.0, z))); 
};

// FROM COORDINATE
inline std::pair<int, int> Tiles::fromCoordinate(int zoom, double lon, double lat)
{
	int x = this->long2TileX(lon, zoom);
	int y = this->lat2TileY(lat, zoom);
	std::pair<int, int> result(x, y);

	return result;
};

#endif