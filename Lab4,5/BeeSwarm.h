#pragma once
#include "Graph.h"
#include "GreedyColorer.h"
#include <queue>
class BeeSwarm
{
	int iterationsLimit;
	int scouts;
	int foragers;
	int foragersForDistrict;
	vector<Graph> districts;
	void foragerCycle(int districtNum, int foragerAmount);
	queue<Graph> scoutCycle();
public:
	BeeSwarm(int iterationsLimit, int scouts, int foragers);
	Graph colourGraph(Graph inputGraph);
};

