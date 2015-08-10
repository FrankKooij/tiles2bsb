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

#include <stdio.h>
#include <stdlib.h>		/* for malloc() */
#include <string.h>		/* for strncmp() */

#include <tiffio.h>		/* libtiff - TIFF file I/O */
#include <bsb.h>

static int depth_for_colors[] = { 1, 2, 4, 8, 16, 32, 64, 128 };

class BSB
{
private:
	inline int read8BPPTiffLine(TIFF* tif, uint16_t bits_per_sample, int width, uint8_t *tiff_row, uint32_t row);
	inline int countTiffColors(TIFF* tif, BSBImage *pImage, uint16_t bits_per_sample);

public:
	inline bool fromTiff(std::string tiffPath, std::string templatePath, std::string capFileName);
};

// READ 8 BPP TIFF LINE
inline int BSB::read8BPPTiffLine(TIFF* tif, uint16_t bits_per_sample, int width, uint8_t *tiff_row, uint32_t row)
{
	int i, result;

	result = TIFFReadScanline(tif, tiff_row, row, 0);

	/* Copy the TIFF row expanding to 8 bits per pixel if necessary */
	switch (bits_per_sample)
	{
        case 8:		/* no modification needed */
        {
			break;
		}
        case 4:
		{
			/* Expand 4 bits-per-sample into 8 bits-per-sample		*/

			unsigned char	*p = tiff_row;
			uint8_t			a, b;

			if ((width % 2) != 0)			// Handle boundary condition
			{
				i = (width - 1) / 2;
				a = (p[i] >> 4) & 0xf;		// left nibble
				p[ width - 1 ] = a;
			}

			/* Start at the end of the compressed row and expand each pair */
			for (i = (width - 2) / 2; i >= 0; i--)
			{
				a = (p[i] >> 4) & 0xf;		// left nibble
				b = p[i] & 0xf;				// right nibble
				p[i*2] = a;
				p[i*2+1] = b;
			}
			break;
		}
	}
	return result;
};

// COUNT TIFF COLORS
// Count unique colors in the TIFF color map.
inline int BSB::countTiffColors(TIFF* tif, BSBImage *pImage, uint16_t bits_per_sample)
{
	int			i, j, max_colors = 0;
	uint64_t	histogram[256] = {0};
	uint8_t		*tiff_row;

	tiff_row = (uint8_t *)malloc(pImage->width);

	/* Scan through entire image computing a histogram of colormap indices	*/
	for (j = 0; j < pImage->height; j++)
	{
		uint8_t *p = tiff_row;

		this->read8BPPTiffLine(tif, bits_per_sample, pImage->width, tiff_row, j);

		for (i = 0; i < pImage->width; i++)
			histogram[*p++]++;
	}
	/* Count down from highest colormap index for the first non-zero value.	*/
	/* This will indicate the maximum number of colors.						*/
	for (i = 255; i >= 0; i--)
	{
		if (histogram[i] != 0)
		{
			max_colors = i + 1;		/* count of colors includes index 0 */
			break;
		}
	}
	free(tiff_row);

	return max_colors;
};

