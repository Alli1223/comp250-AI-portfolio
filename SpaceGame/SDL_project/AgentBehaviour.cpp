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



	bool ThereisPathtobed = false;
	bool AgentisTired = false;
	bool ThereisPathtoToilet = false;
	bool AgentNeedsToilet = false;
	//only run if agent needs something
	if (agent.getToietNeed() > 0.2 || agent.getTiredness() > 0.5 && agent.isMoving == false)
	{
		// Level has bed and agent is tired
		if (levelHasBed && !AgentisTired)
		{
			AgentisTired = true;
			// Find path to bed
			agent.pathfinder.findPath(level, agent.getAgentPointLocation(), emptyBedLocations[0]);
			if (agent.path.size() > 0)
			{
				ThereisPathtobed = true;
			}
		}

		// Level has toilet and agent needs it
		else if (LevelHasToilet && !AgentNeedsToilet)
		{
			//Find path to toilet
			agent.pathfinder.findPath(level, agent.getAgentPointLocation(), emptyToiletLocations[0]);
			if (agent.path.size() > 0)
			{
				ThereisPathtoToilet = true;
			}
		}


		BehaviourTree agentServicesBehaviourTree;

		// A list of leaf nodes
		//BED ACTIONS
		Action isAgentTired(agentServicesBehaviourTree, "bed", AgentisTired), PathToBed(agentServicesBehaviourTree, "bed", ThereisPathtobed);

		//WC ACTIONS
		Action WalkToToilet(agentServicesBehaviourTree, "wc", LevelHasToilet), PathToToilet(agentServicesBehaviourTree, "wc", ThereisPathtoToilet);




		//Create 1 selector
		BehaviourTree::Selector selector[1];
		// Create 2 selectors
		BehaviourTree::Sequence sequence[2];

		// Set root node & add a selector that has 2 sequences 
		agentServicesBehaviourTree.setRootChild(&selector[0]);
		selector[0].addChildren({ &sequence[0], &sequence[1] });

		sequence[0].addChildren({ &isAgentTired, &PathToBed });
		sequence[1].addChildren({ &WalkToToilet, &PathToToilet });

		//if the behaviour tree runs then move the agent
		if (agentServicesBehaviourTree.run())
		{
			// Bed Tree
			if (sequence[0].run())
			{
				//Move to BED
				if (agent.isMoving == false)
				{
					agent.isMoving = true;
					agent.Move(level, agent.getAgentPointLocation(), emptyBedLocations[0]);
				}
			}

			// WC Tree
			else if (sequence[1].run())
			{
				//Move to WC
				if (agent.isMoving == false)
				{
					agent.isMoving = true;
					agent.Move(level, agent.getAgentPointLocation(), emptyToiletLocations[0]);
				}
			}
		}
	}
}

void AgentBehaviour::UpdateLevelInfo(Level& level, int cellX, int cellY)
{
	if (level.grid[cellX][cellY]->isBed)
	{
		levelHasBed = true;
		emptyBedLocations.push_back(Point(cellX, cellY));
	}
	if (level.grid[cellX][cellY]->isToilet)
	{
		LevelHasToilet = true;
		emptyToiletLocations.push_back(Point(cellX, cellY));
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

