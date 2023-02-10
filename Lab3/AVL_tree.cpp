#include "AVL_tree.h"

Info::Info(std::string name, std::string surname) : name(name), surname(surname) {}

Node::Node(int primaryKey, Info row) : primaryKey(primaryKey), row(row), height(1), left(nullptr), right(nullptr) {}

int Node::getHeight(Node* currentNode)
{
	if (!currentNode)
		return 0;
	else
		return currentNode->height;
}

void Node::updateHeight(Node* currentNode)
{
	if (currentNode)
		currentNode->height = std::max(getHeight(currentNode->left), getHeight(currentNode->right)) + 1;
}

Node* Node::findSuccessor(Node* currentNode)
{
	if (!currentNode->left)
		return currentNode;
	else
		return findSuccessor(currentNode->left);
}

int Node::checkBalanse(Node* currentNode)
{
	if (!currentNode)
		return 0;
	int leftHeight = getHeight(currentNode->left);
	int rightHeight = getHeight(currentNode->right);
	int difference = leftHeight - rightHeight;
	return difference;
}

Node* Node::insert(Node* currentNode, int primaryKey, Info row, bool& result)
{
	if (!currentNode)
		return new Node(primaryKey, row);
	else if (currentNode->primaryKey == primaryKey)
	{
		result = false;
		return currentNode;
	}
	else if (currentNode->primaryKey > primaryKey)
		currentNode->left = insert(currentNode->left, primaryKey, row, result);
	else
		currentNode->right = insert(currentNode->right, primaryKey, row, result);
	updateHeight(currentNode);
	return balanceTree(currentNode);
}

Node* Node::update(Node* currentNode, int primaryKey, Info newData, bool& result)
{
	if (!currentNode)
	{
		result = false;
		return nullptr;
	}
	if (currentNode->primaryKey < primaryKey)
		currentNode->right = update(currentNode->right, primaryKey, newData, result);
	else if (currentNode->primaryKey > primaryKey)
		currentNode->left = update(currentNode->left, primaryKey, newData, result);
	else
		currentNode->row = newData;
	return currentNode;
}

Node* Node::erase(Node* currentNode, int primaryKey, bool& result)
{
	if (!currentNode)
	{
		result = false;
		return nullptr;
	}
	if (currentNode->primaryKey < primaryKey)
		currentNode->right = erase(currentNode->right, primaryKey, result);
	else if (currentNode->primaryKey > primaryKey)
		currentNode->left = erase(currentNode->left, primaryKey, result);
	else
	{
		if (!currentNode->left && !currentNode->right)
		{
			delete currentNode;
			return nullptr;
		}
		else if (currentNode->left && currentNode->right)
		{
			Node* successor = findSuccessor(currentNode->right);
			currentNode->primaryKey = successor->primaryKey;
			currentNode->row = successor->row;
			currentNode->right = erase(currentNode->right, successor->primaryKey, result);
		}
		else
		{
			currentNode = currentNode->left != nullptr ? currentNode->left : currentNode->right;
		}
	}
	updateHeight(currentNode);
	return balanceTree(currentNode);
}

Node* Node::find(Node* currentNode, int primaryKey, int& compares)
{
	if (!currentNode)
		return nullptr;
	if (++compares && currentNode->primaryKey < primaryKey)
		return find(currentNode->right, primaryKey, compares);
	else if (++compares && currentNode->primaryKey > primaryKey)
		return find(currentNode->left, primaryKey, compares);
	else
		return currentNode;
}

Node* Node::rightTurn(Node* currentNode)
{
	Node* temp = currentNode;
	currentNode = currentNode->left;
	temp->left = currentNode->right;
	currentNode->right = temp;
	updateHeight(currentNode->right);
	updateHeight(currentNode);
	return currentNode;
}

Node* Node::leftTurn(Node* currentNode)
{
	Node* temp = currentNode;
	currentNode = currentNode->right;
	temp->right = currentNode->left;
	currentNode->left = temp;
	updateHeight(currentNode->left);
	updateHeight(currentNode);
	return currentNode;
}

Node* Node::balanceTree(Node* currentNode)
{
	int balance = checkBalanse(currentNode);
	if (balance > 1 && checkBalanse(currentNode->left) >= 0)
		return rightTurn(currentNode);
	else if (balance < -1 && checkBalanse(currentNode->right) <= 0)
		return leftTurn(currentNode);
	else if (balance > 1 && checkBalanse(currentNode->left) < 0)
	{
		currentNode->left = leftTurn(currentNode->left);
		return rightTurn(currentNode);
	}
	else if (balance < -1 && checkBalanse(currentNode->right) > 0)
	{
		currentNode->right = rightTurn(currentNode->right);
		return leftTurn(currentNode);
	}
	return currentNode;
}

void Node::showTree(Node* currentNode, int space)
{
	if (!currentNode)
		return;
	space += 10;
	showTree(currentNode->right, space);
	std::cout << std::endl;
	for (int i = 10; i < space; i++)
		std::cout << " ";
	std::cout << std::setw(10) << currentNode->primaryKey << std::endl;
	showTree(currentNode->left, space);
}

void Node::deleteNodes(Node* currentNode)
{
	if (!currentNode)
		return;
	deleteNodes(currentNode->left);
	deleteNodes(currentNode->right);
	delete currentNode;
}

AVL_tree::AVL_tree(std::string path) : root(nullptr)
{
	this->deserialize(path);
}

