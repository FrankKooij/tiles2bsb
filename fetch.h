// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// FETCH.H
// Fetch class is used to download a range of tiles from a tileserver
//
// Author: Thomas Brüggemann
// ---------------------------------------------------------------------------

#ifndef FETCH_H
#define FETCH_H

#include <iostream>
#include <string>

class Fetch
{
private:
	inline bool replace(std::string& str, const std::string& from, const std::string& to);

public:
	inline bool fromUrl(std::string url, int zoom, int x, int y);
};

// REPLACE
// replaces the first occurancy of a string with another string
inline bool Fetch::replace(std::string& str, const std::string& from, const std::string& to) 
{
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos) 
    {
        return false;
    }

    str.replace(start_pos, from.length(), to);
    return true;
};

// FROM URL
// url would be something like 'http://a.tile.osm.org/{z}/{x}/{y}.png'
inline bool Fetch::fromUrl(std::string url, int zoom, int x, int y)
{
	// replace the zoom, x and y parameters to the url
	this->replace(url, "{z}", std::to_string(zoom));
	this->replace(url, "{x}", std::to_string(x));
	this->replace(url, "{y}", std::to_string(y));

	std::cout << url << std::endl;
	return true;
};

#endif