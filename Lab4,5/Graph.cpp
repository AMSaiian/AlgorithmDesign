#include "Graph.h"

Graph::Vertex::Vertex(int number, int colour, int degree) : number(number), colour(colour), degree(degree)
{
	neighbours = set<int>();
}

bool Graph::verifyColor(int& verNum, int& colour)
{
	if (vertices[verNum].colour == colour)
		return false;
	if (colour == -1)
		return true;
	for (auto neighbour : vertices[verNum].neighbours)
	{
		if (vertices[neighbour].colour == colour)
			return false;
	}
	return true;
}

void Graph::createEdge(int firstVer, int secondVer)
{
	if (firstVer == secondVer || 
		vertices[secondVer].neighbours.size() == degreeLimit ||
		vertices[firstVer].neighbours.count(secondVer) > 0 || 
		vertices[secondVer].neighbours.count(firstVer) > 0)
		return;
	vertices[firstVer].neighbours.insert(secondVer);
	vertices[secondVer].neighbours.insert(firstVer);
}

void Graph::defineDegree(int verNum)
{
	vertices[verNum].degree = vertices[verNum].neighbours.size();
}

Graph::Graph(int degreeLimit, int vertexAmount) : 
	vertexAmount(vertexAmount), 
	chromaticNum(-1), 
	maxDegree(-1), 
	usedColors(set<int>())
{
	if (degreeLimit >= vertexAmount)
		degreeLimit = vertexAmount - 1;
	this->degreeLimit = degreeLimit;
	if (this->degreeLimit == 0)
	{
		this->degreeLimit = 1;
		this->vertexAmount = 2;
	}
	for (int i = 0; i < this->vertexAmount; i++)
		vertices.emplace_back(Vertex(i));
}

vector<Graph::Vertex>& Graph::getVertices()
{
	return vertices;
}

int Graph::getChromaticNum()
{
	return chromaticNum;
}

void Graph::generateRandGraph()
{
	for (int i = 0; i < vertexAmount; i++)
	{
		int randAmount = rand() % degreeLimit + 1;
		while (vertices[i].neighbours.size() < randAmount)
		{
			int randSecond = rand() % vertexAmount;
			createEdge(i, randSecond);
		}
	}
	for (int i = 0; i < vertexAmount; i++)
	{
		defineDegree(i);
		if (maxDegree < vertices[i].degree)
			maxDegree = vertices[i].degree;
	}
	for (auto vertex : vertices)
	{
		degree—onformity[vertex.degree].push_back(vertex.number);
	}
}

bool Graph::changeColour(int verNum, int colour)
{
	if (verifyColor(verNum, colour))
	{
		vertices[verNum].colour = colour;
		return true;
	}
	else
		return false;
}

void Graph::defineChromaticNum(int usedColors)
{
	chromaticNum = usedColors; 
}

int Graph::getVertexAmount()
{
	return vertexAmount;
}

int Graph::getMaxDegree()
{
	return maxDegree;
}

map<int, vector<int>> Graph::getDegree—onformity()
{
	return degree—onformity;
}

set<int>& Graph::getUsedColors()
{
	return usedColors;
}

void Graph::redefineUsedColors()
{
	usedColors.clear();
	for (auto vertex : vertices)
		usedColors.insert(vertex.colour);
	defineChromaticNum(usedColors.size());
}
