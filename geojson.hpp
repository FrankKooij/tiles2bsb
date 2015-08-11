// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// GEOJSON.HPP
// Parses geojson string and outputs a polygon
//
// Author: Thomas Brüggemann
// ---------------------------------------------------------------------------

#ifndef GEOJSON_HPP
#define GEOJSON_HPP

#include <string>
#include <vector>
#include <fstream>
#include "polygon.hpp"
#include "coordinate.hpp"
#include "json.hpp"

using json = nlohmann::json;

class Geojson
{
private:
	inline std::vector<Polygon> parseInternal(json j);

public:
	inline std::vector<Polygon> parseString(std::string jsonString);
	inline std::vector<Polygon> parseFile(std::string path);
};

// PARSE STRING
inline std::vector<Polygon> Geojson::parseString(std::string jsonString)
{
	auto j = json::parse(jsonString);
	return this->parseInternal(j);
};

// PARSE FILE
inline std::vector<Polygon> Geojson::parseFile(std::string path)
{
	std::ifstream ifs(path);
	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

	return this->parseString(content);
}

// PARSE INTERNAL
inline std::vector<Polygon> Geojson::parseInternal(json j)
{
	std::vector<Polygon> results;

	// feature collection
	if (j["type"] == "FeatureCollection") 
	{
		
		// loop all features
		for(auto f : j["features"])
		{
			// parse a recursive branch of this feature
			std::vector<Polygon> tmp = this->parseInternal(f);

			// add results of features recursive branch to results
			results.insert(results.end(), tmp.begin(), tmp.end());
		}
	}

	// feature
	else if(j["type"] == "Feature") 
	{	
		// we are only interested in polygons
		if(j["geometry"]["type"] == "Polygon")
		{
			// loop coordinates and create polygon elements from it
			std::vector<Coordinate> coordinates;

			for(auto coord : j["geometry"]["coordinates"][0])
			{
				Coordinate c(coord[0], coord[1]);
				coordinates.push_back(c);
			}

			Polygon p(coordinates);
			results.push_back(p);
		}
	}

	return results;
};

#endif