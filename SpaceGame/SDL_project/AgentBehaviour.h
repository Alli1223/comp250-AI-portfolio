#pragma once
#include "BehaviourTree.h"
#include "Agent.h"
class AgentBehaviour
{
public:
	AgentBehaviour();
	~AgentBehaviour();

	struct {
		bool levelHasBed = false;
		int bedNum = 0; 

		bool LevelHasToilet = false;
		int toiletNum = 0;
	};


	int localSearchSize = 2;
	//! Finds the nearest cell to the agent from the string cellType (e.g. "BED" || "TOILET")
	Point AgentBehaviour::FindNearestCelltoAgent(Agent& agent, Level& level, std::string& cellType);

	//! To Decide what task needs to be done
	void AgentBehaviour::DecideTask();
};


class ApproachBedTask : BehaviourTreeNode
{
public:
	ApproachBedTask::ApproachBedTask(Agent& agent);

	

private:
	
};
