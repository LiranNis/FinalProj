/*
 * Behavior.h
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_

#include <vector>
#include "../Robot.h"

class Behavior
{
	std::vector<Behavior*> _behVect;

protected:
	Robot* _robot;

public:
	Behavior(Robot* robot);
	virtual bool StartCond() = 0;
	virtual bool StopCond() = 0;
	virtual void Action() = 0;
	void AddBeh(Behavior* Next);
	Behavior* SelectNext();
	virtual ~Behavior();
};

#endif /* BEHAVIOR_H_ */
