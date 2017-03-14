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
	// Set agents cell x & y tile values
	int cellSize = level.getCellSize();
	setCellX(getX() / level.getCellSize());
	setCellY(getY() / level.getCellSize());


	// Decrease/Increase stats over time
	tiredness = tiredness + tirednessDecayRate;
	hunger = hunger - hungerDecayRate;
	toiletLevel = toiletLevel + toiletDecayRate;
	

	// If the agent has a path move along it
	if (agentStatus == "TraversingPath")
	{
		float deltaY = getY() - path[pathPointIterator].getY() * cellSize;
		float deltaX = getX() - path[pathPointIterator].getX() * cellSize;

		float length = sqrt(deltaX * deltaX + deltaY * deltaY);

		// Normalize 
		deltaX /= length;
		deltaY /= length;

		// Calculate direction
		//float angleInDegrees = atan2(deltaY, deltaX) * 180.0 / PI;

		//if (angleInDegrees < 0.0 || angleInDegrees > 360.0)
			//angleInDegrees = 360.0 - angleInDegrees;

		//deltaX = (cos(angleInDegrees) * speed);
		//deltaY = (sin(angleInDegrees) * speed);
		//agentRotation = angleInDegrees;

		// Multiply direction by magnitude 
		deltaX *= speed;
		deltaY *= speed;

		if (getX() - deltaX > 0 && getY() - deltaY > 0)
		{
			setX(getX() - deltaX);
			setY(getY() - deltaY);
		}
		
		// If the agent reaches the node in the path
		if (getCellX() == path[pathPointIterator].getX() && getCellY() == path[pathPointIterator].getY())
		{
			pathPointIterator++;
		}
	}

	if (this->getHealth() <= 0)
		this->isAlive = false;

	/* Agent will wonder randomly when idle
	if (this->agentStatus == "Idle")
	{
		bool foundEndPoint = false;
		Point endPoint;
		while (!foundEndPoint)
		{
			int x = rand() % level.grid.size();
			int y = rand() % level.grid[x].size();
			if (level.grid[x][y]->isWalkable && level.grid[x][y]->isRoom)
			{
				endPoint = Point(level.grid[x][y]->getX(), level.grid[x][y]->getY());
				foundEndPoint = true;
				this->agentStatus = "Wandering";
			}
		}
		Point startPoint(this->getCellX(), this->getCellY());
		this->Move(level, startPoint, endPoint);
	}
	*/
	

	// If the Agent has reached the end of the path then reset the pathfinder and set the agent to idle.
	if (pathPointIterator >= path.size() && agentStatus == "TraversingPath")
	{
		agentStatus = "Idle";
		pathPointIterator = 0;
	}
}

void Agent::Move(Level& level, Point& StartPoint, Point& EndPoint)
{
	// Erase path
	path.erase(path.begin(), path.end());
	pathPointIterator = 0;

	// Move along path
	path = pathfinder.findPath(level, StartPoint, EndPoint);
	if (path.size() > 0)
		agentStatus = "TraversingPath";
}
