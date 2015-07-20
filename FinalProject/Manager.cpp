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

	_plan = plan;
}

void Manager::run()
{
	_robot->Read();

	int GridWidth, GridHeight;
	int StartX = _config->getStartX(),
		StartY = _config->getStartY(),
		GoalX = _config->getGoalX(),
		GoalY = _config->getGoalY();
	//cout << StartX << " " << StartY << " " << GoalX << " " << GoalY << " ";

	PathPlanner Planner;
	int** ppnGrid = _map->getGrid(&GridWidth, &GridHeight);
	Planner.pathPlannerInit(ppnGrid, GridWidth, GridHeight, 1);
	_map->imagePointToGridPoint(&StartX, &StartY);
	_map->imagePointToGridPoint(&GoalX, &GoalY);
	cout << StartX << " " << StartY << " " << GoalX << " " << GoalY << " ";
	list<int> result  = Planner.AStar(StartY, StartX, GoalY, GoalX);

	if (result.empty())
	{
		std::cout << " No path. Marked start and goal on map.";
		result.push_back(StartX * GridWidth + StartY);
		result.push_back(GoalX * GridWidth + GoalY);
	}

	_map->Set_A_StarGridPointsOnMap(Planner.createWayPoints(result), "A_STAR.png");

	list<int> WayPoints = Planner.createWayPoints(result);

	list<int>::iterator iter = WayPoints.end();
	--iter;

	// Run on all over the A* Points and color them on the real Map
	for (DWORD GridCurrentWidth,GridCurrentHeight, i = 0; i < WayPoints.size(); --iter, i++)
	{
		//std::cout << "X:" << _robot->getX() << ", Y:" << _robot->getY() << ", Yaw:" << _robot->getYaw() << std::endl;
		// Calculate the point (x,y)
		GridCurrentWidth = (*iter % GridWidth)* _map->getGridRatio();
		GridCurrentHeight = (*iter / GridWidth)* _map->getGridRatio();
		//std::cout << "WayPointX " << GridCurrentWidth << " WayPointY " << GridCurrentHeight << std::endl;

		_robot->SetNextWayPoint(GridCurrentWidth, GridCurrentHeight);

		_curr = _plan->GetStartPoint();

		if (!(_curr->StartCond()))
		{
			cout << "Problem with start condition";
			return;
		}

		while (_curr != NULL)
		{
			//cout << "thats why";
			while (!(_curr->StopCond()))
			{
				cout << "Robot (x,y,yaw) : " << "(" << _robot->getX() << "," << _robot->getY() << "," << _robot->getYaw() << ") ";
				_curr->Action();
				_robot->Read();
			}

			//cout << "Stop Condition" << endl;

			_curr = _curr->SelectNext();
			_robot->Read();

		}

	}

	cout << "END" <<endl;
}

Manager::~Manager()
{
}

