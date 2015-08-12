// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// CONFIG.HPP
// Reads a config json file and parsed it into configuration class
//
// Author: Thomas Brüggemann
// ---------------------------------------------------------------------------

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

class Config
{
private:
public:
	std::string geojsonPath;
	std::string tileServerUrl;
	int zoom;
	std::string name;

	Config(std::string path);
	inline void parseFile(std::string path);
};

// CONSTRUCTOR
Config::Config(std::string path)
{
	this->parseFile(path);
};

// PARSE FILE
inline void Config::parseFile(std::string path)
{
	std::ifstream ifs(path);
	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

	auto j = json::parse(content);

	// name
	if (j.find("name") != j.end()) 
	{
		this->name = j["name"].get<std::string>();
	}

	// geojsonPath
	if (j.find("geojsonPath") != j.end()) 
	{
		this->geojsonPath = j["geojsonPath"].get<std::string>();
	}

	// tileServerUrl
	if (j.find("tileServerUrl") != j.end()) 
	{
		this->tileServerUrl = j["tileServerUrl"].get<std::string>();
	}

	// zoom
	if (j.find("zoom") != j.end()) 
	{
		this->zoom = j["zoom"].get<int>();
	}
}

#endif