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
	if (agentStatus == "FoundPath")
	{
		// Move Right
		if (getX() / cellSize > path[pathPointIterator].getX() && getY() / cellSize == path[pathPointIterator].getY())
		{
			setX(getX() - 1);
			movementDirection = "Right";
		}
		// Move Left
		if (getX() / cellSize < path[pathPointIterator].getX() && getY() / cellSize == path[pathPointIterator].getY())
		{
			setX(getX() + 1);
			movementDirection = "Left";
		}
		// Move Down
		if (getY() / cellSize > path[pathPointIterator].getY() && getX() / cellSize == path[pathPointIterator].getX())
		{
			setY(getY() - 1);
			movementDirection = "Down";
		}
		// Move Up
		if (getY() / cellSize < path[pathPointIterator].getY() && getX() / cellSize == path[pathPointIterator].getX())
		{
			setY(getY() + 1);
			movementDirection = "Up";
		}



		// If the agent is at the point then iterate to the next point
		if (getX() / cellSize == path[pathPointIterator].getX() && getY() / cellSize == path[pathPointIterator].getY())
		{
			pathPointIterator++;
		}

		if (pathPointIterator == path.size())
		{
			agentStatus = "Idle";
			pathPointIterator = 0;
		}

	}
		
	
}

void Agent::Move(Level& level, Point& StartPoint, Point& EndPoint)
{
	// Only move if Idle
	if (agentStatus == "Idle")
	{
		path = pathfinder.findPath(level, StartPoint, EndPoint);
		agentStatus = "FoundPath";
	}
	
}