/*
 * main.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: colman
 */

#include <iostream>
#include <fstream>
#include <string.h>


using namespace std;

#include "WriteToPng/pngUtil.h"

int main()
{
	string MapPath = "~/Desktop/roboticLabMap.png";
	double StartX = 362, StartY = 305, StartYaw = 20;
	double DestX = 169, DestY = 138;
	double RobotWidth = 30, RobotHeight = 30;
	double CMInPixel = 2.5; // Pixels in CM
	double GridSize = 10; // Grid CM

	char* ParametersFilePath = "~/Desktop/parameters.txt";

	string CurrentLine;
	ifstream ParametersFile;
	ParametersFile.open(ParametersFilePath);
	if (ParametersFile.is_open())
	{
		while (!ParametersFile.eof())
		{
			// Get a line from the file.
			getline(ParametersFile, CurrentLine);

			// Find the location of the colon.
			size_t ColonPosition = CurrentLine.find(":");

			// Get the string before the colon.
			string CurrentParameter = CurrentLine.substr (0, ColonPosition);

			// If the current parameter is the map path.
			if (!CurrentParameter.compare("map"))
			{
				// Get the map path, skip the space.
				MapPath = CurrentLine.substr (ColonPosition + 1);
			}

			// If the current parameter is the start location.
			if (!CurrentParameter.compare("startLocation"))
			{
				size_t FirstSpacePos = CurrentLine.find(" ", ColonPosition);
				size_t SecondSpacePos = CurrentLine.find(" ", FirstSpacePos + 1);
				size_t ThirdSpacePos = CurrentLine.find(" ", ThirdSpacePos + 1);

				//startX = CurrentLine.substr(FirstSpacePos, SecondSpacePos);
			}

			// If the current parameter is the goal.
			if (!CurrentParameter.compare("goal"))
			{

			}

			// If the current parameter is the robot size.
			if (!CurrentParameter.compare("robotSize"))
			{

			}

			// If the current parameter is the map resolution.
			if (!CurrentParameter.compare("mapResolutionCM"))
			{

			}

			// If the current parameter is the grid resolution.
			if (!CurrentParameter.compare("gridResolutionCM"))
			{

			}

		}
	}
	else
	{
		cout << "Can not open the file, Please locate the file on your desktop and name it parameters.txt" << endl;
	}




	unsigned InflateNumber = 5;
	InflateToGridMap(MapPath, InflateNumber, CMInPixel, GridSize);
}
