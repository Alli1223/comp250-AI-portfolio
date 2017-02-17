#include "stdafx.h"
#include "Agent.h"


Agent::Agent()
{
}


Agent::~Agent()
{
}

void Agent::Update()
{
	if (agentStatus == "FoundPath")
	{
		// Move Right
		if (getX() > path[pathPointIterator].getX() && getY() == path[pathPointIterator].getY())
		{
			setX(getX() + 1);
			movementDirection = "Right";
		}
		// Move Left
		if (getX() < path[pathPointIterator].getX() && getY() == path[pathPointIterator].getY())
		{
			setX(getX() - 1);
			movementDirection = "Left";
		}
		// Move Down
		if (getY() > path[pathPointIterator].getY() && getX() == path[pathPointIterator].getX())
		{
			setY(getY() + 1);
			movementDirection = "Down";
		}
		// Move Up
		if (getY() < path[pathPointIterator].getY() && getX() == path[pathPointIterator].getX())
		{
			setY(getY() - 1);
			movementDirection = "Up";
		}
		// If the agent is at the point then iterate to the next point
		else if (getX() == path[pathPointIterator].getX() && getY() == path[pathPointIterator].getY())
		{
			pathPointIterator++;
		}


	}
		
	
}

void Agent::Move(Level& level, Point& StartPoint, Point& EndPoint)
{
	
	path = pathfinder.findPath(level, StartPoint, EndPoint);
	agentStatus = "FoundPath";
	
}