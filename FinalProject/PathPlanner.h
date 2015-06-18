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
	Graph _graph;
	void gridToGraph(int** Grid);

public:
	void pathPlannerInit(int** Grid);
	vector<int> AStar(int StartX, int StartY, int GoalX, int GoalY);
};

#endif
