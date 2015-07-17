#include "PathPlanner.h"

//*************************************************************************
// DEBUG SECTION
//*************************************************************************

#include<iostream>
void openAddR(int v)
{
	std::cout << "Open set add : " << v << std::endl;
}

void openDelR(int v)
{
	std::cout << "Open set remove : " << v << std::endl;
}

void closedAddR(int v)
{
	std::cout << "Closed set add : " << v << std::endl;
}

void closedDelR(int v)
{
	std::cout << "Closed set remove : " << v << std::endl;
}

void printArray(vector<int> *array)
{
	vector<int>::iterator iter = array->begin();
	cout << "{";
	for (; iter != array->end(); ++iter) {
		cout << " " << *iter << endl;

	}
	cout << "}";
}
//*************************************************************************
// DEBUG SECTION END
//*************************************************************************


void PathPlanner::pathPlannerInit(int** Grid, uint width, uint height, int obstacleIdentifier)
{
	cout << "grid width : " << width << " height : " << height << endl;
	this->_graph = new Graph(Grid, width, height, obstacleIdentifier);
}

int PathPlanner::heuristicCost(int VStart, int VDest)
{
	return this->_graph->getDotDistance(VStart, VDest);
}

bool PathPlanner::isInSet(list<int>* source, int target)
{
	for (list<int>::iterator iter = source->begin(); iter != source->end(); ++iter)
	{
		if (*iter == target) return true;
	}

	return false;
}

int PathPlanner::getMinFScoreVertex(list<int>* source, int* f_score)
{
	if (source->empty())
	{
		cout << "Super error empty set" << endl;
		return -1;
	}

	int min = *(source->begin());
	for (list<int>::iterator iter = source->begin(); iter != source->end(); ++iter) {
		min = f_score[min] > f_score[*iter] ? *iter : min;
	}

	return min;
}

list<int> PathPlanner::reconstructPath(int* cameFrom, int startVertex)
{
	int currVertex = startVertex;
	list<int> totalPath;

	while (currVertex != -1)
	{
		totalPath.push_back(currVertex);
		currVertex = cameFrom[currVertex];
	}

	return totalPath;
}

list<int> PathPlanner::AStar(int StartX, int StartY, int GoalX, int GoalY)
{
	int Start = this->_graph->indexToVertex(StartX, StartY),
		Goal = 	this->_graph->indexToVertex(GoalX, GoalY);
	int* g_score,* f_score, *cameFrom, currVertex;
	g_score = new int [this->_graph->getVertexCount()];
	f_score = new int [this->_graph->getVertexCount()];
	cameFrom = new int [this->_graph->getVertexCount()];

	list<int> 	closedSet, // *closedSet for the return
				openSet; // open list for the algorithm to iterate over

	for (int i = 0; i < this->_graph->getVertexCount(); ++i)
	{
		g_score[i] = f_score[i] = 0;
		cameFrom[i] = -1;
	}

	openSet.push_back(Start);
	g_score[Start] = 0;
	f_score[Start] = g_score[Start] + this->heuristicCost(Start,Goal);

	while (!openSet.empty())
	{
		int tentative_g_score;
		currVertex = getMinFScoreVertex(&openSet, f_score);
		openSet.remove(currVertex);
		closedSet.push_front(currVertex);
		cout << "Current Vertex : " << currVertex << endl;
		if (currVertex == Goal)
		{
			list<int> pathToGoal = reconstructPath(cameFrom, Goal);
			delete[] f_score;
			delete[] g_score;
			delete[] cameFrom;

			return pathToGoal;
		}

		vector<int> adjacent = this->_graph->getAdjacent(currVertex);
		cout << "Adjacent of " << currVertex << " : ";
		printArray(&adjacent);
		for (vector<int>::iterator adjVertex = adjacent.begin(); adjVertex != adjacent.end(); ++adjVertex)
		{
			cout << "Current Adjacent : " << *adjVertex << endl;
			if (!this->isInSet(&closedSet, *adjVertex))
			{
				bool isAdjInOpenSet = this->isInSet(&openSet, *adjVertex);
				tentative_g_score = g_score[currVertex] + 1; // Weight between neighbors is 1

				if (!isAdjInOpenSet or tentative_g_score < g_score[*adjVertex])
				{
					cameFrom[*adjVertex] = currVertex;
					g_score[*adjVertex] = tentative_g_score;
					f_score[*adjVertex] = g_score[*adjVertex] + heuristicCost(*adjVertex, Goal);

					if (!isAdjInOpenSet)
					{
						openSet.push_back(*adjVertex);
					}
				}
			}
		}
	}

	closedSet.clear();

	delete[] g_score;
	delete[] f_score;
	delete[] cameFrom;

	return closedSet;
}

list<int> PathPlanner::createWayPoints(list<int> completePath)
{
	unsigned int 	i = 0,
					j = 0,
					pathLength = completePath.size();
	const unsigned int SOFT_FACTOR = 9;
	list<int> waypoints;
	list<int>::iterator iter = completePath.begin();

	if (pathLength > 2)
	{
		for (; i < completePath.size() - 1; i+=SOFT_FACTOR)
		{
			waypoints.push_back(*(iter));
			for (j = 0; j < SOFT_FACTOR && iter != completePath.end(); ++j, ++iter);
		}

		waypoints.push_back(*completePath.rbegin());
	}

	return waypoints;
}
