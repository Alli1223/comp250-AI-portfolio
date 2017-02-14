#include "stdafx.h"
#include "Character.h"


Character::Character() : characterTex("Resources\\crew2.png"), characterLeft("Resources\\Character\\crewLeft.png"), characterRight("Resources\\Character\\crewRight.png"), characterUp("Resources\\Character\\crewUp.png"), characterDown("Resources\\Character\\crewDown.png"),
npcLeft("Resources\\Character\\npcLeft.png"), npcRight("Resources\\Character\\npcRight.png"), npcUp("Resources\\Character\\npcUp.png"), npcDown("Resources\\Character\\npcDown.png")
{
}


Character::~Character()
{

}

void Character::SpawnCharacter(std::string CharacterTypeVar, std::vector<Character>& allCharacters, int x, int y)
{
	if (CharacterTypeVar == "NPC")
	{
		Character newChar;
		newChar.setX(x);
		newChar.setY(y);
		newChar.characterType = CharacterTypeVar;
		newChar.movementDirection = "Down";
		allCharacters.push_back(newChar);
	}

	if (CharacterTypeVar == "Player")
	{
		Character newChar;
		newChar.setX(x);
		newChar.setY(y);
		newChar.characterType = CharacterTypeVar;
		newChar.movementDirection = "Down";
		allCharacters.push_back(newChar);
	}
}

void Character::RenderCharacters(std::vector<Character>& allCharacters, SDL_Renderer* renderer, Level& level)
{
	for each (auto character in allCharacters)
	{
		int charX = character.getX() * level.getCellSize() + (level.getCellSize() / 2);
		int charY = character.getY() * level.getCellSize() + (level.getCellSize() / 2);

		if (character.characterType == "NPC")
		{
			if (character.movementDirection == "Up")
				npcUp.render(renderer, character.getX() * level.getCellSize() , character.getY() * level.getCellSize(), character.getSize(), character.getSize());
			if (character.movementDirection == "Right")
				npcRight.render(renderer, character.getX() * level.getCellSize(), character.getY() * level.getCellSize(), character.getSize(), character.getSize());
			if (character.movementDirection == "Down")
				npcDown.render(renderer, charX, charY, character.getSize(), character.getSize());
			if (character.movementDirection == "Left")
				npcLeft.render(renderer, character.getX() * level.getCellSize(), character.getY() * level.getCellSize(), character.getSize(), character.getSize());
		}
		if (character.characterType == "Player")
		{
			if (character.movementDirection == "Up")
				characterUp.render(renderer, character.getX() * level.getCellSize(), character.getY() * level.getCellSize(), character.getSize(), character.getSize());
			if (character.movementDirection == "Right")
				characterRight.render(renderer, character.getX() * level.getCellSize(), character.getY() * level.getCellSize(), character.getSize(), character.getSize());
			if (character.movementDirection == "Down")
				characterDown.render(renderer, character.getX() * level.getCellSize(), character.getY() * level.getCellSize(), character.getSize(), character.getSize());
			if (character.movementDirection == "Left")
				characterLeft.render(renderer, character.getX() * level.getCellSize(), character.getY() * level.getCellSize(), character.getSize(), character.getSize());
		}
	}
}