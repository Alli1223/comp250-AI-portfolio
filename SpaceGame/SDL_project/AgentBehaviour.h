#pragma once
#include "BehaviourTree.h"
#include "Agent.h"
class AgentBehaviour
{
public:
	AgentBehaviour();
	~AgentBehaviour();



	Sequence *root = new Sequence, *sequence1 = new Sequence;
	Selector* selector1 = new Selector;


	bool levelHasBed = false;
	int bedNum = 0;

	bool LevelHasToilet = false;
	int toiletNum = 0;


	int localSearchSize = 2;
	//! Finds the nearest cell to the agent from the string cellType (e.g. "BED" || "TOILET")
	Point AgentBehaviour::FindNearestCelltoAgent(Agent& agent, Level& level, std::string cellType);

	//! To Decide what task needs to be done
	void AgentBehaviour::DecideTask(Level& level, Agent& agent);

	void AgentBehaviour::UpdateLevelInfo(Level& level, int cellX, int cellY);

private:
	double tirednessThreshold = 0.4;
	double toiletThreshold = 0.2;
	double hungerThreshold = 0.2;
};
