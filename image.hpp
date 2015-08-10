// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// IMAGE.HPP
// Image class is able to stitch multiple images together to one giant image
//
// Author: Thomas Brüggemann
// ---------------------------------------------------------------------------

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>
#include <string>
#include <Magick++.h>

#include "patches.hpp"
#include "tiles.hpp"

class Image
{
private:

public:
	Image();
	inline bool stitchTogether(TilesResult tiles, int zoom, std::string fileName);
};

// CONSTRUCTOR
Image::Image()
{
	Magick::InitializeMagick("");
}

// STITCH TOGETHER
inline bool Image::stitchTogether(TilesResult tiles, int zoom, std::string fileName)
{	
	std::vector<Magick::Image> sourceImageList;
    Magick::Image image;

    // loop all coordinates
    for(XY xy : tiles.coordinates)
    {
    	std::string imageName = "tiles/" + patches::to_string(zoom) + "_" + patches::to_string(xy.first) + 
    							"_" + patches::to_string(xy.second) + ".png";

    	image.read(imageName);
    	sourceImageList.push_back(image);
    }

    Magick::Geometry tileGeometry(tiles.width, tiles.height); 

    // background color for the montage
	Magick::Color color("rgba(0,0,0,0)");

	// prepare settings for the montage
	Magick::Montage montageSettings;
	montageSettings.geometry("256x256-0-0");
	montageSettings.shadow(false);
	montageSettings.backgroundColor(color);
	montageSettings.tile(tileGeometry);

	std::vector<Magick::Image> montagelist;
    Magick::montageImages( &montagelist, sourceImageList.begin(), sourceImageList.end(), montageSettings);

    // reduce amount of colors for every image
    for(Magick::Image &image : montagelist) 
    {
        image.type(Magick::PaletteType);
        image.quantizeColors(128); 
        image.quantize();
    }

    // This will give the expected result
   	Magick::writeImages(montagelist.begin(), montagelist.end(), fileName);

	return true;
}

#endif