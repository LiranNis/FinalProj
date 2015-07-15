/*
 * Map.h
 *
 *  Created on: Jun 15, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_
#include <fstream>
#include <stdlib.h>
#include <list>

#include "WriteToPng/pngUtil.h"
#include "WriteToPng/lodepng.h"

#define DWORD unsigned int


class Map
{
	// TODO: CMInPixel, GridSize from file...!!!
	string MapPath;
	double StartX, StartY, StartYaw;
	double GoalX, GoalY;
	double RobotWidth, RobotHeight;
	double CMInPixel = 2.5; // Pixels in CM
	double GridSize = 10; // Grid CM
	int** Grid;
	int gridHeight,
		gridWidth,
		_GridRatio;
	DWORD _mapWidth,
			_mapHeight;

	DWORD const _MyMapColor = 0x0666CEA1;

public:
	vector<unsigned char> _navImage; // vector of inflated map -> will be drowen and be saved
	Map(char* ParametersFilePath);
	vector<unsigned char> GetInflatedMap();
	vector<unsigned char> ImageToGrid(vector<unsigned char> Image);
	void InitInflatedGrid();
	int** getGrid(int* gridWidthOut, int* gridHeightOut);
	void Set_A_StarGridPointsOnMap(list<int> A_StarPathPointsOnGrid);
	virtual ~Map();
};

#endif /* MAP_H_ */
