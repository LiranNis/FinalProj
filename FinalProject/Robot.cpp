/*
 * Robot.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#include "Robot.h"

Robot::Robot(char* ip, int port)
{
	_pc = new PlayerClient(ip,port);
	_pp = new Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);

	_pp->SetMotorEnable(true);
	//For fixing Player's reading BUG
	for(int i=0;i<15;i++)
		Read();
}

void Robot::Read()
{
	_pc->Read();
}

void Robot::SetSpeed(float xSpeed, float AngularSpeed)
{
	_pp->SetSpeed(xSpeed, AngularSpeed);
}

bool Robot::IsDirectedToWayPoint()
{
	return true;
}

Robot::~Robot()
{
	delete _pc;
	delete _pp;
	delete _lp;
}

