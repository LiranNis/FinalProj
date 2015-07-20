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
	_yaw = DegreeToRadian(yaw);

	_pp->SetOdometry(0, 0, _yaw);
}

bool Robot::IsDirectedToWayPoint()
{
	double Radian = atan2(_y - _NextWayPointHeight, _x - _NextWayPointWidth);
	//Radian = Radian < 0 ? M_PI + Radian : Radian;
	Radian = M_PI - Radian;
	//std::cout << _yaw;
	if (((Radian - _yaw)<0?_yaw-Radian:Radian-_yaw) < AngularTolerance)
	{

		std::cout<< Radian << std::endl;
		return true;
	}
	else
	{
		//std::cout<< atan2(_y - _NextWayPointHeight, _x - _NextWayPointWidth) << " " << _yaw << std::endl;
		return false;
	}
}

bool Robot::ArrivedToWayPoint()
{
	if (sqrt(pow(_x - _NextWayPointWidth, 2) + pow(_y - _NextWayPointHeight, 2)) < Tolerance)
	{
		//std::cout << "nextX:" << _NextWayPointWidth << " X:" << _x << " nextY:" << _NextWayPointHeight << " Y:" << _y;
		//std::cout << sqrt(pow(_x - _NextWayPointWidth, 2) + pow(_y - _NextWayPointHeight, 2));
		return true;
	}
	else
	{
		//std::cout << "nextX:" << _NextWayPointWidth << " X:" << _x << " nextY:" << _NextWayPointHeight << " Y:" << _y;
		//std::cout << sqrt(pow(_x - _NextWayPointWidth, 2) + pow(_y - _NextWayPointHeight, 2));
		return false;
	}
}

Robot::~Robot()
{
	delete _pc;
	delete _pp;
	delete _lp;
}

