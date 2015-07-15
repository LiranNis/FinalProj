/*
 * Map.cpp
 *
 *  Created on: Jun 15, 2015
 *      Author: colman
 */

#include "Map.h"

Map::Map(char* ParametersFilePath)
{
	// TODO: Replace atof

	string CurrentLine;
	ifstream ParametersFile;
	ParametersFile.open(ParametersFilePath);

	// If the file didnt open, print error and exit.
	if (!ParametersFile.is_open())
	{
		cout << "Can not open the file, Please locate the file in the project folder and name it parameters.txt" << endl;
		exit(1);
	}

	// While there is parameters in the parameters file.
	while (!ParametersFile.eof())
	{
		// Get a line from the file.
		getline(ParametersFile, CurrentLine);

		// Find the location of the colon.
		size_t ColonPosition = CurrentLine.find(":");

		// Get the string before the colon.
		string CurrentParameter = CurrentLine.substr (0, ColonPosition);

		// If the current parameter is the map path.
		if (!CurrentParameter.compare("map"))
		{
			// Get the map path, skip the space.
			MapPath = CurrentLine.substr (ColonPosition + 1);
		}

		// If the current parameter is the start location.
		if (!CurrentParameter.compare("startLocation"))
		{
			// Find the first space.
			size_t FirstSpacePos = CurrentLine.find(" ", ColonPosition);

			// Find the second space.
			size_t SecondSpacePos = CurrentLine.find(" ", FirstSpacePos + 1);

			// Find the third space.
			size_t ThirdSpacePos = CurrentLine.find(" ", SecondSpacePos + 1);

			// Get the start X (between the first two spaces).
			StartX = atof(CurrentLine.substr(FirstSpacePos, SecondSpacePos).c_str());

			// Get the start Y (between the second and third space).
			StartY = atof(CurrentLine.substr(SecondSpacePos, ThirdSpacePos).c_str());

			// Get the start Yaw (between the first space and the end of the line).
			StartYaw = atof(CurrentLine.substr(ThirdSpacePos).c_str());

		}

		// If the current parameter is the goal.
		if (!CurrentParameter.compare("goal"))
		{
			// Find the first space.
			size_t FirstSpacePos = CurrentLine.find(" ", ColonPosition);

			// Find the second space.
			size_t SecondSpacePos = CurrentLine.find(" ", FirstSpacePos + 1);

			// Get the goal X (between the first two spaces).
			GoalX = atof(CurrentLine.substr(FirstSpacePos, SecondSpacePos).c_str());

			// Get the goal Y (between the second and third space).
			GoalY = atof(CurrentLine.substr(SecondSpacePos).c_str());
		}

		// If the current parameter is the robot size.
		if (!CurrentParameter.compare("robotSize"))
		{
			// Find the first space.
			size_t FirstSpacePos = CurrentLine.find(" ", ColonPosition);

			// Find the second space.
			size_t SecondSpacePos = CurrentLine.find(" ", FirstSpacePos + 1);

			// Get the robot width (between the first two spaces).
			RobotWidth = atof(CurrentLine.substr(FirstSpacePos, SecondSpacePos).c_str());

			// Get the robot height (between the second and third space).
			RobotHeight = atof(CurrentLine.substr(SecondSpacePos).c_str());
		}

		// If the current parameter is the map resolution.
		if (!CurrentParameter.compare("MapResolutionCM"))
		{
			// Find the first space.
			size_t FirstSpacePos = CurrentLine.find(" ", ColonPosition);

			// Get the map resolution CM (between the first two spaces).
			CMInPixel = atof(CurrentLine.substr(FirstSpacePos).c_str());
		}

		// If the current parameter is the grid resolution.
		if (!CurrentParameter.compare("GridResolutionCM"))
		{
			// Find the first space.
			size_t FirstSpacePos = CurrentLine.find(" ", ColonPosition);

			// Get the grid size (between the first two spaces).
			GridSize = atof(CurrentLine.substr(FirstSpacePos).c_str());
		}

	}

	ParametersFile.close();

	// Replace tilde with user home folder.
	size_t TildePosition = MapPath.find("~");
	if (TildePosition != string::npos)
	{
		char* HomePath = getenv("HOME");
		MapPath.replace(0 , sizeof(HomePath) - 2, HomePath);
	}

	size_t NewRowPosition;

	// Delete carriage return (new lines).
	if (!MapPath.empty() && ((NewRowPosition = MapPath.find("\r")) != string::npos))
	{
		MapPath.erase(NewRowPosition);
	}

	InitInflatedGrid();
}

vector<unsigned char> Map::GetInflatedMap()
{
	unsigned int InflateNumber = RobotWidth / 2;
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

void Map::InitInflatedGrid()
{
	std::vector<unsigned char> image; //the raw pixels
	unsigned int width, height, x, y, InflateNumber = (RobotWidth / CMInPixel) / 2 + 1;

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

	int GridRatio =  this->_GridRatio = GridSize / CMInPixel;
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


void Map::Set_A_StarGridPointsOnMap(list<int> A_StarPathPointsOnGrid) // Bonus
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
	encodeOneStep("A_star_Map.png", navImage, this->_mapWidth, this->_mapHeight);
}


Map::~Map()
{
}

