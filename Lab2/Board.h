#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Board
{
	vector<vector<char>> grid;
	vector<int> queensPos;
	int gridSize;
	int conflictAmount = 0;
	bool checkFrame(int i, int j);
	void countConflicts();
public:
	Board(int gridSize = 8);
	Board(const Board& anotherBoard);
	void putQueens();
	int getGridSize();
	int getConflictAmount();
	void printBoard();
	void moveFigure(int& column, int& dist);
	Board operator=(const Board& anotherBoard);
	bool operator==(const Board& rightBoard);
};

