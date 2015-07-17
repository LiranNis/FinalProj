#include "Graph.h"

#include <iostream> // For debug

Graph::Graph(int** Grid, uint width, uint height, int obstacleIdentifier)
{
	this->_dimension = width * height;
	this->_widthOrigin = width;

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

		for (unsigned int x = 0; x < height; ++x)
		{
			for (unsigned int y = 0; y < width; ++y)
			{
				cout << " accessing index: [" << x << "] [ " << y << "]" << endl;
				// Place that can't be reached, thus can't lead anywhere
				if (Grid[x][y] == obstacleIdentifier)
					continue;

				for (unsigned int currDir = 0; currDir  < this->MAX_ADJACENT; ++currDir )
				{
					if(	(this->isValidDir(x, y, currDir, width, height)) &&
						(Grid[x + DIR[currDir][0]][y + DIR[currDir][1]] != obstacleIdentifier))
					{
						//std::cout << "Matrix index : " << (x*width) + y << std::endl;
						//std::cout << "New Adjacent : [" << ((x + DIR[currDir][0]) * width) + (y + DIR[currDir][1]) <<  "] direct : " << currDir << std::endl;
						this->_matrix[(x*width) + y][currDir] = ((x + DIR[currDir][0]) * width) + (y + DIR[currDir][1]);
					}
				}
			}
		}

		this->_vertexes.resize(this->_dimension);
		for (uint v = 0; v < this->_dimension; ++v)
		{
			this->_vertexes[v] = v;
		}
	}
	cout << " width origin : " << width << endl;
}

bool Graph::isValidDir(uint x, uint y, uint direction, uint width, uint height)
{
	/*if ((x + DIR[direction][0] >= 0) &&
			(x + DIR[direction][0] < width) &&
			(y + DIR[direction][1] >= 0) &&
			(y + DIR[direction][1] < height))
	{
		std::cout << "Valid : [" << x + DIR[direction][0] << "]" << "[" << y + DIR[direction][1] << "]" << std::endl;
	}*/

	return (x + DIR[direction][0] >= 0) &&
			(x + DIR[direction][0] < height) &&
			(y + DIR[direction][1] >= 0) &&
			(y + DIR[direction][1] < width);
}

vector<int> Graph::getAdjacent(int vertex)
{
	vector<int> adj;

	for (uint i = 0; i < this->MAX_ADJACENT; ++i)
	{
		if (this->_matrix[vertex][i] != EMPTY)
			adj.push_back(this->_matrix[vertex][i]);
	}

	return adj;
}

vector<int>* Graph::getVertexes()
{
	return new vector<int>(this->_vertexes);
}

int Graph::indexToVertex(int x, int y)
{
	return (x * this->_widthOrigin) + y;
}

int Graph::getVertexCount()
{
	return this->_dimension;
}

int Graph::getManhattanDistance(int VSource, int VDest)
{
	return (abs((int)((VSource / this->_widthOrigin) - (VDest / this->_widthOrigin))) +
			abs((int)((VSource % this->_widthOrigin) - (VDest % this->_widthOrigin))));
}

int Graph::getDotDistance(int VSource, int VDest)
{
	return sqrt(
	(((int)((VSource / this->_widthOrigin) - (VDest / this->_widthOrigin))) *
	((int)((VSource / this->_widthOrigin) - (VDest / this->_widthOrigin)))) +
	(((int)((VSource % this->_widthOrigin) - (VDest % this->_widthOrigin))) *
			((int)((VSource % this->_widthOrigin) - (VDest % this->_widthOrigin)))));
}

Graph::~Graph()
{
	for (unsigned int currVertex = 0; currVertex < this->_dimension; ++currVertex)
	{
		// Delete neighbors for each vertex
		delete[] this->_matrix[currVertex];
	}

	delete[] this->_matrix;
}
