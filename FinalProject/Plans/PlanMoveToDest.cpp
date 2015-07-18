/*
 * PlanMoveToDest.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "PlanMoveToDest.h"

PlanMoveToDest::PlanMoveToDest(Robot* robot):Plan(robot)
{
	// Creating Behaviors
	_beh[0] = new TurnToDest(robot);
	_beh[1] = new MoveForward(robot);

	// Connecting Behaviors
	_beh[0]->AddBeh(_beh[1]);
	_beh[1]->AddBeh(_beh[0]);

	// Set the start behavior
	_start = _beh[0];
}

PlanMoveToDest::~PlanMoveToDest()
{
	for (int i=0; i < 3; i++)
	{
		delete _beh[i];
	}
}

