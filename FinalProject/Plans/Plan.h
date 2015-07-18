/*
 * Plan.h
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#ifndef PLAN_H_
#define PLAN_H_

#include "../Behaviors/Behavior.h"
#include "../Robot.h"

class Plan
{
protected:
	Behavior* _start;

public:
	Plan(Robot* robot);
	virtual Behavior* GetStartPoint();
	virtual ~Plan();
};

#endif /* PLAN_H_ */
