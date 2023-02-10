#pragma once
#include "Node.h"
#include <queue>
#include <set>
#include <algorithm>

class StatesTree
{
	Node* root;
	int amountMemoryStates;
	int amountBoardStates;
	int iter;
	bool DLS(Node* node, int& depthLimit);
public:
	StatesTree();
	Node* getRoot();
	void IDS();
	void AStar();
};