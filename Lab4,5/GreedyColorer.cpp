#include "GreedyColorer.h"

void GreedyColorer::colorVer(Graph& graph, int verNum)
{
	int colorNum = 0;
	while (!graph.changeColour(verNum, colorNum))
	{
		colorNum++;
	}
	if (usedColors.count(colorNum) == 0)
		usedColors.insert(colorNum);
}

void GreedyColorer::traversalGraph(Graph& graph)
{
	int uncolored = graph.getVertexAmount();
	int chosenVertex;
	while (uncolored > 0)
	{
		chosenVertex = rand() % graph.getVertexAmount();
		if (graph.getVertices()[chosenVertex].colour == -1)
		{
			colorVer(graph, chosenVertex);
			uncolored--;
		}
	}
}

GreedyColorer::GreedyColorer() : usedColors(set<int>()){}

Graph GreedyColorer::greedyColoring(Graph graph)
{
	usedColors.clear();
	if (graph.getVertexAmount() > 0)
		traversalGraph(graph);
	graph.defineChromaticNum(usedColors.size());
	graph.getUsedColors() = GreedyColorer::usedColors;
	return graph;
}
