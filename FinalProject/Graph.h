#ifndef GRAPH_H_
#define GRAPH_H_

#include <cstdlib>
#include <vector>
#include <math.h>

using namespace std;

static const int EMPTY = -1,
				 DIR[][8] = {{-1,-1}, {0, -1}, {1, -1}, {0,-1}, {0,1}, {1, -1}, {1, 0}, {1, 1}};
class Graph
{
private:
	int** _matrix; // Graph representation
	vector<int> _vertexes;
	uint _dimension, // Vertex count
		 _widthOrigin;
	bool isValidDir(uint x, uint y, uint direction, uint width, uint height);

public:
	static const uint MAX_ADJACENT = 8; // Graph based on grid matrix, connected to 8 adjacent at most
	Graph(int** Grid, uint width, uint height, int obstacleIdentifier);
	vector<int> getAdjacent(int vertex);
	vector<int>* getVertexes();
	int indexToVertex(int x, int y);
	int getVertexCount();
	int getManhattanDistance(int VSource, int VDest);
};

#endif
