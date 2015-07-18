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
	_curr = plan->GetStartPoint();
}

void Manager::run()
{
	_robot->Read();

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

Manager::~Manager()
{
}

