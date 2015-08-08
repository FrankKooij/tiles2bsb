#include <iostream>

#include "../fetch.h"

// Fetch::fromUrl
TEST_CASE("Fetch an tile image from url", "[fromUrl]") 
{
	Fetch f;
	bool result = f.fromUrl("http://a.tile.osm.org/{z}/{x}/{y}.png", 14, 23, 45);

	REQUIRE( result == true );
}