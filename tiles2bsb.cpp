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

int main()
{
	std::cout << "=== TILES-2-BSB v1.0 ===" << std::endl;

	double lat = 51.272376;
	double lon = 6.271966;

	Tiles t;
	std::pair<int, int> xy = t.fromCoordinate(10, lon, lat);

	std::cout << "(" << xy.first << ", " << xy.second << ")" << std::endl;

  	return 0;
}
