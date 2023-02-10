#include "Board.h"

bool Board::checkFrame(int i, int j)
{
    return (i >= 0 && i < gridSize && j >= 0 && j < gridSize);
}

void Board::countConflicts()
{
    this->conflictAmount = 0;
    auto checkLeft = [this](const int& row, const int& column) 
    {
        for (int j = column - 1; j > -1; j--)
        {
            if (grid[row][j] == '*')
            {
                conflictAmount++;
                break;
            }
        }
    };
    auto checkRight = [this](const int& row, const int& column) 
    {
        for (int j = column + 1; j < gridSize; j++)
        {
            if (grid[row][j] == '*')
            {
                conflictAmount++;
                break;
            }
        }
    };
    auto checkLeftDiagonal = [this](const int& row, const int& column) 
    {
        for (int i = row - 1, j = column - 1; i > -1 && j > -1; i--, j--)
        {
            if (grid[i][j] == '*')
            {
                conflictAmount++;
                break;
            }
        }
        for (int i = row + 1, j = column + 1; i < gridSize && j < gridSize; i++, j++)
        {
            if (grid[i][j] == '*')
            {
                conflictAmount++;
                break;
            }
        }
    };
    auto checkRightDiagonal = [this](const int& row, const int& column) 
    {
        for (int i = row - 1, j = column + 1; i > -1 && j < gridSize; i--, j++)
        {
            if (grid[i][j] == '*')
            {
                conflictAmount++;
                break;
            }
        }
        for (int i = row + 1, j = column - 1; i < gridSize && j > -1; i++, j--)
        {
            if (grid[i][j] == '*')
            {
                conflictAmount++;
                break;
            }
        }
    };
    int currentQueenPos = -1;
    for (int j = 0; j < gridSize; j++)
    {
        currentQueenPos = queensPos[j];
        checkLeft(currentQueenPos, j);
        checkRight(currentQueenPos, j);
        checkLeftDiagonal(currentQueenPos, j);
        checkRightDiagonal(currentQueenPos, j);
    }
}

Board::Board(int gridSize)
{
    this->gridSize = gridSize;
    grid = vector<vector<char>>(gridSize, vector<char>(gridSize, (char)39));
    queensPos = vector<int>(gridSize, -1);
}

Board::Board(const Board& anotherBoard)
{
    this->gridSize = anotherBoard.gridSize;
    this->grid = vector<vector<char>>(anotherBoard.grid);
    this->queensPos = vector<int>(anotherBoard.queensPos);
    this->conflictAmount = anotherBoard.conflictAmount;
}

void Board::putQueens()
{
    int pos;
    for (int i = 0; i < gridSize; i++)
    {
        pos = rand() % gridSize;
        grid[pos][i] = '*';
        queensPos[i] = pos;
    }
    countConflicts();
}

int Board::getGridSize()
{
    return gridSize;
}

int Board::getConflictAmount()
{
    return conflictAmount;
}

void Board::printBoard()
{   
    cout << "    ";
    for (int i = 0; i < gridSize; i++)
    {
        cout << (char)(97 + i) << "   ";
    }
    cout << "\n\n";
    for (int i = 0; i < gridSize; i++)
    {
        cout << i + 1 << "   ";
        for (int j = 0; j < gridSize; j++)
        {
            cout << grid[i][j] << "   ";
        }
        cout << "\n\n";
    }
    cout << endl << endl;
}

void Board::moveFigure(int& column, int& dist)
{
    int oldPos = queensPos[column];
    int newPos = oldPos + dist;
    newPos %= gridSize;
    grid[oldPos][column] = (char)39;
    grid[newPos][column] = '*';
    queensPos[column] = newPos;
    this->countConflicts();
}

Board Board::operator=(const Board& anotherBoard)
{
    if (this != &anotherBoard)
    {
        this->gridSize = anotherBoard.gridSize;
        this->grid = vector<vector<char>>(anotherBoard.grid);
        this->queensPos = vector<int>(anotherBoard.queensPos);
        this->conflictAmount = anotherBoard.conflictAmount;
    }
    return *this;
}

bool Board::operator==(const Board& rightBoard)
{
    return this->grid == rightBoard.grid;
}