// FROM TIF
inline bool BSB::fromTiff(std::string tiffPath, std::string templatePath, std::string capFileName)
{
	BSBImage	image;
	int			i, j, arg_idx, depth = 0, num_colors = -1, *index;
	FILE		*tmpl_file, *out;
	TIFF*		tif;
	uint16_t	*red, *green, *blue;
	uint16_t	bits_per_sample, photometric, planar_config;
	uint8_t		*tiff_row, *scratch;
	char		line[1024];

	// open tiff iamge
	tif = TIFFOpen(tiffPath.c_str(), "rb");
	if (! tif)
	{
		fprintf(stderr, "Could not TIFFOpen \"%s\"\n", tiffPath.c_str());
		return false;
	}

	TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &image.width);
	TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &image.height);
	TIFFGetFieldDefaulted(tif, TIFFTAG_BITSPERSAMPLE, &bits_per_sample);
	TIFFGetFieldDefaulted(tif, TIFFTAG_PHOTOMETRIC, &photometric);
	TIFFGetFieldDefaulted(tif, TIFFTAG_PLANARCONFIG, &planar_config);

	/* Check for supported TIFF files */
	if (image.width == 0 || image.height == 0)
	{
		fprintf(stderr, "Invalid TIFF file (width=%d,height=%d)\n", image.width, image.height);
		exit(1);
	}
	if (photometric != PHOTOMETRIC_PALETTE)
	{
		fprintf(stderr, "No support for TIFF files with PHOTOMETRIC=%d (only images containing color maps supported)\n", photometric);
		exit(1);
	}
	if (bits_per_sample != 8 && bits_per_sample != 4)
	{
		fprintf(stderr, "No support for TIFF files with BITSPERSAMPLE=%d (only 4 or 8 bits per sample supported)\n", bits_per_sample);
		exit(1);
	}
	if (planar_config != PLANARCONFIG_CONTIG)
	{
		fprintf(stderr, "No support for TIFF files with PLANARCONFIG=%d (only single plane images supported)\n", planar_config);
		exit(1);
	}

	// TIFFGetField allocates memory for color fields - TIFFClose frees it.
	TIFFGetField(tif, TIFFTAG_COLORMAP, &red, &green, &blue);

	tiff_row = (uint8_t *)malloc(image.width);
	if (! tiff_row)
	{
		fprintf(stderr,"Cannot allocate %d bytes for image row\n", image.width);
		return false;
	}

	if (num_colors == -1)
	{
		num_colors = this->countTiffColors(tif, &image, bits_per_sample);
	}

	if (num_colors <= 0)
	{
		fprintf(stderr, "Error - no colors found in image\n");
		return false;
	}

	// the BSB format cannot cope with more than 128 colors 
	if (num_colors > 128)
	{
		fprintf(stderr, "Too many colors for BSB format (%d > 128 max.)\n", num_colors);
		fprintf(stderr, "Try reducing the colors.\n\tE.g. Using ImageMagick\n\tconvert -colors 128 ...\n\n");
		fprintf(stderr, "Or use -c max-colors to restrict the colormap to max-colors\n");
		return false;
	}

	// given num_colors in input image, compute required "depth"
	// e.g. num_colors=35, depth=6  (2^6 = 64)
	for (i = 0; i < (int)sizeof(depth_for_colors); i++)
	{
		if (num_colors < depth_for_colors[i])
			break;

		depth = i + 1;
	}
	image.depth = depth;

	// open cap file to write to
	out = fopen(capFileName.c_str(), "wb");
	if (!out)
	{
		perror(capFileName.c_str());
		return false;
	}

	// copy in all text lines from template excluding RGB and IFM tags
	tmpl_file = fopen(templatePath.c_str(), "rb");
	while (fgets(line, sizeof(line), tmpl_file) != NULL)
	{
		if (strncmp("RGB/", line, 4) == 0)
			continue;
		if (strncmp("IFM/", line, 4) == 0)
			continue;
		if (line[0] == 0x1a)
			break;
		fputs(line, out);
	}
	fclose(tmpl_file);

	// write IFM tag
	fprintf(out, "IFM/%d\r\n", depth);

	// write RGB tags for colormap
	for (i = 0; i < num_colors; i++)
	{
		fprintf(out, "RGB/%d,%d,%d,%d\r\n",
					i+1,
					red[i] >> 8,
					green[i] >> 8,
					blue[i] >> 8
					);
	}
	fputc(0x1a, out);
	fputc('\0', out);
	fputc(depth, out);

	index = (int *)malloc((image.height + 1) * sizeof(int));
	scratch = (uint8_t *)malloc(image.width + 8);	// max space encoded line can take

	// read rows from tif, write to bsb
	for (j = 0; j < image.height; j++)
	{
		int	len;

		// record start-of-row file position for index table
		index[j] = ftell(out);

		this->read8BPPTiffLine(tif, bits_per_sample, image.width, tiff_row, j);

		// compress raster and write to BSB file 
		len = bsb_compress_row(&image, j, tiff_row, scratch);
		fwrite(scratch, len, 1, out);
	}

	free(scratch);
	free(tiff_row);
	TIFFClose(tif);

	// record start-of-index-table file position in the index table
	index[image.height] = ftell(out);

	bsb_write_index(out, image.height, index);
	free(index);

	fclose(out);

	return true;
};

#endif