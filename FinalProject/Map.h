/*
 * Map.h
 *
 *  Created on: Jun 15, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_
#include <list>

#include "WriteToPng/pngUtil.h"
#include "WriteToPng/lodepng.h"

#define DWORD unsigned int


class Map
{
	string MapPath;
	int** Grid;
	int gridHeight,
		gridWidth,
		_GridRatio;
	DWORD _mapWidth,
			_mapHeight;

	DWORD const _MyMapColor = 0x0666CEA1;

public:
	vector<unsigned char> _navImage; // vector of inflated map -> will be drowen and be saved
	Map(string mapPath, unsigned int InflateNumber, int GridRatio);
	vector<unsigned char> GetInflatedMap(unsigned int InflateNumber);
	vector<unsigned char> ImageToGrid(vector<unsigned char> Image);
	void InitInflatedGrid(unsigned int InflateNumber, int GridRatio);
	int** getGrid(int* gridWidthOut, int* gridHeightOut);
	void Set_A_StarGridPointsOnMap(list<int> A_StarPathPointsOnGrid, char* filename);
	void imagePointToGridPoint(int* pointX, int* pointY);
	virtual ~Map();

	int getGridRatio() const {
		return _GridRatio;
	}
};

#endif /* MAP_H_ */
