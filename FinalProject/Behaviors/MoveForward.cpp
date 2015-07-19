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
	if (!_robot->ArrivedToWayPoint())
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
	if (_robot->ArrivedToWayPoint())
	{
		std::cout << "stop";
		return true;
	}
	else
	{
		return false;
	}
}

void MoveForward::Action()
{
	float SleepTime = 12.4;
	double Speed = 0.1;
	_robot->SetSpeed(Speed, 0);
	usleep(SleepTime * 1000);
	_robot->setX(_robot->getX() + Speed * 100 * ((double)SleepTime / 1000) * cos(_robot->getYaw()));
	_robot->setY(_robot->getY() - Speed * 100 * ((double)SleepTime / 1000) * sin(_robot->getYaw()));

	std::cout<<"Action:Move"<<std::endl;
}

MoveForward::~MoveForward() {
	// TODO Auto-generated destructor stub
}

