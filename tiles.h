#ifndef TILES_H
#define TILES_H

#include <math>
#include <utility>

class Tiles
{
private:
	inline int long2TileX(double lon, int z);
	inline int lat2TileY(double lat, int z);

public:
	inline std::pair<int, int> fromCoordinate( int zoom, double lon, double lat);
};

// FROM COORDINATE
inline std::pair<int, int> Tiles::fromCoordinate( int zoom, double lon, double lat)
{
	int x = this.long2TileX(lon, zoom);
	int y = this.lat2TileY(lat, zoom);
	std::pair<int, int> result(x, y);

	return result;
};

// LONG 2 TILE X
inline int long2TileX(double lon, int z) 
{ 
	return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, z))); 
};
 
// LAT 2 TILE Y
inline int lat2TileY(double lat, int z)
{ 
	return (int)(floor((1.0 - log( tan(lat * M_PI/180.0) + 1.0 / cos(lat * M_PI/180.0)) / M_PI) / 2.0 * pow(2.0, z))); 
};

#endif