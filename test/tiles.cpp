#include "catch.hpp"
#include "../tiles.hpp"

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
	TilesResult result = t.fromBoundingBox(16, topLeft, bottomRight);

	REQUIRE( result.coordinates.size() == 20 );
}