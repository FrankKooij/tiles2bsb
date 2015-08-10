
#include "../geojson.hpp"
#include <fstream>
#include <string>
#include <iostream>

TEST_CASE("Read and parse GeoJSON data", "[parse]")
{
	std::ifstream ifs("test/test.geojson");
	std::string content((std::istreambuf_iterator<char>(ifs)),
                       (std::istreambuf_iterator<char>()));

	REQUIRE( content.size() > 0 );

	Geojson g;
	std::vector<Polygon> polygons = g.parse(content);

	REQUIRE( polygons.size() > 0 );

	std::cout << polygons.size() << std::endl;
}