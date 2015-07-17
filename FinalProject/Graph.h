#ifndef GRAPH_H_
#define GRAPH_H_

#include <cstdlib>
#include <vector>
#include <math.h>

using namespace std;

static const int EMPTY = -1,
				 DIR[][4] = {{0, -1}, {-1, 0}, {0,1}, {1, 0}},
				 DIR_COUNT = 4;
class Graph
{
private:
	int** _matrix; // Graph representation
	vector<int> _vertexes;
	uint _dimension, // Vertex count
		 _widthOrigin;
	bool isValidDir(uint x, uint y, uint direction, uint width, uint height);
	~Graph();
public:
	static const uint MAX_ADJACENT = 4; // Graph based on grid matrix, connected to 4 adjacent at most
	Graph(int** Grid, uint width, uint height, int obstacleIdentifier);
	vector<int> getAdjacent(int vertex);
	vector<int>* getVertexes();
	int indexToVertex(int x, int y);
	int getVertexCount();
	int getManhattanDistance(int VSource, int VDest);
	int getDotDistance(int VSource, int VDest);
};

#endif
