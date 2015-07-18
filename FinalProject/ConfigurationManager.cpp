/*
 * ConfigurationManager.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "ConfigurationManager.h"

ConfigurationManager::ConfigurationManager(char* ParametersFilePath)
{
	std::string CurrentLine;
	ifstream ParametersFile;
	ParametersFile.open(ParametersFilePath);

	// If the file didnt open, print error and exit.
	if (!ParametersFile.is_open())
	{
		cout << "Can not open the file, Please locate the file in the project folder and name it parameters.txt" << endl;
		exit(1);
	}

	// While there is parameters in the parameters file.
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
			// Find the first space.
			size_t FirstSpacePos = CurrentLine.find(" ", ColonPosition);

			// Find the second space.
			size_t SecondSpacePos = CurrentLine.find(" ", FirstSpacePos + 1);

			// Find the third space.
			size_t ThirdSpacePos = CurrentLine.find(" ", SecondSpacePos + 1);

			// Get the start X (between the first two spaces).
			StartX = atof(CurrentLine.substr(FirstSpacePos, SecondSpacePos).c_str());

			// Get the start Y (between the second and third space).
			StartY = atof(CurrentLine.substr(SecondSpacePos, ThirdSpacePos).c_str());

			// Get the start Yaw (between the first space and the end of the line).
			StartYaw = atof(CurrentLine.substr(ThirdSpacePos).c_str());

		}

		// If the current parameter is the goal.
		if (!CurrentParameter.compare("goal"))
		{
			// Find the first space.
			size_t FirstSpacePos = CurrentLine.find(" ", ColonPosition);

			// Find the second space.
			size_t SecondSpacePos = CurrentLine.find(" ", FirstSpacePos + 1);

			// Get the goal X (between the first two spaces).
			GoalX = atof(CurrentLine.substr(FirstSpacePos, SecondSpacePos).c_str());

			// Get the goal Y (between the second and third space).
			GoalY = atof(CurrentLine.substr(SecondSpacePos).c_str());
		}

		// If the current parameter is the robot size.
		if (!CurrentParameter.compare("robotSize"))
		{
			// Find the first space.
			size_t FirstSpacePos = CurrentLine.find(" ", ColonPosition);

			// Find the second space.
			size_t SecondSpacePos = CurrentLine.find(" ", FirstSpacePos + 1);

			// Get the robot width (between the first two spaces).
			RobotWidth = atof(CurrentLine.substr(FirstSpacePos, SecondSpacePos).c_str());

			// Get the robot height (between the second and third space).
			RobotHeight = atof(CurrentLine.substr(SecondSpacePos).c_str());
		}

		// If the current parameter is the map resolution.
		if (!CurrentParameter.compare("MapResolutionCM"))
		{
			// Find the first space.
			size_t FirstSpacePos = CurrentLine.find(" ", ColonPosition);

			// Get the map resolution CM (between the first two spaces).
			CMInPixel = atof(CurrentLine.substr(FirstSpacePos).c_str());
		}

		// If the current parameter is the grid resolution.
		if (!CurrentParameter.compare("GridResolutionCM"))
		{
			// Find the first space.
			size_t FirstSpacePos = CurrentLine.find(" ", ColonPosition);

			// Get the grid size (between the first two spaces).
			GridSize = atof(CurrentLine.substr(FirstSpacePos).c_str());
		}

	}

	ParametersFile.close();

	// Replace tilde with user home folder.
	size_t TildePosition = MapPath.find("~");
	if (TildePosition != string::npos)
	{
		char* HomePath = getenv("HOME");
		MapPath.replace(0 , sizeof(HomePath) - 2, HomePath);
	}

	size_t NewRowPosition;

	// Delete carriage return (new lines).
	if (!MapPath.empty() && ((NewRowPosition = MapPath.find("\r")) != string::npos))
	{
		MapPath.erase(NewRowPosition);
	}
}

ConfigurationManager::~ConfigurationManager() {
	// TODO Auto-generated destructor stub
}

