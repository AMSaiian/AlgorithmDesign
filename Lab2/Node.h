#pragma once
#include "Board.h"

class Node
{
	Board stateBoard;
	int depth;
	vector<Node*> children;
public:
	Node();
	Node(Node& another);
	void expandChildren();
	int getDepth();
	Board getBoard();
	vector<Node*> getChildren();
};

