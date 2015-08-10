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

	Coordinate a(3.849678039550781, 51.742549461489034);
	Coordinate b(3.8905334472656246, 51.76996448812039);
	Coordinate c(3.9464950561523433, 51.760190496399375);
	Coordinate d(3.93310546875, 51.717032167390364);
	Coordinate e(3.8544845581054683, 51.72171141639037);

	points.push_back(a);
	points.push_back(b);
	points.push_back(c);
	points.push_back(d);
	points.push_back(e);

	Polygon polygon(points);
	
	std::vector<BoundingBox> boxes = polygon.getCoveringRectangles();

	for(BoundingBox box : boxes)
	{
		std::cout << box.toString() << std::endl;
	}

	REQUIRE( boxes.size() == 4 );
}