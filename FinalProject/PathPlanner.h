/*
 * Map.cpp
 *
 *  Created on: Jun 15, 2015
 *      Author: AIL
 */

#ifndef PATH_PLANNER_H_
#define PATH_PLANNER_H_

#include <list>
#include <cstdlib>
#include "Graph.h"

using namespace std;

class PathPlanner
{
private:
	Graph* _graph;
	int heuristicCost(int VStart, int VDest);
	list<int> reconstructPath(int* cameFrom, int currVertex);
	bool isInSet(list<int>* source, int target);

public:
	void pathPlannerInit(int** Grid, uint width, uint height, int obstacleIdentifier);
	list<int> AStar(int StartX, int StartY, int GoalX, int GoalY);

};

#endif
