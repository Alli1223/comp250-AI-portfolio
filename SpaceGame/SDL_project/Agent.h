#pragma once
#include "Point.h"
#include "PathFinder.h"

class Agent
{
public:
	Agent();
	~Agent();

	//! Update method for Agent
	void Agent::Update(Level& level);
	void Agent::Move(Level& level, Point& StartPoint, Point& EndPoint);


	//Getter methods
	//! Gets the characters X value
	int getX() { return x; }
	//! Gets the characters Y value
	int getY() { return y; }
	//! Gets the characters size
	int getSize() { return size; }
	//! Gets the characters speed
	int getSpeed() { return speed; }

	//Setter methods
	//! Sets the characters X value
	int setX(int newX) { return x = newX; }
	//! Sets the characters Y value
	int setY(int newY) { return y = newY; }
	//! Sets the characters current speed
	int setSpeed(int newSpeed) { return speed = newSpeed; }

	//! Movement Direction
	std::string movementDirection = "Down";

	//! Character Type
	std::string characterType = "NPC";

	//! CHARACTER PATHFINDING

	//! Create an instance of pathfinder
	Pathfinder pathfinder;

	//! Conains the list of nodes that makes the path
	std::vector<Point> path;

	//! Contains what the current status of the agent is doing
	/*! Types of agent state: (Idle, FoundPath, Dead)*/
	std::string agentStatus = "Idle";


	//! Gets and Sets the characters hunger
	double getHunger() { return Hunger; }
	double setHunger(int newHunger) { return Hunger = newHunger; }


	//! A double for the character's health
	double health = 100;
	//! A int for the character's stored oxygen
	int agentsOxygenReserves = 100;
	//! Boolean for whether character is alive
	bool isAlive = true;

private:

	//! Integers for the character's X and Y position
	int x = 0; int y = 0;
	//! Integer for the character's size when rendered
	int size = 25;
	//! Integer for the characters current speed
	int speed = 10;
	//! Double to store character hunger
	double Hunger = 100;
	//! Integer to store character tiredness
	int Tiredness = 0;

	int pathPointIterator = 0;
};

