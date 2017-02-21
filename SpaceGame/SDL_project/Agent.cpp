#include "stdafx.h"
#include "Agent.h"


Agent::Agent()
{
}


Agent::~Agent()
{
}

void Agent::Update(Level& level)
{
	int cellSize = level.getCellSize();

	// If the agent has a path move along it
	if (agentStatus == "FoundPath")
	{
		// Move Left
		if (getX() / cellSize > path[pathPointIterator].getX() && getY() / cellSize == path[pathPointIterator].getY())
		{
			setX(getX() - speed);
			movementDirection = "Left";
		}
		// Move Right
		if (getX() / cellSize < path[pathPointIterator].getX() && getY() / cellSize == path[pathPointIterator].getY())
		{
			setX(getX() + speed);
			movementDirection = "Right";
		}
		// Move Up
		if (getY() / cellSize > path[pathPointIterator].getY() && getX() / cellSize == path[pathPointIterator].getX())
		{
			setY(getY() - speed);
			movementDirection = "Up";
		}
		// Move Down
		if (getY() / cellSize < path[pathPointIterator].getY() && getX() / cellSize == path[pathPointIterator].getX())
		{
			setY(getY() + speed);
			movementDirection = "Down";
		}



		// If the agent is at the point then iterate to the next point
		if (getX() / cellSize == path[pathPointIterator].getX() && getY() / cellSize == path[pathPointIterator].getY())
		{
			pathPointIterator++;
		}

		// If the Agent has reached the end of the path then reset the pathfinder and set the agent to idle.
		if (pathPointIterator >= path.size())
		{
			agentStatus = "Idle";
			pathPointIterator = 0;
			path.erase(path.begin(), path.end());
		}

	}

	// If the agent dies
	if (!this->isAlive)
	{
		//->agentStatus = "Dead";
	}
	/* TODO: finish this code to make the agent wonder randomly
	if (this->agentStatus == "Idle")
	{
		bool foundEndPoint = false;
		Point endPoint;
		while (!foundEndPoint)
		{
			int x = rand() % level.getLevelWidth() / cellSize;
			int y = rand() % level.getLevelHeight() / cellSize;
			if (level.grid[x][y]->isRoom)
			{
				endPoint = Point(level.grid[x][y]->getX(), level.grid[x][y]->getY());
				foundEndPoint = true;
			}
		}
		Point startPoint(this->getX() / cellSize, this->getY() / cellSize);
		this->Move(level, startPoint, endPoint);
	}
	*/

	//! Changes what the agent looks like based on how much oxyen it has
	if (level.grid[this->getX() / cellSize][this->getY() / cellSize]->oxygenLevel < 30)
	{
		this->characterType = "NPC";
	}
	else
	{
		this->characterType = "Player";
	}
}

void Agent::Move(Level& level, Point& StartPoint, Point& EndPoint)
{
	// Only move if Idle
	if (agentStatus == "Idle")
	{
		path = pathfinder.findPath(level, StartPoint, EndPoint);
		if (path.size() > 0)
			agentStatus = "FoundPath";
	}

}