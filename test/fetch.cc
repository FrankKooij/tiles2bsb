#include <iostream>

#include "../fetch.h"

// Fetch::fromUrl
TEST_CASE("Fetch an tile image from url", "[fromUrl]") 
{
	Fetch f;
	std::string result = f.fromUrl("http://a.tile.osm.org/{z}/{x}/{y}.png", 14, 23, 45);

	REQUIRE( result.size() > 0 );
}

// Fetch::saveFromUrl
TEST_CASE("Fetch an tile image from url and save the file to disc", "[saveFromUrl]") 
{
	Fetch f;
	bool result = f.saveFromUrl("http://a.tile.osm.org/{z}/{x}/{y}.png", 14, 23, 45, "tiles/{z}_{x}_{y}.png");

	std::ifstream infile("tiles/14_23_45.png");
    bool isGood = infile.good();

	REQUIRE( isGood == true );
}