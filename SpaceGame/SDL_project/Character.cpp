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
	for (int i = 0; i < allAgents.size(); i++)
	{
		allAgents[i].Update();
		if (allAgents[i].characterType == "NPC")
		{
			//npcDown.alterTextureColour(rand() % 200, 0,0);
			if (allAgents[i].movementDirection == "Up")
				npcUp.render(renderer, allAgents[i].getX() , allAgents[i].getY() , allAgents[i].getSize(), allAgents[i].getSize());
			if (allAgents[i].movementDirection == "Right")
				npcRight.render(renderer, allAgents[i].getX(), allAgents[i].getY(), allAgents[i].getSize(), allAgents[i].getSize());
			if (allAgents[i].movementDirection == "Down")
				npcDown.render(renderer, allAgents[i].getX(), allAgents[i].getY(), allAgents[i].getSize(), allAgents[i].getSize());
			if (allAgents[i].movementDirection == "Left")
				npcLeft.render(renderer, allAgents[i].getX(), allAgents[i].getY(), allAgents[i].getSize(), allAgents[i].getSize());
		}
		if (allAgents[i].characterType == "Player")
		{
			if (allAgents[i].movementDirection == "Up")
				characterUp.render(renderer, allAgents[i].getX(), allAgents[i].getY(), allAgents[i].getSize(), allAgents[i].getSize());
			if (allAgents[i].movementDirection == "Right")
				characterRight.render(renderer, allAgents[i].getX(), allAgents[i].getY(), allAgents[i].getSize(), allAgents[i].getSize());
			if (allAgents[i].movementDirection == "Down")
				characterDown.render(renderer, allAgents[i].getX(), allAgents[i].getY(), allAgents[i].getSize(), allAgents[i].getSize());
			if (allAgents[i].movementDirection == "Left")
				characterLeft.render(renderer, allAgents[i].getX() , allAgents[i].getY(), allAgents[i].getSize(), allAgents[i].getSize());
		}		
	}
}