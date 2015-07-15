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

#include "WriteToPng/pngUtil.h"
#include "WriteToPng/lodepng.h"

class Map
{
	string MapPath;
	double StartX, StartY, StartYaw;
	double GoalX, GoalY;
	double RobotWidth, RobotHeight;
	double CMInPixel = 2.5; // Pixels in CM
	double GridSize = 10; // Grid CM
	int** Grid;

public:
	Map(char* ParametersFilePath);
	vector<unsigned char> GetInflatedMap();
	vector<unsigned char> ImageToGrid(vector<unsigned char> Image);
	void InitInflatedGrid();
	int** getGrid();
	virtual ~Map();
};

#endif /* MAP_H_ */
