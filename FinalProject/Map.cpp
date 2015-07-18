/*
 * Map.cpp
 *
 *  Created on: Jun 15, 2015
 *      Author: colman
 */

#include "Map.h"

Map::Map(string mapPath, unsigned int InflateNumber, int GridRatio)
{
	MapPath = mapPath;
	InitInflatedGrid(InflateNumber, GridRatio);
}

vector<unsigned char> Map::GetInflatedMap(unsigned int InflateNumber)
{
	std::vector<unsigned char> image; //the raw pixels
	unsigned int width, height, x, y;

	//decode
	unsigned int error = lodepng::decode(image, width, height, MapPath);

	//if there's an error, display it
	if (error)
	{
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << " file path: " << MapPath << std::endl;
	}

	vector<unsigned char> navImage; //the raw pixels
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
				for (unsigned int nX = 0; nX < InflateNumber; nX++)
				{
					for (unsigned int nY = 0; nY < InflateNumber; nY++)
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

	encodeOneStep("InflatedMap.png", navImage, width, height);

	return (navImage);
}

void Map::InitInflatedGrid(unsigned int InflateNumber, int GridRatio)
{
	std::vector<unsigned char> image; //the raw pixels
	unsigned int width, height, x, y;

	//decode
	unsigned int error = lodepng::decode(image, width, height, MapPath);

	//if there's an error, display it
	if (error)
	{
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << " file path: " << MapPath << std::endl;
	}

	std::vector<unsigned char> navImage; //the raw pixels
	navImage.resize(width * height * 4);
	this-> _mapWidth = width;
	this-> _mapHeight = height;


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

	int GridWidth = width / GridRatio + 1;
	int GridHeight = height / GridRatio + 1;
	cout << GridHeight << ":" << GridWidth << endl;

	// Vector for the grid PNG
	std::vector<unsigned char> GridImage; //the raw pixels
	GridImage.resize(GridWidth * GridHeight * 4);
	this->gridHeight = GridHeight;
	this->gridWidth = GridWidth;

	// Init the grid map
	Grid = (new int*[GridHeight]);

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
	this->_navImage = navImage;
	encodeOneStep("InflatedMap.png", navImage, width, height);
	encodeOneStep("GridMap.png", GridImage, GridWidth, GridHeight);
}

int** Map::getGrid(int* gridWidthOut, int* gridHeightOut)
{
	cout << "Map returns grid width : " << this->gridWidth << " height : " << this->gridHeight << endl;
	*gridHeightOut = this->gridHeight;
	*gridWidthOut = this->gridWidth;
	return this->Grid;
}


void Map::Set_A_StarGridPointsOnMap(list<int> A_StarPathPointsOnGrid, char* filename) // Bonus
{
	list<int>::iterator iter = A_StarPathPointsOnGrid.begin();
	std::vector<unsigned char> navImage; //the raw pixels

	navImage = this->_navImage; // Actually a pointer so if it importent then need to really copy the vector (init and byte by byte copy)

	// Run on all over the A* Points and color them on the real Map
	for (DWORD Grid_P_width,Grid_P_hight; iter != A_StarPathPointsOnGrid.end(); ++iter)
	{
		// Calculate the point (x,y)
		Grid_P_width = (*iter % this->gridWidth)* this->_GridRatio; // x (<--->)
		Grid_P_hight = (*iter / this->gridWidth)* this->_GridRatio; // y (/\ , \/)

		// Color The points
		for (DWORD nXRatio=0; nXRatio < this->_GridRatio/2 ; nXRatio++)
		{
			for (DWORD nYRatio=0; nYRatio < this->_GridRatio/2 ; nYRatio++)
			{
				DWORD nOffsetOnVector = (Grid_P_hight+nYRatio)* this->_mapWidth *4 + (Grid_P_width+nXRatio)*4;// *4 for the RGB.
				*((DWORD*)((void*)&(navImage[nOffsetOnVector]))) = _MyMapColor;
				/*navImage[nOffsetOnVector] = 0xAA;
				navImage[nOffsetOnVector+1] = 0xAA;
				navImage[nOffsetOnVector+2] = 0xAA;
				navImage[nOffsetOnVector+3] = 0xAA;*/
			}
		}
	}

	// Save the Map
	encodeOneStep(filename, navImage, this->_mapWidth, this->_mapHeight);
}

void Map::imagePointToGridPoint(int* pointX, int* pointY)
{
	*pointX = ((*pointX) / this->_GridRatio) + 1;
	*pointY = ((*pointY) / this->_GridRatio) + 1;
}

Map::~Map()
{
	int j;

	for (j = 0; j < this->gridHeight; ++j)
	{
		delete [] (this->Grid[j]);
	}

	delete[](this->Grid);

	std::cout << "Map destroyed" << std::endl;
}

