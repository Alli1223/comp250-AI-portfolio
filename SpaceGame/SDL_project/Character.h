#pragma once
#include"Level.h"
#include "Point.h"
#include "PathFinder.h"
#include "Texture.h"
#include "Point.h"
#include "Agent.h"


//!  The abstract character class 
/*!
  This class is the controller for the Agent class and will manage how the agents behave.
*/
class Character
{
public:
	//! A constructor
	Character();
	//! A destructor
	~Character();

	void Character::RenderAgents(std::vector<Agent>& allAgents, SDL_Renderer* renderer, Level& level);

	//! Spawn character function (Character types are (NPC, Player)
	void Character::SpawnAgent(std::string CharacterTypeVar, std::vector<Agent>& allAgents, int x, int y);

	//! Move the character
	void Character::MoveCharacter(Level& level, Point& StartPoint, Point& EndPoint, Agent& AgentToMove);
		

	//! Movement Direction
	std::string movementDirection = "Down";

	//! Character Type
	std::string characterType = "NPC";

	//! CHARACTER PATHFINDING

	//! Conains the list of nodes that makes the path
	std::vector<Point> path;




	//! Gets and Sets the characters hunger
	double getHunger() { return Hunger; }
	double setHunger(int newHunger) { return Hunger = newHunger; }

	
	//! A double for the character's health
	double health = 100;
	//! A double for the character's stored oxygen
	double charactersOxygenReserves = 100;
	//! Boolean for whether character is alive
	bool isAlive = true; 

private:

	//! start point and end point for pathfinding
	Point startPoint, endPoint;

	//! Integers for the character's X and Y position
	int x = 0; int y = 0;
	//! Integer for the character's size when rendered
	int size = 25;
	//! Integer for the characters current speed
	int speed = 3;
	//! Double to store character hunger
	double Hunger = 100;
	//! Integer to store character tiredness
	int Tiredness = 0;


	//! For the Character
	Texture characterTex;
	//! Is the textures for the default character
	Texture characterLeft;
	Texture characterRight;
	Texture characterUp;
	Texture characterDown;

	//! Are the textures for the NPC
	Texture npcLeft;
	Texture npcRight;
	Texture npcUp;
	Texture npcDown;
};

