
#include "catch.hpp"
#include "../bsb.hpp"

TEST_CASE("Convert a tiff to bsb kap file", "[fromTiff]") 
{
	BSB b;
	bool result = b.fromTiff("tiles/map.tif");

	REQUIRE( result == true );
}