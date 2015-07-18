/*
 * PlanMoveToDest.h
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#ifndef PLANMOVETODEST_H_
#define PLANMOVETODEST_H_

#include "Plan.h"
#include "../Behaviors/MoveForward.h"
#include "../Behaviors/TurnToDest.h"

class PlanMoveToDest : public Plan
{
	Behavior* _beh[2];

public:
	PlanMoveToDest(Robot* robot);
	Behavior* getStartPoint();
	virtual ~PlanMoveToDest();
};

#endif /* PLANMOVETODEST_H_ */
