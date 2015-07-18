/*
 * Manager.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "Manager.h"

Manager::Manager(Robot* robot, Plan* plan)
{
	_robot = robot;

	char* ParametersFilePath = "parameters.txt";
	_config = new ConfigurationManager(ParametersFilePath);
	_robot->SetLocation(_config->getStartX(), _config->getStartY(), _config->getStartYaw());
	_map = new Map(_config->getMapPath(),
			           ((_config->getRobotWidth() / _config->getCmInPixel()) / 2) + 1,
			           _config->getGridSize() / _config->getCmInPixel());

	_curr = plan->GetStartPoint();
}

void Manager::run()
{
	_robot->Read();

	int GridWidth, GridHeight;
	int StartX = _config->getStartX(),
		StartY = _config->getStartY(),
		GoalX = _config->getGoalX(),
		GoalY = _config->getGoalY();

	PathPlanner Planner;

	int** ppnGrid = _map->getGrid(&GridWidth, &GridHeight);

	Planner.pathPlannerInit(ppnGrid, GridWidth, GridHeight, 1);
	_map->imagePointToGridPoint(&StartX, &StartY);
	_map->imagePointToGridPoint(&GoalX, &GoalY);
	list<int> result  = Planner.AStar(StartX, StartY, GoalX, GoalY);


	if (result.empty())
	{
		std::cout << " No path. Marked start and goal on map.";
		result.push_back(StartX * GridWidth + StartY);
		result.push_back(GoalX * GridWidth + GoalY);
	}

	_map->Set_A_StarGridPointsOnMap(Planner.createWayPoints(result));

	list<int> WayPoints = Planner.createWayPoints(result);
	list<int>::iterator iter = WayPoints.begin();

	// Run on all over the A* Points and color them on the real Map
	for (DWORD GridCurrentWidth,GridCurrentHeight; iter != WayPoints.end(); ++iter)
	{
		// Calculate the point (x,y)
		GridCurrentWidth = (*iter % GridWidth)* _map->getGridRatio(); // x (<--->)
		GridCurrentHeight = (*iter / GridWidth)* _map->getGridRatio(); // y (/\ , \/)

		_robot->SetNextWayPoint(GridCurrentWidth, GridCurrentHeight);

		if (!(_curr->StartCond()))
		{
			return;
		}

		while (_curr != NULL)
		{
			while (!(_curr->StopCond()))
			{
				_curr->Action();
				_robot->Read();
			}

			_curr = _curr->SelectNext();
			_robot->Read();
		}

	}
}

Manager::~Manager()
{
}

