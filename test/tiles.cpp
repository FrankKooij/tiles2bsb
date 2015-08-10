#include "catch.hpp"
#include "../tiles.hpp"
#include "../xy.hpp"
#include "../coordinate.hpp"
#include <vector>

// Tiles::fromCoordinate
TEST_CASE("Map a coordinate with a zoomlevel to X and Y tiles", "[fromCoordinate]") 
{

	double lat = 51.272376;
	double lon = 6.271966;

	Tiles t;
	XY xy = t.fromCoordinate(10, lon, lat);

    REQUIRE( xy.x == 529 );
    REQUIRE( xy.y == 341 );
}

// Tiles::fromCoordinate
TEST_CASE("Map a coordinate object with a zoomlevel to X and Y tiles", "[fromCoordinate]") 
{

	double lat = 51.272376;
	double lon = 6.271966;

	Coordinate coord(lon, lat);

	Tiles t;
	XY xy = t.fromCoordinate(10, coord);

    REQUIRE( xy.x == 529 );
    REQUIRE( xy.y == 341 );
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

// Tiles::fromPolygon
TEST_CASE("Extract rectangles from polygon", "[fromPolygon")
{
	std::vector<Coordinate> coordinates;

	Coordinate a(3.849678039550781, 51.742549461489034);
	Coordinate b(3.8905334472656246, 51.76996448812039);
	Coordinate c(3.9464950561523433, 51.760190496399375);
	Coordinate d(3.93310546875, 51.717032167390364);
	Coordinate e(3.8544845581054683, 51.72171141639037);

	coordinates.push_back(a);
	coordinates.push_back(b);
	coordinates.push_back(c);
	coordinates.push_back(d);
	coordinates.push_back(e);

	Tiles t;
	std::vector<TilesResult> results = t.fromPolygon(16, coordinates);
}