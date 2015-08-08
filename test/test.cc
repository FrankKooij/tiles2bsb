#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <iostream>

#include "catch.h"
#include "../tiles.h"

// Tiles::fromCoordinate
TEST_CASE("Map a coordinate with a zoomlevel to X and Y tiles", "[fromCoordinate]") 
{

	double lat = 51.272376;
	double lon = 6.271966;

	Tiles t;
	std::pair<int, int> xy = t.fromCoordinate(10, lon, lat);

    REQUIRE( xy.first == 529 );
    REQUIRE( xy.second == 341 );
}

// Tiles::fromCoordinate
TEST_CASE("Map a coordinate object with a zoomlevel to X and Y tiles", "[fromCoordinate]") 
{

	double lat = 51.272376;
	double lon = 6.271966;

	Coordinate coord(lon, lat);

	Tiles t;
	std::pair<int, int> xy = t.fromCoordinate(10, coord);

    REQUIRE( xy.first == 529 );
    REQUIRE( xy.second == 341 );
}

// Tiles::fromBoundingBox
TEST_CASE("Map a bounding box to XY coordinates", "[fromBoundingBox]")
{
	Coordinate topLeft(6.265175, 51.282414);
	Coordinate bottomRight(6.282084, 51.267595);

	Tiles t;

	std::vector<XY> tiles = t.fromBoundingBox(16, topLeft, bottomRight);

	REQUIRE( tiles.size() == 20 );
}