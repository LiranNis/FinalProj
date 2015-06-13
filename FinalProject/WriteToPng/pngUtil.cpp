/*
 * pngUtil.cpp
 *
 *  Created on: Mar 30, 2015
 *      Author: colman
 */
#include "pngUtil.h"
#include "lodepng.h"

//Encode from raw pixels to disk with a single function call
//The image argument has width * height RGBA pixels or width * height * 4 bytes
void encodeOneStep(const char* filename, std::vector<unsigned char> image,
		unsigned width, unsigned height) {
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if (error)
		std::cout << "encoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;
}

void decodeOneStep(const char* filename) {
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;

	//decode
	unsigned error = lodepng::decode(image, width, height, filename);

	//if there's an error, display it
	if (error)
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;

	//the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}
void ConvertMapBlackToWhiteAndWhiteToBlack(const char* filename) {
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;
	unsigned x, y;
	//decode
	unsigned error = lodepng::decode(image, width, height, filename);

	//if there's an error, display it
	if (error)
	{
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;
		return;
	}

	std::vector<unsigned char> navImage; //the raw pixels
	navImage.resize(width * height * 4);
	unsigned char color;
	for (y = 0; y < height; y++)
		for (x = 0; x < width; x++) {
			if (image[y * width * 4 + x * 4 + 0]
					|| image[y * width * 4 + x * 4 + 1]
					|| image[y * width * 4 + x * 4 + 2])
				color = 0;
			else
				color = 255;
			navImage[y * width * 4 + x * 4 + 0] = color;
			navImage[y * width * 4 + x * 4 + 1] = color;
			navImage[y * width * 4 + x * 4 + 2] = color;
			navImage[y * width * 4 + x * 4 + 3] = 255;
		}

	encodeOneStep("newMap.png", navImage, width, height);
}

void InflateToGridMap(string filename, double InflateNumber, double PixelToCM, double GridSize)
{
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;
	unsigned x, y;

	//decode
	unsigned error = lodepng::decode(image, width, height, filename);

	//if there's an error, display it
	if (error)
	{
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << " file path: " << filename << std::endl;
	}

	std::vector<unsigned char> navImage; //the raw pixels
	navImage.resize(width * height * 4);

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			unsigned Current = (y) * width * 4 + (x) * 4;
			navImage[Current] = 255;
			navImage[Current + 1] = 255;
			navImage[Current + 2] = 255;
			navImage[Current + 3] = 255;
		}
	}

	unsigned char color = 0;
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{

			if (!image[y * width * 4 + x * 4 + 0]
					|| !image[y * width * 4 + x * 4 + 1]
					|| !image[y * width * 4 + x * 4 + 2])
			{
				for (unsigned nX = 0; nX < InflateNumber; nX++)
				{
					for (unsigned nY = 0; nY < InflateNumber; nY++)
					{
						unsigned Current = (y + nY) * width * 4 + (x + nX) * 4;
						if (Current < navImage.size())
						{
							navImage[Current + 0] = color;
							navImage[Current + 1] = color;
							navImage[Current + 2] = color;
							navImage[Current + 3] = 255;
						}

						Current = (y - nY) * width * 4 + (x + nX) * 4;
						if (Current < navImage.size())
						{
							navImage[Current + 0] = color;
							navImage[Current + 1] = color;
							navImage[Current + 2] = color;
							navImage[Current + 3] = 255;
						}

						Current = (y + nY) * width * 4 + (x - nX) * 4;
						if (Current < navImage.size())
						{
							navImage[Current + 0] = color;
							navImage[Current + 1] = color;
							navImage[Current + 2] = color;
							navImage[Current + 3] = 255;
						}

						Current = (y - nY) * width * 4 + (x - nX) * 4;
						if (Current < navImage.size())
						{
							navImage[Current + 0] = color;
							navImage[Current + 1] = color;
							navImage[Current + 2] = color;
							navImage[Current + 3] = 255;
						}
					}
				}
			}
		}
	}

	int GridRatio = GridSize / PixelToCM;
	int GridWidth = width / GridRatio + 1;
	int GridHeight = height / GridRatio + 1;
	cout << GridHeight << ":" << GridWidth << endl;

	// Vector for the grid PNG
	std::vector<unsigned char> GridImage; //the raw pixels
	GridImage.resize(GridWidth * GridHeight * 4);

	// Init the grid map
	int** Grid = (new int*[GridHeight]);

	for(int y = 0; y < GridHeight; y++)
	{
		Grid[y] = new int[GridWidth];
	}

	for (int y = 0; y < GridHeight; y++)
	{
		for (int x = 0; x < GridWidth; x++)
		{
			// Set the PNG vector as white
			unsigned Current = (y) * GridWidth * 4 + (x) * 4;
			GridImage[Current + 0] = 255;
			GridImage[Current + 1] = 255;
			GridImage[Current + 2] = 255;
			GridImage[Current + 3] = 255;

			// Set as free
			Grid[y][x] = FREE;
		}
	}

	//int gridWidth = width / PixelInCM / GridSize;
	//int gridHeight = height / PixelInCM / GridSize;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			unsigned Current = (y) * width * 4 + (x) * 4;

			//cout << "first " << Current << endl;
			if((navImage[Current] == 0 )|| (navImage[Current + 1] == 0) || (navImage[Current + 2] == 0))
			{
				Grid[y / GridRatio][x / GridRatio] = BLOCKED;

				// Color the PNG vector
				unsigned GridCurrent = (y / GridRatio * GridWidth) * 4 + (x / GridRatio) * 4;
				GridImage[GridCurrent + 0] = 0;
				GridImage[GridCurrent + 1] = 0;
				GridImage[GridCurrent + 2] = 0;
				GridImage[GridCurrent + 3] = 255;
			}
		}
	}

	encodeOneStep("InflatedMap.png", navImage, width, height);
	encodeOneStep("GridMap.png", GridImage, GridWidth, GridHeight);

}
