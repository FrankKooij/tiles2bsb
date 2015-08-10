// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// BSB.HPP
// Converts a tif image to bsb output format
//
// Author: Thomas Brüggemann
// ---------------------------------------------------------------------------

#ifndef BSB_HPP
#define BSB_HPP

#include <iostream>
#include <string>
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */

#include "tiles.hpp"
#include "patches.hpp"

class BSB
{
private:

public:
	inline bool fromPNG(std::string tiffPath, std::string capFileName, Coordinate topLeft, Coordinate bottomRight);
};


// FROM TIF
inline bool BSB::fromPNG(std::string tiffPath, std::string capFileName, Coordinate topLeft, Coordinate bottomRight)
{
	std::string cmd = "lib/imgkap " + tiffPath + " " + patches::to_string(topLeft.second) + " " + 
					  patches::to_string(topLeft.first) + " " + patches::to_string(bottomRight.second) + " " + 
					  patches::to_string(bottomRight.first) + " " +  capFileName;

	std::cout << cmd << std::endl;

	system(cmd.c_str());
	return true;
};

#endif