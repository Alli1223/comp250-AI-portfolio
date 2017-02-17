#include "stdafx.h"
#include "Character.h"


Character::Character() : characterTex("Resources\\crew2.png"), characterLeft("Resources\\Character\\crewLeft.png"), characterRight("Resources\\Character\\crewRight.png"), characterUp("Resources\\Character\\crewUp.png"), characterDown("Resources\\Character\\crewDown.png"),
npcLeft("Resources\\Character\\npcLeft.png"), npcRight("Resources\\Character\\npcRight.png"), npcUp("Resources\\Character\\npcUp.png"), npcDown("Resources\\Character\\npcDown.png")
{
}


Character::~Character()
{

}

void Character::MoveCharacter(Level& level, Point& StartPoint, Point& EndPoint, Agent& AgentToMove)
{

}

void Character::SpawnAgent(std::string CharacterTypeVar, std::vector<Agent>& allAgents, int x, int y)
{
		Agent newAgent;
		newAgent.setX(x);
		newAgent.setY(y);
		newAgent.characterType = CharacterTypeVar;
		newAgent.movementDirection = "Down";
		allAgents.push_back(newAgent);
}

void Character::RenderAgents(std::vector<Agent>& allAgents, SDL_Renderer* renderer, Level& level)
{
	for each (auto agent in allAgents)
	{
		agent.Update();
		if (agent.characterType == "NPC")
		{
			//npcDown.alterTextureColour(rand() % 200, 0,0);
			if (agent.movementDirection == "Up")
				npcUp.render(renderer, agent.getX() , agent.getY() , agent.getSize(), agent.getSize());
			if (agent.movementDirection == "Right")
				npcRight.render(renderer, agent.getX(), agent.getY(), agent.getSize(), agent.getSize());
			if (agent.movementDirection == "Down")
				npcDown.render(renderer, agent.getX(), agent.getY(), agent.getSize(), agent.getSize());
			if (agent.movementDirection == "Left")
				npcLeft.render(renderer, agent.getX(), agent.getY(), agent.getSize(), agent.getSize());
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