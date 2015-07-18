/*
 * ConfigurationManager.h
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#ifndef CONFIGURATIONMANAGER_H_
#define CONFIGURATIONMANAGER_H_

#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class ConfigurationManager
{
	std::string MapPath;
	double StartX, StartY, StartYaw;
	double GoalX, GoalY;
	double RobotWidth, RobotHeight;
	double CMInPixel = 2.5; // Pixels in CM
	double GridSize = 10; // Grid CM

public:
	ConfigurationManager(char* ParametersFilePath);
	virtual ~ConfigurationManager();

	double getCmInPixel() const {
		return CMInPixel;
	}

	double getGoalX() const {
		return GoalX;
	}

	double getGoalY() const {
		return GoalY;
	}

	double getGridSize() const {
		return GridSize;
	}

	const std::string& getMapPath() const {
		return MapPath;
	}

	double getRobotHeight() const {
		return RobotHeight;
	}

	double getRobotWidth() const {
		return RobotWidth;
	}

	double getStartX() const {
		return StartX;
	}

	double getStartY() const {
		return StartY;
	}

	double getStartYaw() const {
		return StartYaw;
	}
};

#endif /* CONFIGURATIONMANAGER_H_ */
