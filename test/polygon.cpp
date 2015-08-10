#include "../polygon.hpp"
#include "../coordinate.hpp"
#include <vector>

TEST_CASE("Construct a polygon and find the centriod", "[getControid]")
{
	std::vector<Coordinate> points;

	Coordinate a(0.0, 0.0);
	Coordinate b(0.0, 3.0);
	Coordinate c(3.0, 3.0);
	Coordinate d(3.0, 0.0);

	points.push_back(a);
	points.push_back(b);
	points.push_back(c);
	points.push_back(d);

	Polygon polygon(points);

	Coordinate center = polygon.getCentroid();

	REQUIRE( center.latitude == 1.5 );
	REQUIRE( center.longitude == 1.5);
}

TEST_CASE("Find covering rectangles of polygon", "[getCoveringRectangles]")
{
	std::vector<Coordinate> points;

	Coordinate a(0.0, 0.0);
	Coordinate b(0.0, 3.0);
	Coordinate c(3.0, 3.0);
	Coordinate d(3.0, 0.0);

	points.push_back(a);
	points.push_back(b);
	points.push_back(c);
	points.push_back(d);

	Polygon polygon(points);
	
	polygon->getCoveringRectangles();
}