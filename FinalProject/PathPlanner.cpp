#include "PathPlanner.h"

void PathPlanner::pathPlannerInit(int** Grid, uint width, uint height, int obstacleIdentifier)
{
	this->_graph = new Graph(Grid, width, height, obstacleIdentifier);
}

int PathPlanner::heuristicCost(int VStart, int VDest)
{
	return this->_graph->getManhattanDistance(VStart, VDest);
}

bool PathPlanner::isInSet(list<int>* source, int target)
{
	for (list<int>::iterator iter = source->begin(); iter != source->end(); ++iter)
	{
		if (*iter == target) return true;
	}

	return false;
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
	int* g_score,* f_score, *cameFrom, lowestFScoreVrtx, currVertex;
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
	lowestFScoreVrtx = Start;

	while (!openSet.empty())
	{
		int tentative_g_score;
		currVertex = lowestFScoreVrtx;
		openSet.remove(currVertex);
		closedSet.push_front(currVertex);

		if (currVertex == Goal) goto success;

		vector<int> adjacent = this->_graph->getAdjacent(currVertex);

		for (vector<int>::iterator adjVertex = adjacent.begin(); adjVertex != adjacent.end(); ++adjVertex)
		{
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
						if (lowestFScoreVrtx > f_score[*adjVertex])
							lowestFScoreVrtx = *adjVertex;
					}
				}
			}
		}
	}

	closedSet.clear();

success:
	delete[] g_score;
	delete[] f_score;
	delete[] cameFrom;

	return closedSet;
}
