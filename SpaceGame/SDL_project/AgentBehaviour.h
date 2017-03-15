#pragma once
#include "BehaviourTree.h"
#include "Agent.h"

class AgentBehaviour
{
public:
	AgentBehaviour();
	~AgentBehaviour();

	//! Bool that stores whether the level has a bed
	bool levelHasBed = false;
	//! Bool that stores whether the level has a toilet
	bool LevelHasToilet = false;



	int localSearchSize = 2;
	//! Finds the nearest cell to the agent from the string cellType (e.g. "BED" || "TOILET")
	Point AgentBehaviour::FindNearestCelltoAgent(Agent& agent, Level& level, std::string cellType);

	//! To Decide what task needs to be done
	void AgentBehaviour::DecideTask(Level& level, Agent& agent);

	//! Updates some of the local class varaibles that store info about the level and what it contains for ease of use by behaviour tree
	void AgentBehaviour::UpdateLevelInfo(Level& level, int cellX, int cellY);

private:
	double tirednessThreshold = 0.4;
	double toiletThreshold = 0.2;
	double hungerThreshold = 0.2;


	class AgentActions : public BehaviourTree::Node
	{
		class WalkToBed : public BehaviourTree::Node
		{
		private:
			Agent& agent;
			Level& level;
		public:
			WalkToBed(Agent&, Level&);
		private:
			virtual bool run() override {

			}
			
		};
	};
};

