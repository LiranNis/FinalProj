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
	int SleepTime = 100;
	double Speed = 0.4;
	_robot->SetSpeed(0, Speed);
	usleep(SleepTime * 1000);
	_robot->setYaw(_robot->getYaw() + Speed * ((double)SleepTime / 1000.00));
	std::cout<<"Action:Turn"<<std::endl;
}

TurnToDest::~TurnToDest()
{
}

