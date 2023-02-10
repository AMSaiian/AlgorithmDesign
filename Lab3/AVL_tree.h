#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <queue>
#include <fstream>


struct Info
{
	std::string name;
	std::string surname;
	Info(std::string name = "", std::string surname = "");
	friend bool operator==(Info& left, Info& right);
};

class Node 
{
public:
	int primaryKey;
	int height;
	Node* left;
	Node* right;
	Info row;
public:
	Node(int primaryKey, Info row);
	int getHeight(Node* currentNode);
	int checkBalanse(Node* currentNode);
	void updateHeight(Node* currentNode);
	Node* findSuccessor(Node* currentNode);
	Node* insert(Node* currentNode, int primaryKey, Info row, bool& result);
	Node* update(Node* currentNode, int primaryKey, Info newData, bool& result);
	Node* erase(Node* currentNode, int primaryKey, bool& result);
	Node* find(Node* currentNode, int primaryKey, int& compares);
	Node* rightTurn(Node* currentNode);
	Node* leftTurn(Node* currentNode);
	Node* balanceTree(Node* currentNode);
	void showTree(Node* currentNode, int space = 0);
	void deleteNodes(Node* currentNode);
	void traversal(Node* current, std::vector<std::pair<int, Info>>& data);
	friend class AVL_tree;
};

class AVL_tree
{
	Node* root;
public:
	AVL_tree(std::string parh = "");
	bool insert(int primaryKey, Info newRow);
	bool erase(int primaryKey);
	bool update(int primaryKey, Info updateRow);
	Info select(int primaryKey, int& compares);
	void showTree();
	bool isNotEmpty();
	~AVL_tree();
	bool serialize(std::string path);
	bool deserialize(std::string path);
	std::vector<std::pair<int, Info>> getAllNodes();
};
