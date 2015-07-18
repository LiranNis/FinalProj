/*
 * TurnToDest.h
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#ifndef TURNTODEST_H_
#define TURNTODEST_H_

#include "Behavior.h"

class TurnToDest : public Behavior
{
public:
	TurnToDest(Robot* robot);
	bool StartCond();
	bool StopCond();
	void Action();
	virtual ~TurnToDest();
};

#endif /* TURNTODEST_H_ */
