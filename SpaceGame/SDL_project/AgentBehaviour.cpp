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
	//BehaviourTree::Sequence *root = new BehaviourTree::Sequence, *sequence1 = new BehaviourTree::Sequence;
	//BehaviourTree::Selector* selector1 = new BehaviourTree::Selector;
	//Action action("BED", 1);

	{
		BehaviourTree agentNeedsBehaviourTree;
		Action WalkToBed("WalkToBed", levelHasBed), AgentIsTired("AgentIsTired", true);

		Action WalkToToilet("WalkToToilet", LevelHasToilet), AgentNeedsToilet("AgentNeedsToilet", true);



		//Create 1 selector & 1 sequence
		BehaviourTree::Selector selector[1];
		BehaviourTree::Sequence sequence[1];

		agentNeedsBehaviourTree.setRootChild(&selector[0]);
		selector[0].addChildren({ &WalkToBed, &sequence[0] });
		sequence[0].addChildren({ &WalkToToilet, &AgentNeedsToilet });

		Point startPoint(agent.getAgentPointLocation());
		if (agentNeedsBehaviourTree.run())
		{
			if (agent.isMoving == false)
			{
				agent.isMoving = true;
				agent.Move(level, startPoint, emptyBedLocations[0]);
				
			}
		}
	}







	/*
	BehaviourTree::Selector selector[3];
	BehaviourTree::Sequence sequence[4];
	Action walkToDoor("Walk to door", 99), openDoor1("Open door", 15), unlockDoor("Unlock door", 25), openDoor2("Open door after unlocking it", 99), smashDoor("Smash door", 60),
		walkThroughDoor("Walk through door", 60), closeDoor("Close door", 100), walkToWindow("Walk to Window", 99), openWindow1("Open window", 70), unlockWindow("Unlock window", 65),
		openWindow2("Open window after unlocking it", 85), smashWindow("Smash window", 95), climbThroughWindow("Climb through window", 85), closeWindow("Close window", 100);

	behaviorTree.setRootChild(&selector[0]);
	selector[0].addChildren({ &sequence[0],&sequence[2] });
	sequence[0].addChildren({ &walkToDoor, &selector[1], &walkThroughDoor, &closeDoor });
	selector[1].addChildren({ &openDoor1, &sequence[1], &smashDoor });
	sequence[1].addChildren({ &unlockDoor, &openDoor2 });
	sequence[2].addChildren({ &walkToWindow, &selector[2], &climbThroughWindow, &closeWindow });
	const std::list<BehaviourTree::Node*> nodes = { &openWindow1, &sequence[3], &smashWindow };
	selector[2].addChildren(nodes);
	sequence[3].addChildren({ &unlockWindow, &openWindow2 });
	*/

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

