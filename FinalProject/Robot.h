/*
 * Robot.h
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>

using namespace PlayerCc;

class Robot
{
	PlayerClient* _pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;

public:
	Robot(char* ip, int port);
	void Read();
	void SetSpeed(float xSpeed, float AngularSpeed);
	bool IsDirectedToWayPoint();
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