bool AVL_tree::insert(int primaryKey, Info newRow)
{
	bool result = true;
	root = root->insert(root, primaryKey, newRow, result);
	return result;
}

bool AVL_tree::erase(int primaryKey)
{
	bool result = true;
	root = root->erase(root, primaryKey, result);
	return result;
}

bool AVL_tree::update(int primaryKey, Info updateRow)
{
	bool result = true;
	root = root->update(root, primaryKey, updateRow, result);
	return result;
}

Info AVL_tree::select(int primaryKey, int& compares)
{
	Node* temp = nullptr;
	Info result;
	if (isNotEmpty())
	{
		temp = temp->find(root, primaryKey, compares);
		if (temp)
			result = temp->row;
	}
	return result;
}

void AVL_tree::showTree()
{
	if (isNotEmpty())
		root->showTree(root);
}

bool AVL_tree::isNotEmpty()
{
	return root;
}

AVL_tree::~AVL_tree()
{
	root->deleteNodes(root);
	root = nullptr;
}

bool AVL_tree::serialize(std::string path)
{
	std::ofstream out(path, std::ios::binary);
	if (!this->isNotEmpty())
	{
		out.close();
		remove(path.c_str());
		return false;
	}
	bool flag = out.is_open();
	int defaultKey = -1;
	std::string defaultString = "";
	int defaultHeight = -1;
	auto storeData = [&path, &out, &defaultKey, &defaultHeight, &defaultString](Node*& currentNode)
	{
		if (!currentNode)
		{
			out.write(reinterpret_cast<char*>(&defaultKey), sizeof(defaultKey));
			out.write(reinterpret_cast<char*>(&defaultHeight), sizeof(defaultHeight));
			size_t len = 1;
			for (int i = 0; i < 2; i++)
			{
				out.write(reinterpret_cast<char*>(&len), sizeof(len));
				out.write(const_cast<char*>(defaultString.c_str()), len);
			}
		}
		else
		{
			int tempID = currentNode->primaryKey;
			int tempHeight = currentNode->height;
			std::string tempName = currentNode->row.name;
			std::string tempSurname = currentNode->row.surname;
			out.write(reinterpret_cast<char*>(&tempID), sizeof(tempID));
			out.write(reinterpret_cast<char*>(&tempHeight), sizeof(tempHeight));
			size_t len = tempName.length() + 1;
			out.write(reinterpret_cast<char*>(&len), sizeof(len));
			out.write(const_cast<char*>(tempName.c_str()), len);
			len = tempSurname.length() + 1;
			out.write(reinterpret_cast<char*>(&len), sizeof(len));
			out.write(const_cast<char*>(tempSurname.c_str()), len);
		}
	};
	Node* temp = nullptr;
	std::queue<Node*> breadth;
	breadth.push(root);
	int amountOfNodes = std::pow(2, root->height) - 1;
	while (amountOfNodes != 0)
	{
		temp = breadth.front();
		breadth.pop();
		storeData(temp);
		amountOfNodes--;
		if (temp)
		{
			breadth.push(temp->left);
			breadth.push(temp->right);
		}
		else if (amountOfNodes != 0)
		{
			for (int i = 0; i < 2; i++)
				breadth.push(nullptr);
		}
	}
	out.close();
	return true;
}

bool AVL_tree::deserialize(std::string path)
{
	std::ifstream in(path, std::ios::binary);
	in.seekg(0, std::ios::beg);
	if (!in.is_open())
		return false;
	else
	{
		auto getData = [&path, &in](Node** currentNode)
		{
			int tempID;
			int tempHeight;
			size_t stringLength = 0;
			in.read(reinterpret_cast<char*>(&tempID), sizeof(tempID));
			in.read(reinterpret_cast<char*>(&tempHeight), sizeof(tempHeight));
			in.read(reinterpret_cast<char*>(&stringLength), sizeof(stringLength));
			if (!stringLength)
				return;
			char* tempName = new char[stringLength];
			in.read(tempName, stringLength);
			in.read(reinterpret_cast<char*>(&stringLength), sizeof(stringLength));
			char* tempSurname = new char[stringLength];
			in.read(tempSurname, stringLength);
			if (tempID == -1)
			{
				*currentNode = nullptr;
			}
			else
			{
				*currentNode = new Node(tempID, Info(std::string(tempName), std::string(tempSurname)));
				(*currentNode)->height = tempHeight;
			}
			delete[] tempName;
			delete[] tempSurname;
		};
		std::queue<Node**> breadth;
		breadth.push(&root);
		while (!in.eof() && !breadth.empty())
		{
			Node** temp = breadth.front();
			breadth.pop();
			getData(temp);
			if ((*temp))
			{
				breadth.push(&((*temp)->left));
				breadth.push(&((*temp)->right));
			}
		}
		in.close();
		return true;
	}
}

void Node::traversal(Node* current, std::vector<std::pair<int, Info>>& data)
{
	if (!current)
		return;
	traversal(current->left, data);
	data.push_back(std::make_pair(current->primaryKey, current->row));
	traversal(current->right, data);
}

std::vector<std::pair<int, Info>> AVL_tree::getAllNodes()
{
	std::vector<std::pair<int, Info>> data;
	root->traversal(root, data);
	return data;
}

bool operator==(Info& left, Info& right)
{
	if (left.name == right.name && left.surname == right.surname)
		return true;
	else 
		return false;
}
