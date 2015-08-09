
#include "catch.hpp"
#include "../image.hpp"

TEST_CASE("Fetch 20 tiles from a bounding box and store them in /tiles direcotry", "[stitchTogether]") 
{
	// init bounding box
	Coordinate topLeft(6.265175, 51.282414);
	Coordinate bottomRight(6.282084, 51.267595);

	int zoom = 16;

	Tiles t;
	Fetch f;

	// find XY coordinates
	TilesResult tiles = t.fromBoundingBox(zoom, topLeft, bottomRight);

	REQUIRE( tiles.coordinates.size() == 20 );

	for(XY xy : tiles.coordinates) 
	{
		// download each of these tiles
		bool isGood = f.saveFromUrl("http://a.tile.osm.org/{z}/{x}/{y}.png", zoom, xy.first, xy.second, "tiles/{z}_{x}_{y}.png");
		REQUIRE( isGood == true );
	}

    // stitch images together
    Image i;
    i.stitchTogether(tiles, zoom, "tiles/map.tif");
}
