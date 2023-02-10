#pragma once
#include "Graph.h"

class GreedyColorer
{
	set<int> usedColors;
	void colorVer(Graph& graph, int verNum);
	void traversalGraph(Graph& graph);
public:
	GreedyColorer();
	Graph greedyColoring(Graph graph);
};
