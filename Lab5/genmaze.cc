#include "maze.hh"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/*
 * Checks the neighbor in specific direction of current location
 * and adds it to vector of directions if valid and not visited.
*/

void addDirectionOption(const Maze &maze, const Location &current,
	Direction dir, vector<Direction> &v)
{
	Location neighbor = maze.getNeighborCell(current.row, current.col,
		dir);
	MazeCell n = maze.getCell(neighbor.row, neighbor.col);
	if (!maze.isVisited(neighbor.row, neighbor.col) && n != MazeCell::WALL)
	{
		v.push_back(dir);
	}
}

/*
 * Gets the possible directions we can move in from the current location
*/
void getPossibleDirections(const Maze &maze, const Location &current,
	vector<Direction> &v)

{
	if (current.row > 0)
	{
		addDirectionOption(maze, current, Direction::NORTH, v);
	}
	if (current.col > 0)
	{
		addDirectionOption(maze, current, Direction::WEST, v);
	}
	if (current.row < maze.getNumRows() - 1)
	{
		addDirectionOption(maze, current, Direction::SOUTH, v);
	}
	if (current.col < maze.getNumCols() - 1)
	{
		addDirectionOption(maze, current, Direction::EAST, v);
	}
}

int main(int argc, char**argv)
{
	if (argc != 3)
	{
		cout << "usage: ./genmaze numRows numCols" << endl;
		exit(1);
	}
	int numRows = atoi(argv[1]);
	int numCols = atoi(argv[2]);
	srand(time(nullptr));

	Maze maze = Maze(numRows, numCols);
	vector<Location> path;
	// Clearing and setting of start/end done in constructors
	maze.setAllWalls();
	Location start = maze.getStart();
	maze.setVisited(start.row, start.col);
	path.push_back(start);

	while (!path.empty())
	{
		Location current = path.back();
		if (current == maze.getEnd())
		{
			path.pop_back();    // Pops the last element
			continue;
		}
		vector<Direction> options;
		getPossibleDirections(maze, current, options);
		if (options.empty())
		{
			path.pop_back();
			continue;
		}

		// Time to choose a random direction 
		int index = rand() % options.size();
		Direction randDir = options[index];

		// Now that we have a random direction,
		// we must clear the wall in that direction
		maze.clearWall(current.row, current.col, randDir);

		// Get next location to add onto vector
		Location next = maze.getNeighborCell(current.row, current.col, randDir);
		maze.setVisited(next.row, next.col);
		path.push_back(next);
	}

	// Alas, let's print out the maze.
	maze.print(std::cout);

	return 1;
}
