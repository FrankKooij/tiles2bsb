#include <iostream>
#include <utility>

#include "tiles.h"

int main()
{
	std::cout << "=== TILES2BSB v1.0 ===" << std::endl;

	double lat = 51.272376;
	double lon = 6.271966;

	Tiles t;
	std::pair<int, int> xy = t.fromCoordinate(10, lon, lat);

	std::cout << "(" << xy.first << ", " << xy.second << ")" << std::endl;

  	return 0;
}
