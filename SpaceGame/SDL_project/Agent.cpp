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

	// Decrease stats over time
	tiredness = tiredness + tirednessDecayRate;
	hunger = hunger - hungerDecayRate;

	//behaviour.BehaviourTree(*this, level);
	

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

	if (this->getHealth() <= 0)
		this->isAlive = false;

	if (this->tiredness > 3.0)
	{
		Point bedlocation = FindNearestCelltoAgent(*this, level, "Bed");
		Point agentLocation(this->x / cellSize, this->y / cellSize);
		this->Move(level, agentLocation, bedlocation);
	}



	// Agent will wonder randomly when idle
	if (this->agentStatus == "Idle")
	{
		bool foundEndPoint = false;
		Point endPoint;
		while (!foundEndPoint)
		{
			int x = rand() % level.getLevelWidth();
			int y = rand() % level.getLevelHeight();
			if (level.grid[x][y]->isRoom)
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
	else if (level.grid[x / level.getCellSize()][y / level.getCellSize()]->getOxygenLevel() > 0.0)
		this->setOxygenLevel(this->getOxygenLevel() + oxygenDecayRate);
	
	//If the agent reaches a bed
	if (level.grid[x / level.getCellSize()][y / level.getCellSize()]->isBed && agentStatus == "SearchingForBed")
	{
		//Increase rest at twice the speed
		tiredness = tiredness + tirednessDecayRate * 2;
		agentStatus = "Sleeping";
	}
	
}
Point Agent::FindNearestCelltoAgent(Agent& agent, Level& level, std::string cellType)
{
	Point endPoint;

	// Do a local search of nearest 10 cells 
	for (int x = agent.getX() - localSearchSize; x <= agent.getX() + localSearchSize; x++)
	{
		for (int y = agent.getY() - localSearchSize; y <= agent.getY() + localSearchSize; y++)
		{
			if (x > 0 && y > 0 && x < level.grid.size() && y < level.grid[x].size())
			{
				if (cellType == "BED" || cellType == "Bed")
				{
					if (level.grid[x][y]->isBed)
					{
						endPoint = Point(x, y);
						return endPoint;
					}
				}
				else if (cellType == "TOILET" || cellType == "Toilet")
				{
					if (level.grid[x][y]->isToilet)
					{
						endPoint = Point(x, y);
						return endPoint;
					}
				}
			}
		}
	}

	localSearchSize = localSearchSize * 2;

	// Seach entire map
	for (int x = 0; x <= level.grid.size(); x++)
	{
		for (int y = 0; y <= level.grid[x].size(); y++)
		{
			if (cellType == "BED" || cellType == "Bed")
			{
				if (level.grid[x][y]->isBed)
				{
					endPoint = Point(x, y);
					return endPoint;
				}
			}
			else if (cellType == "TOILET" || cellType == "Toilet")
			{
				if (level.grid[x][y]->isToilet)
				{
					endPoint = Point(x, y);
					return endPoint;
				}
			}
		}
	}
}

void Agent::Move(Level& level, Point& StartPoint, Point& EndPoint)
{
	path = pathfinder.findPath(level, StartPoint, EndPoint);
	if (path.size() > 0)
		agentStatus = "FoundPath";
}