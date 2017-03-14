#include "stdafx.h"
#include "AgentBehaviour.h"


AgentBehaviour::AgentBehaviour()
{
}


AgentBehaviour::~AgentBehaviour()
{
}

void AgentBehaviour::DecideTask(Level& level, Agent& agent)
{
	
	BehaviourTree::Sequence *root = new BehaviourTree::Sequence, *sequence1 = new BehaviourTree::Sequence;
	BehaviourTree::Selector* selector1 = new BehaviourTree::Selector;


}

void AgentBehaviour::UpdateLevelInfo(Level& level, int cellX, int cellY)
{
	if (level.grid[cellX][cellY]->isBed)
	{
		levelHasBed = true;
	}
	if (level.grid[cellX][cellY]->isToilet)
	{
		LevelHasToilet = true;
	}
}

Point AgentBehaviour::FindNearestCelltoAgent(Agent& agent, Level& level, std::string cellType)
{
	Point endPoint;
	
	while (localSearchSize < level.grid.size())
	{
		// Do a local search of nearest cells 
		for (int x = agent.getCellX() - localSearchSize; x <= agent.getCellX() + localSearchSize; x++)
		{
			for (int y = agent.getCellY() - localSearchSize; y <= agent.getCellY() + localSearchSize; y++)
			{
				// If within grid
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
		// Double search size if not found
		localSearchSize = localSearchSize * 2;
	}
	localSearchSize = 2;
}

