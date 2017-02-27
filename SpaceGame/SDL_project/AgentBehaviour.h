#pragma once
#include "Agent.h"
class AgentBehaviour : public Agent
{
public:
	AgentBehaviour();
	~AgentBehaviour();

	void AgentBehaviour::BehaviourTree(Agent& agent, Level& level);

	void AgentBehaviour::AgentMovement(Agent& agent, Level& level);
private:
	double hungerThreshold = 0.3;
	double tirednessThreshold = 0.3;
	double toiletThreshold = 0.3;
};

