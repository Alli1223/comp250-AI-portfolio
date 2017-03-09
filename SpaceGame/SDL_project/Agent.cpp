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
		//point.getX() * level.getCellSize() + level.getCellSize() / 2;

		float deltaY = getY()  - path[pathPointIterator].getY() * cellSize;
		float deltaX = getX()  - path[pathPointIterator].getX() * cellSize;

		float dist = sqrt(deltaX * deltaX + deltaY * deltaY);

		// Normalize 
		deltaX /= dist;
		deltaY /= dist;

		// Calculate direction
		float angleInDegrees = atan2(deltaY, deltaX) * 180.0 / PI;

		if (angleInDegrees < 0.0 || angleInDegrees > 360.0)
			angleInDegrees = 360.0 - angleInDegrees;

		//deltaX = (cos(angleInDegrees) * speed);
		//deltaY = (sin(angleInDegrees) * speed);
		agentRotation = angleInDegrees;
		
		// Multiply direction by magnitude 
		deltaX *= speed;
		deltaY *= speed;

		setX(getX() + -deltaX);
		setY(getY() + -deltaY);
		
		// If the agent reaches the node in the path
		if (getCellX() == path[pathPointIterator].getX() && getCellY() == path[pathPointIterator].getY())
		{
			// If the Agent has reached the end of the path then reset the pathfinder and set the agent to idle.
			if (pathPointIterator >= path.size())
			{
				pathPointIterator = 0;
				agentStatus = "Idle";

			}
			else
				pathPointIterator++;
		}




	}

	if (this->getHealth() <= 0)
		this->isAlive = false;

	// Agent will wonder randomly when idle
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

	

	/* DECREASE OXYGEN WHEN IN CELL WITH NO OXYGEN 
	// If the cell has no oxygen
	if (level.grid[x / level.getCellSize()][y / level.getCellSize()]->getOxygenLevel() == 0.0)
	{
		// And agent has personal oxygen
		if (this->getOxygenLevel() > 0.0)
			this->setOxygenLevel(this->getOxygenLevel() - oxygenDecayRate); //Reduce it's personal oxygen

		// Decay health if the agent has no personal oxygen left
		else if (this->getOxygenLevel() <= 0.0)
			this->setHealth(this->getHealth() - healthDecayRate);
	}
	else if (level.grid[x / level.getCellSize()][y / level.getCellSize()]->getOxygenLevel() > 0.0 && oxygenLevel < 3.0)
		this->setOxygenLevel(this->getOxygenLevel() + oxygenDecayRate);
	
	//If the agent reaches a bed
	if (level.grid[x / level.getCellSize()][y / level.getCellSize()]->isBed)
	{
		//Increase rest at twice the speed
		tiredness = 0.0;
		agentNeed = "NA";
	}

	//If the agent reaches a Toilet
	if (level.grid[x / level.getCellSize()][y / level.getCellSize()]->isToilet)
	{
		//Increase rest at twice the speed
		toiletLevel = 0.0;
		agentNeed = "NA";
	}
	*/
	
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
