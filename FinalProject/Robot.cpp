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
	{
		Read();
	}
}

double Robot::RadianToDegree(double Radian)
{
	return (Radian * (180 / M_PI));
}

double Robot::DegreeToRadian(double Degree)
{
	return (Degree * (M_PI / 180));
}

void Robot::Read()
{
	_pc->Read();
}

void Robot::SetSpeed(float xSpeed, float AngularSpeed)
{
	_pp->SetSpeed(xSpeed, AngularSpeed);
	sleep(100);

}

void Robot::SetNextWayPoint(unsigned int NextWayPointWidth,unsigned int NextWayPointHeight)
{
	_NextWayPointHeight = NextWayPointHeight;
	_NextWayPointWidth = NextWayPointWidth;
}

void Robot::SetLocation(double x, double y, double yaw)
{
	_x = x;
	_y = y;
	_yaw = yaw;

	_pp->SetOdometry(0, 0, DegreeToRadian(yaw));
}

bool Robot::IsDirectedToWayPoint()
{
	return true;
}

bool Robot::ArrivedToWayPoint()
{

}

Robot::~Robot()
{
	delete _pc;
	delete _pp;
	delete _lp;
}

