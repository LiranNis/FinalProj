/*
 * MoveForward.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "MoveForward.h"

MoveForward::MoveForward(Robot* robot):Behavior(robot)
{
}

bool MoveForward::StartCond()
{
	if (_robot->IsDirectedToWayPoint())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MoveForward::StopCond()
{
	if (!_robot->IsDirectedToWayPoint())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MoveForward::Action()
{
	_robot->SetSpeed(0.2, 0);
}

MoveForward::~MoveForward() {
	// TODO Auto-generated destructor stub
}

