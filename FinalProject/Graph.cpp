#include "Graph.h"

Graph::Graph(int** Grid, uint width, uint height, int obstacleIdentifier)
{
	this->_dimension = width * height;

	if (width > 0 && height > 0)
	{
		this->_matrix = new int*[this->_dimension];

		for (unsigned int currVertex = 0; currVertex < this->_dimension; ++currVertex)
		{
			// Allocate neighbors for each vertex
			this->_matrix[currVertex] = new int[this->MAX_ADJACENT];

			for (unsigned int currNeighbor = 0; currNeighbor < this->MAX_ADJACENT; ++currNeighbor)
			{
				this->_matrix[currVertex][currNeighbor] = EMPTY;
			}
		}

		for (unsigned int x = 0; x < width; ++x)
		{
			for (unsigned int y = 0; y < height; ++y)
			{
				// Place that can't be reached, thus can't lead anywhere
				if (Grid[x][y] == obstacleIdentifier)
					continue;

				for (unsigned int currDir = 0; currDir  < this->MAX_ADJACENT; ++currDir )
				{
					if(	(this->isValidDir(x, y, currDir, width, height)) &&
						(Grid[x + DIR[currDir][0]][y + DIR[currDir][1]] != obstacleIdentifier))
					{
						this->_matrix[x*y][currDir] = (x + DIR[currDir][0]) * (y + DIR[currDir][1]);
					}
				}
			}
		}

		this->_vertexes.resize(this->_dimension)
		for (int v = 0; v < this->_dimension; ++v)
		{
			this->_vertexes[v] = v;
		}
	}
}

bool Graph::isValidDir(uint x, uint y, uint direction, uint width, uint height)
{
	return (x + DIR[direction][0] >= 0) &&
			(x + DIR[direction][0] < width) &&
			(y + DIR[direction][1] >= 0) &&
			(y + DIR[direction][1] < height);
}

vector<int> Graph::getAdjacent(int vertex)
{
	vector<int> adj(this->MAX_ADJACENT);

	for (uint i = 0; i < this->MAX_ADJACENT; ++i)
	{
		adj[i] = this->_matrix[vertex][i];
	}

	return adj;
}

vector<int> Graph::getVertexes()
{
	return new vector<int>(this->_vertexes);
}
