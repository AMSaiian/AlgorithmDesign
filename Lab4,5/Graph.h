#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <map>

using namespace std;

class Graph
{
	struct Vertex
	{
		int number;
		int colour;
		int degree;
		set<int> neighbours;
		Vertex(int number, int colour = -1, int degree = -1);
	};
	int vertexAmount;
	int degreeLimit;
	int maxDegree;
	int chromaticNum;
	set<int> usedColors;
	vector<Vertex> vertices;
	map<int, vector<int>> degree—onformity;
	bool verifyColor(int& verNum, int& colour);
	void createEdge(int firstVer, int secondVer);
	void defineDegree(int verNum);
public:
	Graph(int degreeLimit = 20, int vertexAmount = 100);
	vector<Vertex>& getVertices();
	int getChromaticNum();
	void generateRandGraph();
	bool changeColour(int verNum, int colour);
	void defineChromaticNum(int usedColors);
	int getVertexAmount();
	int getMaxDegree();
	map<int, vector<int>> getDegree—onformity();
	set<int>& getUsedColors();
	void redefineUsedColors();
};
