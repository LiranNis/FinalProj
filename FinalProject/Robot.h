/*
 * Robot.h
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>
#include <math.h>
#include <unistd.h>

using namespace PlayerCc;

class Robot
{
	PlayerClient* _pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;
	double _x, _y, _yaw;
	const double Tolerance = 0.5;
	unsigned int _NextWayPointWidth, _NextWayPointHeight;

public:
	Robot(char* ip, int port);
	void Read();
	void SetSpeed(float xSpeed, float AngularSpeed);
	void SetLocation(double aX, double aY, double aYaw);
	void SetNextWayPoint(unsigned int NextWayPointWidth,unsigned int NextWayPointHeight);
	double DegreeToRadian(double Degree);
	double RadianToDegree(double Radian);
	bool ArrivedToWayPoint();
	bool IsDirectedToWayPoint();
	virtual ~Robot();

	double getX() const {
		return _x;
	}

	double getY() const {
		return _y;
	}

	double getYaw() const {
		return _yaw;
	}
};

#endif /* ROBOT_H_ */
