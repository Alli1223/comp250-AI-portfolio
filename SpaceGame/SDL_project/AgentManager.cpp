#include "stdafx.h"
#include "AgentManager.h"


AgentManager::AgentManager() : characterTex(characterTextureLocation + "crew2.png"), characterLeft(characterTextureLocation + "crewLeft.png"), characterRight(characterTextureLocation + "crewRight.png"), characterUp(characterTextureLocation + "crewUp.png"), characterDown(characterTextureLocation + "crewDown.png"),
npcLeft(characterTextureLocation + "npcLeft.png"), npcRight(characterTextureLocation + "npcRight.png"), npcUp(characterTextureLocation + "npcUp.png"), npcDown(characterTextureLocation + "npcDown.png"),
healthBarTexture(playerStatsTextureLocation + "PlayerHealth.png"), oxygenBarTexture(playerStatsTextureLocation + "PlayerOxygen.png"), hungerBarTexture(playerStatsTextureLocation + "PlayerHunger.png"), tiredBarTexture(playerStatsTextureLocation + "PlayerTiredness.png")
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



void AgentManager::UpdateAgents(std::vector<Agent>& allAgents, SDL_Renderer* renderer, Level& level)
{
	for (Agent& agent : allAgents)
	{
		RenderAgents(agent, renderer, level);
		agentBehaviour.DecideTask(level, agent);
	}
}

void AgentManager::RenderAgents(Agent& agent, SDL_Renderer* renderer, Level& level)
{

	int x = agent.getX() + (agent.getSize() / 2);
	int y = agent.getY() + (agent.getSize() / 2);
	if (agent.characterType == "NPC" && agent.isAlive)
	{
		//npcDown.alterTextureColour(200, 100,100);
		if (agent.movementDirection == "Up")
			npcUp.render(renderer, x, y, agent.getSize(), agent.getSize());
		if (agent.movementDirection == "Right")
			npcRight.render(renderer, x, y, agent.getSize(), agent.getSize());
		if (agent.movementDirection == "Down")
			npcDown.render(renderer, x, y, agent.getSize(), agent.getSize());
		if (agent.movementDirection == "Left")
			npcLeft.render(renderer, x, y, agent.getSize(), agent.getSize());

		//Render agent stats to the right of agent
		if (agent.getHealth() < 100)
			healthBarTexture.render(renderer, x + agent.getSize() - agent.getSize() / 10, y, agent.getSize() / 10, agent.getHealth() / 2);
		if (agent.getOxygenLevel() < 100)
			oxygenBarTexture.render(renderer, x + agent.getSize(), y, agent.getSize() / 10, agent.getOxygenLevel() * 30.0);
		if (agent.getHunger() < 100)
			hungerBarTexture.render(renderer, x + agent.getSize() + agent.getSize() / 10, y, agent.getSize() / 10, agent.getHunger() * 30.0);
		if (agent.getTiredness() > 0)
			tiredBarTexture.render(renderer, x + ((agent.getSize() + agent.getSize()) * 2) / 10, y, agent.getSize() / 10, agent.getTiredness() / 2);

	}
	if (agent.characterType == "Player" && agent.isAlive)
	{
		if (agent.movementDirection == "Up")
			characterUp.render(renderer, x, y, agent.getSize(), agent.getSize());
		if (agent.movementDirection == "Right")
			characterRight.render(renderer, x, y, agent.getSize(), agent.getSize());
		if (agent.movementDirection == "Down")
			characterDown.render(renderer, x, y, agent.getSize(), agent.getSize());
		if (agent.movementDirection == "Left")
			characterLeft.render(renderer, x, y, agent.getSize(), agent.getSize());
	}

}