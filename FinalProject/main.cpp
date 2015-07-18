/*
 * main.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: colman
 */

#include "Map.h"
#include "PathPlanner.h"
#include <iostream>

int mainT()
{
	PathPlanner pp;
	char* ParametersFilePath = "parameters.txt";
	Map *map = new Map(ParametersFilePath);
	int Width,
		Height,
		StartX = 305,
		StartY = 365,
		GoalX = 138,
		GoalY = 169;
	int** ppnGrid = map->getGrid(&Width, &Height);
	pp.pathPlannerInit(ppnGrid, Width, Height, 1);
	map->imagePointToGridPoint(&StartX, &StartY);
	map->imagePointToGridPoint(&GoalX, &GoalY);
	list<int> result  = pp.AStar(StartX, StartY, GoalX, GoalY);

	if (result.empty())
	{
		std::cout << " No path. Marked start and goal on map.";
		result.push_back(StartX * Width + StartY);
		result.push_back(GoalX * Width + GoalY);
	}

	map->Set_A_StarGridPointsOnMap(pp.createWayPoints(result), "Path.png");

	delete map;

	return 0;
}
