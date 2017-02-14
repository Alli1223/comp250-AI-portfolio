#include "stdafx.h"
#include "Character.h"


Character::Character() : characterTex("Resources\\crew2.png"), characterLeft("Resources\\Character\\crewLeft.png"), characterRight("Resources\\Character\\crewRight.png"), characterUp("Resources\\Character\\crewUp.png"), characterDown("Resources\\Character\\crewDown.png"),
npcLeft("Resources\\Character\\npcLeft.png"), npcRight("Resources\\Character\\npcRight.png"), npcUp("Resources\\Character\\npcUp.png"), npcDown("Resources\\Character\\npcDown.png")
{
}


Character::~Character()
{
}

void Character::RenderCharacters(std::vector<Character>& allCharacters, SDL_Renderer* renderer, Level& level)
{
	for each (auto character in allCharacters)
	{
		if (character.characterType == "NPC")
		{
			if (character.movementDirection == "Down")
				npcDown.render(renderer, character.getX() * level.getCellSize() , character.getY() * level.getCellSize(), character.getSize(), character.getSize());
		}
	}
}