/*
 * TurnToDest.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "TurnToDest.h"

TurnToDest::TurnToDest(Robot* robot):Behavior(robot)
{
}

bool TurnToDest::StartCond()
{
	if(!_robot->IsDirectedToWayPoint())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool TurnToDest::StopCond()
{
	if(_robot->IsDirectedToWayPoint())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void TurnToDest::Action()
{
	_robot->SetSpeed(0, 0.2);
}

TurnToDest::~TurnToDest()
{
}

