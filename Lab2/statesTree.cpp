#include "statesTree.h"
#define workLimit 1400000

bool StatesTree::DLS(Node* node, int& depthLimit)
{
	//node->getBoard().printBoard();
	//cout << "Depth: " << node->getDepth() << endl;
	//cout << "Limit: " << depthLimit << endl;
	//cout << "Conflicts: " << node->getBoard().getConflictAmount() << endl << endl << endl << endl;
	iter++;
	if (node->getBoard().getConflictAmount() == 0)
	{
		cout << "Solution:\n\n";
		node->getBoard().printBoard();
		cout << "Depth: " << node->getDepth() << endl;
		cout << "Limit: " << depthLimit << endl;
		return true;
	}
	if (node->getDepth() < depthLimit)
	{
		node->expandChildren();
		amountMemoryStates += 56;
		amountBoardStates += 56;
		if (amountBoardStates >= workLimit)
		{
			return false;
		}
		for (int elem = 0; elem < node->getChildren().size(); elem++)
		{
			if (DLS(node->getChildren()[elem], depthLimit))
			{
				return true;
			}
		}
	}
	return false;
}

StatesTree::StatesTree()
{
    root = new Node();
    amountMemoryStates = amountBoardStates = 1;
    iter = 0;
    cout << "Problem state:\n\n";
    root->getBoard().printBoard();
	cout << "Amount of conflicts: " << root->getBoard().getConflictAmount() << "\n\n\n";
}

Node* StatesTree::getRoot()
{
    return root;
}

void StatesTree::IDS()
{
    int limit = 1;
	bool success = true;
    while (!(DLS(root, limit)))
    {
		if (amountBoardStates >= workLimit)
		{
			success = false;
			break;
		}
		++limit;
        amountMemoryStates = 1;
    }
	if (success)
	{
		cout << "Iterations: " << iter << endl;
		cout << "All states: " << amountBoardStates << endl;
		cout << "Memory states: " << amountMemoryStates << endl;
	}
	else
		cout << "Algorithm has got blind corner. Force break\n";
}

void StatesTree::AStar()
{
	auto priority = [](Node* first, Node* second)
	{
		if (first->getBoard().getConflictAmount() != second->getBoard().getConflictAmount())
		{
			return first->getBoard().getConflictAmount() > second->getBoard().getConflictAmount();
		}
		return first->getDepth() > second->getDepth();
	};
	priority_queue <Node*, vector<Node*>, decltype(priority)> opened(priority);
	vector<Board> closed;
	opened.push(root);
	while (!opened.empty())
	{
		if (opened.top()->getBoard().getConflictAmount() == 0)
		{
			cout << "Solution:\n\n";
			opened.top()->getBoard().printBoard();
			cout << "Depth: " << opened.top()->getDepth() << endl;
			break;
		}
		closed.push_back(opened.top()->getBoard());
		opened.top()->expandChildren();
		vector<Node*> temp = opened.top()->getChildren();
		opened.pop();
		auto checkClosed = [&closed](Node* state)  
		{
			for (int i = 0; i < closed.size(); i++)
			{
				if (state->getBoard() == closed[i])
					return true;
			}
			return false;
		};
		for (int i = 0; i < temp.size(); i++)
		{
			if (checkClosed(temp[i]))
				continue;
			opened.push(temp[i]);
		}
		++iter;
	}
	amountBoardStates = opened.size() + closed.size();
	amountMemoryStates = opened.size();
	cout << "Iterations: " << iter << endl;
	cout << "All states: " << amountBoardStates << endl;
	cout << "Memory states: " << amountMemoryStates << endl;
}
