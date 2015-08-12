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
#include <string>
#include <utility>

#include "tiles.hpp"
#include "fetch.hpp"
#include "image.hpp"
#include "bsb.hpp"
#include "polygon.hpp"
#include "geojson.hpp"
#include "boundingbox.hpp"
#include "coordinate.hpp"
#include "elapsed.hpp"
#include "crayons.hpp"
#include "config.hpp"

Crayon GREY(FG_LIGHT_GRAY);
Crayon DEFAULT(FG_DEFAULT);
Crayon GREEN(FG_GREEN);
Crayon RED(FG_RED);

int main(int argc, char* argv[])
{
	std::cout << "=== TILES-2-BSB v1.0 ===" << std::endl;

	if (argc < 2) 
	{ 
		std::cout << RED << "Error: Missing Parameters!" << DEFAULT << std::endl;
		std::cout << "Usage: ./tiles2bsb path/to/config.json" << std::endl;
		exit(1);
	}

	// load config from json file
	std::string confFile(argv[1]);
	Config conf(confFile);

	Elapsed total; 
	total.Start();

	int zoom = conf.zoom;

	// read geojson from input string
	Tiles tiles;
	Geojson gjson;
	Fetch f;

	std::vector<Polygon> polygons = gjson.parseFile(conf.geojsonPath);

	// loop all the available polygons
	int j = 1;
	for (auto polyg : polygons)
	{
		Elapsed e; e.Start();
		std::cout << "========================" << std::endl;
		std::cout << "Start processing of Polygon!" << std::endl;

		std::vector<TilesResult> tileResults = tiles.fromPolygon(zoom, polyg);

		// loop all tile mapping results
		for(auto tiles : tileResults)
		{
			std::cout << "------------------------" << std::endl;

			// loop all xy coordinates to download
			for(XY xy : tiles.coordinates) 
			{
				// download each of these tiles
				f.saveFromUrl(conf.tileServerUrl, zoom, xy.x, xy.y, "tiles/{z}_{x}_{y}.png");
			}

			std::cout << GREEN << "Tile download ... OK" << DEFAULT << std::endl;

			// display stats
			double downloadMs = e.End();
			std::cout << GREY << "Download of " << tiles.coordinates.size() <<  " tiles ran " << downloadMs << "ms" << DEFAULT << std::endl;

			e.Start();

			// stitch images together
			Image i;
			bool stitchResult = i.stitchTogether(tiles, zoom, "tiles/map_" + conf.name +  "_" + patches::to_string(j) + ".png");
			if(stitchResult == true) {
				std::cout << GREEN << "Image stitching ... OK" << DEFAULT << std::endl;
			}

			// display stats
			double stitchingMs = e.End();
			std::cout << GREY << "Stitching of " << tiles.coordinates.size() <<  " images ran " << stitchingMs << "ms" << DEFAULT << std::endl;

			e.Start();

			BSB b;
			bool bsbResult = b.fromPNG("tiles/map.png", "maps/map_" + conf.name + "_" + patches::to_string(j) + ".kap", tiles.topLeftEdge, tiles.bottomRightEdge);
			if(bsbResult == true) {
				std::cout << GREEN << "BSB conversion ... OK" << DEFAULT << std::endl;
			}

			double bsbMs = e.End();
			std::cout << GREY << "Converting to .kap file took " << bsbMs << "ms" << DEFAULT << std::endl;

			j++;
		}
	}

	double totalMs = total.End();
	std::cout << GREY << "Total runtime of tiles2bsb " << totalMs << "ms" << DEFAULT << std::endl;
	

	return 0;
}
