/*
 * main.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: colman
 */

#include "Robot.h"
#include "Manager.h"
#include "Plans/PlanMoveToDest.h"

int main()
{
	Robot robot("localhost",6665);
	PlanMoveToDest plnMTD(&robot);
	Manager manager(&robot, &plnMTD);
	manager.run();
	return 0;
}
