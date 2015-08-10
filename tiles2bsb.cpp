// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// TILES2BSB.CC
// Main program to transform a range of tiles from a tileserver into a BSB
// formatted .cap/.kap file for usage in nautical charts navigation software
//
// Author: Thomas Brüggemann
// ---------------------------------------------------------------------------

#include <iostream>
#include <utility>

#include "tiles.hpp"
#include "fetch.hpp"
#include "image.hpp"
#include "bsb.hpp"
#include "elapsed.hpp"
#include "crayons.hpp"

Crayon GREY(FG_LIGHT_GRAY);
Crayon DEFAULT(FG_DEFAULT);

int main()
{
	std::cout << "=== TILES-2-BSB v1.0 ===" << std::endl;
	Elapsed e; e.Start();

	// init bounding box
	Coordinate topLeft(6.265175, 51.282414);
	Coordinate bottomRight(6.282084, 51.267595);

	int zoom = 16;

	Tiles t;
	Fetch f;

	// find XY coordinates
	TilesResult tiles = t.fromBoundingBox(zoom, topLeft, bottomRight);

	for(XY xy : tiles.coordinates) 
	{
		// download each of these tiles
		f.saveFromUrl("http://a.tile.osm.org/{z}/{x}/{y}.png", zoom, xy.first, xy.second, "tiles/{z}_{x}_{y}.png");
	}

	// display stats
	double downloadMs = e.End();
	std::cout << GREY << "Download of " << tiles.coordinates.size() <<  " tiles ran " << downloadMs << "ms" << DEFAULT << std::endl;

	e.Start();

	// stitch images together
    Image i;
    i.stitchTogether(tiles, zoom, "tiles/map.png");

    // display stats
	double stitchingMs = e.End();
	std::cout << GREY << "Stitching of " << tiles.coordinates.size() <<  " images ran " << stitchingMs << "ms" << DEFAULT << std::endl;

	BSB b;
	bool result = b.fromPNG("tiles/map.png", "map.kap", topLeft, bottomRight);

  	return 0;
}
