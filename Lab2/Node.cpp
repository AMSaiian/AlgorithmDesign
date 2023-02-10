#include "Node.h"

Node::Node()
{
	depth = 1;
	stateBoard = Board();
	stateBoard.putQueens();
	children = vector<Node*>(stateBoard.getGridSize() * (stateBoard.getGridSize() - 1));
}

Node::Node(Node& another)
{
	depth = another.depth + 1;
	stateBoard = Board(another.stateBoard);
	children = vector<Node*>(stateBoard.getGridSize() * (stateBoard.getGridSize() - 1));
}

void Node::expandChildren()
{
	int column = 0;
	int shift = 1;
	for (int child = 0; child < children.size(); child++)
	{
		if (shift == this->getBoard().getGridSize())
		{
			column++;
			shift = 1;
		}
		children[child] = new Node(*this);
		children[child]->stateBoard.moveFigure(column, shift);
		++shift;
	}
}

int Node::getDepth()
{
	return depth;
}

Board Node::getBoard()
{
	return stateBoard;
}

vector<Node*> Node::getChildren()
{
	return children;
}
