#include "stdafx.h"
#include "AgentManager.h"


AgentManager::AgentManager() : characterTex("Resources\\crew2.png"), characterLeft("Resources\\Character\\crewLeft.png"), characterRight("Resources\\Character\\crewRight.png"), characterUp("Resources\\Character\\crewUp.png"), characterDown("Resources\\Character\\crewDown.png"),
npcLeft("Resources\\Character\\npcLeft.png"), npcRight("Resources\\Character\\npcRight.png"), npcUp("Resources\\Character\\npcUp.png"), npcDown("Resources\\Character\\npcDown.png")
{
}


AgentManager::~AgentManager()
{

}

void AgentManager::SpawnAgent(std::string CharacterTypeVar, std::vector<Agent>& allAgents, int x, int y)
{
		Agent newAgent;
		newAgent.setX(x);
		newAgent.setY(y);
		newAgent.characterType = CharacterTypeVar;
		newAgent.movementDirection = "Down";
		allAgents.push_back(newAgent);
}

void AgentManager::EraseAllAgentPaths(std::vector<Agent>& allAgents) 
{
	for (int i = 0; i < allAgents.size(); i++)
	{
		allAgents[i].path.erase(allAgents[i].path.begin(), allAgents[i].path.end());
		allAgents[i].agentStatus = "Idle";
	}
}

void AgentManager::EraseAllAgents(std::vector<Agent>& allAgents)
{
	allAgents.erase(allAgents.begin(), allAgents.end());
}

void AgentManager::RenderAgents(std::vector<Agent>& allAgents, SDL_Renderer* renderer, Level& level)
{
	for (Agent& agent : allAgents)
	{
		int x = agent.getX()  + (level.getCellSize() / 2);
		int y = agent.getY() + (level.getCellSize() / 2);
		if (agent.characterType == "NPC")
		{
			//npcDown.alterTextureColour(rand() % 200, 0,0);
			if (agent.movementDirection == "Up")
				npcUp.render(renderer, x, y , agent.getSize(), agent.getSize());
			if (agent.movementDirection == "Right")
				npcRight.render(renderer, x, y, agent.getSize(), agent.getSize());
			if (agent.movementDirection == "Down")
				npcDown.render(renderer, x, y, agent.getSize(), agent.getSize());
			if (agent.movementDirection == "Left")
				npcLeft.render(renderer, x, y, agent.getSize(), agent.getSize());
		}
		if (agent.characterType == "Player")
		{
			if (agent.movementDirection == "Up")
				characterUp.render(renderer, agent.getX(), agent.getY(), agent.getSize(), agent.getSize());
			if (agent.movementDirection == "Right")
				characterRight.render(renderer, agent.getX(), agent.getY(), agent.getSize(), agent.getSize());
			if (agent.movementDirection == "Down")
				characterDown.render(renderer, agent.getX(), agent.getY(), agent.getSize(), agent.getSize());
			if (agent.movementDirection == "Left")
				characterLeft.render(renderer, agent.getX() , agent.getY(), agent.getSize(), agent.getSize());
		}		
	}
}