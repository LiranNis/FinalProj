/*
 * MoveForward.h
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#ifndef MOVEFORWARD_H_
#define MOVEFORWARD_H_

#include "Behavior.h"
#include <math.h>

class MoveForward : public Behavior
{
public:
	MoveForward(Robot* robot);
	bool StartCond();
	bool StopCond();
	void Action();
	virtual ~MoveForward();
};

#endif /* MOVEFORWARD_H_ */
