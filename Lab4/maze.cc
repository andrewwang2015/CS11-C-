#include "maze.hh"
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <algorithm>

using namespace std;

// Constructors
Maze::Maze(int rows, int cols)
{
	this->numRows = rows;
	this->numCols = cols;

	// We need additional cells to accomodate for the walls
    int arrSize = (2 * this->numRows + 1) * (2 * this->numCols + 1);
	this->cells = new MazeCell[arrSize];
	this->setStart(0,0);
    this->setEnd(rows - 1, cols - 1);
    this->clear();

}

Maze::Maze(const Maze &m)
{
    this->numRows = m.numRows;
    this->numCols = m.numCols;
    this->start = m.getStart();
    this->end = m.getEnd();

    int arrSize = (2 * this->numRows + 1) * (2 * this->numCols + 1);
    this->cells = new MazeCell[arrSize];
    for (int i = 0 ; i < arrSize; i++)
    {
        this->cells[i] = m.cells[i];
    }

}

// Destructor 
Maze::~Maze()
{
    delete[] this->cells;
}

Maze & Maze::operator=(const Maze &m)
{
    if (this != &m)
    {
        delete[] this->cells;
        this->numRows = m.numRows;
        this->numCols = m.numCols;
        this->start = m.getStart();
        this->end = m.getEnd();

        int arrSize = (2 * this->numRows + 1) * (2 * this->numCols + 1);
        this->cells = new MazeCell[arrSize];
        for (int i = 0 ; i < arrSize; i++)
        {
            this->cells[i] = m.cells[i];
        }
    }
    return *this;

}
// Public functions

int Maze::getNumRows() const
{
	return this->numRows;
}

int Maze::getNumCols() const
{
	return this->numCols;
}

Location Maze::getStart() const
{
	return this->start;
}

Location Maze::getEnd() const
{
    return this->end;
}
void Maze::setStart(int row, int col)
{
	this->start = Location(row, col);
}

void Maze::setEnd(int row, int col)
{
    this->end = Location(row, col);
}

void Maze::clear()
{
    int arrSize = (2 * this->numRows + 1) * (2 * this->numCols + 1);
    for (int i = 0 ; i < arrSize; i++)
    {
        this->cells[i] = MazeCell::EMPTY;
    }
}

MazeCell Maze::getCell(int cellRow, int cellCol) const
{
    assert(cellRow >= 0 && cellRow < this->numRows);
    assert(cellCol >= 0 && cellCol < this->numCols);
    int index = this->getArrayIndex(cellRow, cellCol);
    return this->cells[index];
}

void Maze::setCell(int cellRow, int cellCol, MazeCell val)
{
    assert(cellRow >= 0 && cellRow < this->numRows);
    assert(cellCol >= 0 && cellCol < this->numCols);
    int index = this->getArrayIndex(cellRow, cellCol);
    this->cells[index] = val;
}

Location Maze::adjustLocation(int row, int col, Direction direction) const
{
    switch(direction)
    {
        case Direction::NORTH:
            row -= 1;
            break;

        case Direction::EAST:
            col += 1;
            break;

        case Direction::SOUTH:
            row += 1;
            break;

        case Direction::WEST:
            col -= 1;
            break;
        default: 
            assert(false);
    }
    return Location(row, col);
}

void Maze::setWall(int cellRow, int cellCol, Direction direction)
{
    assert(cellRow >= 0 && cellRow < this->numRows);
    assert(cellCol >= 0 && cellCol < this->numCols);
    Location exp = getCellArrayCoord(cellRow, cellCol);
    Location newLoc = adjustLocation(exp.row, exp.col, direction);
    int index = this->getArrayIndexExp(newLoc.row, newLoc.col);
    this->cells[index] = MazeCell::WALL;
}

bool Maze::hasWall(int cellRow, int cellCol, Direction direction) const
{
    assert(cellRow >= 0 && cellRow < this->numRows);
    assert(cellCol >= 0 && cellCol < this->numCols);
    Location exp = getCellArrayCoord(cellRow, cellCol);
    Location newLoc = adjustLocation(exp.row, exp.col, direction);
    int index = this->getArrayIndexExp(newLoc.row, newLoc.col);    
    return this->cells[index] == MazeCell::WALL;
}

