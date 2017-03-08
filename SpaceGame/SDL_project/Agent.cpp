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
	setCellX((int)getX() / level.getCellSize());
	setCellY((int)getY() / level.getCellSize());


	// Decrease/Increase stats over time
	tiredness = tiredness + tirednessDecayRate;
	hunger = hunger - hungerDecayRate;
	toiletLevel = toiletLevel + toiletDecayRate;
	

	// If the agent has a path move along it
	if (agentStatus == "TraversingPath")
	{

		// Magnitude is speed

		double deltaY = getY() - (double)(path[pathPointIterator].getY() * cellSize);
		double deltaX = getX() - (double)(path[pathPointIterator].getX() * cellSize);

		//pythagoras
		double dist;


		dist = sqrt(pow(deltaX, 2) + pow(deltaY, 2));


		//dist = sqrt(deltaX + deltaY);
		// Calculate direction
		double angleInDegrees = atan2(deltaY, deltaX) * 360.0 / PI;

		if (angleInDegrees <= 0.0)
			angleInDegrees = 360.0 - angleInDegrees;

		deltaX = (double)(sin(angleInDegrees) * speed);
		deltaY = (double)(cos(angleInDegrees) * speed);
		agentRotation = angleInDegrees;

		setX(getX() + deltaX);
		setY(getY() + -deltaY);





		

		if (getCellX() == path[pathPointIterator].getX() && getCellY() == path[pathPointIterator].getY())
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

	if (this->getHealth() <= 0)
		this->isAlive = false;

	// Agent will wonder randomly when idle
	if (this->agentStatus == "Idle")
	{
		bool foundEndPoint = false;
		Point endPoint;
		while (!foundEndPoint)
		{
			int x = rand() % level.getLevelWidth();
			int y = rand() % level.getLevelHeight();
			if (level.grid[x][y]->isWalkable)
			{
				endPoint = Point(level.grid[x][y]->getX(), level.grid[x][y]->getY());
				foundEndPoint = true;
				this->agentStatus = "Wandering";
			}
		}
		Point startPoint(this->getX() / level.getCellSize(), this->getY() / level.getCellSize());
		this->Move(level, startPoint, endPoint);
	}

	

	/* DECREASE OXYGEN WHEN IN CELL WITH NO OXYGEN */
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
