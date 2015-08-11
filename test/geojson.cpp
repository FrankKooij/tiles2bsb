
#include "../geojson.hpp"
#include <fstream>
#include <string>
#include <iostream>

TEST_CASE("Read and parse GeoJSON data", "[parseString]")
{
	std::ifstream ifs("test/test.geojson");
	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

	REQUIRE( content.size() > 0 );

	Geojson g;
	std::vector<Polygon> polygons = g.parseString(content);

	REQUIRE( polygons.size() > 0 );
}

TEST_CASE("Read and parse GeoJSON file", "[parseFile]")
{
	Geojson g;
	std::vector<Polygon> polygons = g.parseFile("test/test.geojson");

	REQUIRE( polygons.size() > 0 );
}