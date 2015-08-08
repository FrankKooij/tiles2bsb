#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.h"
#include "../tiles.h"

// TILES::fromCoordinate
TEST_CASE( "Map a coordinate with a zoomlevel to X and Y tiles", "[fromCoordinate]") 
{

	double lat = 51.272376;
	double lon = 6.271966;

	Tiles t;
	std::pair<int, int> xy = t.fromCoordinate(10, lon, lat);

    REQUIRE( xy.first == 529 );
    REQUIRE( xy.second == 341 );
}