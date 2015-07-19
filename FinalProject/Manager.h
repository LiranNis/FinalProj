/*
 * Manager.h
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include "Plans/PlanMoveToDest.h"
#include "Robot.h"
#include "Map.h"
#include "ConfigurationManager.h"
#include "PathPlanner.h"

class Manager {
	Behavior* _curr;
	Robot* _robot;
	Map* _map;
	Plan* _plan;
	ConfigurationManager* _config;

public:
	Manager(Robot* robot, Plan* plan);
	void run();
	virtual ~Manager();
};

#endif /* MANAGER_H_ */
