/*
 * Behavior.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "Behavior.h"

Behavior::Behavior(Robot* robot)
{
	_robot = robot;
}

void Behavior::AddBeh(Behavior* next)
{
	_behVect.push_back(next);
}

Behavior* Behavior::SelectNext()
{
	return _behVect.begin()[0];
}

Behavior::~Behavior()
{
}

