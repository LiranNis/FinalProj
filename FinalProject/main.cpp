/*
 * main.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: colman
 */

#include "Map.h"
#include "PathPlanner.h"

int main()
{

	char* ParametersFilePath = "parameters.txt";
	Map *map = new Map(ParametersFilePath);
	return 0;
}