void Maze::clearWall(int cellRow, int cellCol, Direction direction)
{
    assert(cellRow >= 0 && cellRow < this->numRows);
    assert(cellCol >= 0 && cellCol < this->numCols);
    Location exp = getCellArrayCoord(cellRow, cellCol);
    Location newLoc = adjustLocation(exp.row, exp.col, direction);
    int index = this->getArrayIndexExp(newLoc.row, newLoc.col);  
    this->cells[index] = MazeCell::EMPTY;
}

void Maze::setAllWalls()
{
    for (int i = 0; i < this->numRows; i++)
    {
        for (int j = 0; j < this->numCols; j++)
        {
            this->setWall(i, j, Direction::NORTH);
            this->setWall(i, j, Direction::WEST);
            if (j == this->numCols - 1)
            {
                this->setWall(i, j, Direction::EAST);
            }
            if (i == this->numRows - 1)
            {
                this->setWall(i, j, Direction::SOUTH);
            }
        }
    }
}

void Maze::setVisited(int cellRow, int cellCol)
{
    assert(cellRow >= 0 && cellRow < this->numRows);
    assert(cellCol >= 0 && cellCol < this->numCols);
    Location exp = getCellArrayCoord(cellRow, cellCol);
    int index = this->getArrayIndexExp(exp.row, exp.col);  
    this->cells[index] = MazeCell::VISITED;
}

bool Maze::isVisited(int cellRow, int cellCol) const
{
    assert(cellRow >= 0 && cellRow < this->numRows);
    assert(cellCol >= 0 && cellCol < this->numCols);
    Location exp = getCellArrayCoord(cellRow, cellCol);
    int index = this->getArrayIndexExp(exp.row, exp.col);  
    return this->cells[index] == MazeCell::VISITED;
}

int Maze::convertToIndex(int n) const
{
    return 2 * n + 1;
}

Location Maze::getNeighborCell(int cellRow, int cellCol, Direction direction) const
{
    assert(cellRow >= 0 && cellRow < this->numRows);
    assert(cellCol >= 0 && cellCol < this->numCols);
    Location newLoc = adjustLocation(cellRow, cellCol, direction);
    assert(newLoc.row >= 0 && newLoc.row < this->numRows);
    assert(newLoc.col >= 0 && newLoc.col < this->numCols);
    return newLoc;
}


Location Maze::getCellArrayCoord(int cellRow, int cellCol) const
{
    assert(cellRow >= 0 && cellRow < this->numRows);
    assert(cellCol >= 0 && cellCol < this->numCols);
    int expRow = convertToIndex(cellRow);
    int expCol = convertToIndex(cellCol);
    return Location(expRow, expCol);
}

int Maze::getArrayIndex(int row, int col) const
{
    int expRow = convertToIndex(row);
    int expCol = convertToIndex(col);
    int expTotalCols = convertToIndex(this->numCols);
    return expRow * expTotalCols + expCol;
}

int Maze::getArrayIndexExp(int row, int col) const
{
    int expTotalCols = convertToIndex(this->numCols);
    return row * expTotalCols + col;
}

void Maze::print(ostream &os) const
{
    os << this->numRows << " " << this->numCols << endl;
    for (int i = 0; i < this->numRows; i++)
    {
        // Output walls above specific row
        for (int j = 0; j < this->numCols; j++)
        {
            os << "+";
            if (this->hasWall(i, j, Direction::NORTH))
            {
                os << "---";
            }
            else
            {
                os << "   ";
            }
        }
        os << "+" << endl;

        for (int j = 0; j < this->numCols; j++)
        {
            bool isWall = false;
            if (this->hasWall(i, j, Direction::WEST))
            {
                os << "|";
                isWall = true;
            }
            if (!isWall)
            {
                os << " ";
            }
            if (this->start.row == i && this->start.col == j)
            {
                cout << " S ";
            }
            else if (this->end.row == i && this->end.col == j)
            {
                cout << " E ";
            }
            else
            {
                cout << "   ";
            }
        }
        if (this->hasWall(i, this->numCols-1, Direction::EAST))
        {
            os << "|" <<endl;

        }
        else
        {
            os << endl;
        }
    }

    // Below last row
    for (int j = 0; j < this->numCols; j++)
    {
        os << "+";
        if (this->hasWall(this->numRows - 1, j, Direction::SOUTH))
        {
            os << "---";
        }
        else
        {
            os << "   ";
        }
    }
    os << "+" << endl;
    return;
}