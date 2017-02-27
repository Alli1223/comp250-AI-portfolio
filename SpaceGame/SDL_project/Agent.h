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
	//! Movement method for Agent
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

	//!* CHARACTER PATHFINDING */
	//! Create an instance of pathfinder
	Pathfinder pathfinder;
	//! Conains the list of nodes that makes the path
	std::vector<Point> path;

	//! Contains what the current status of the agent is doing
	/*! Types of agent state: (Idle, FoundPath, Dead)*/
	std::string agentStatus = "Idle";

	//! Gets and Sets the agents health
	double getHealth() { return health; }
	double setHealth(double newHealth) { return health = newHealth; }

	//! Gets and Sets the agents hunger
	double getHunger() { return hunger; }
	double setHunger(double newHunger) { return hunger = newHunger; }

	//! Gets and Sets the agents tiredness
	double getTiredness() { return tiredness; }
	double setTiredness(double newTiredness) { return tiredness = newTiredness; }

	//! Gets and Sets the agents oxygen level
	double getOxygenLevel() { return oxygenLevel; }
	double setOxygenLevel(double newOxygenLevel) { return oxygenLevel = newOxygenLevel; }

	//! Boolean for whether character is alive
	bool isAlive = true;

private:

	//! Integers for the character's X and Y position
	int x = 0; int y = 0;
	//! Integer for the character's size when rendered
	int size = 25;
	//! Integer for the characters current speed
	int speed = 1;
	//! A double for the agents's health
	double health = 100.0;
	//! Double to store character hunger
	double hunger = 1.0;
	//! Integer to store character tiredness
	double tiredness = 0.0;
	//! A int for the agents's stored oxygen
	double oxygenLevel = 3.0;

	//! A double for storing agents health decay rate
	double healthDecayRate = 0.1;
	//! A double for storing agents hunger decay rate
	double hungerDecayRate = 0.001;
	//! A double for storing agents tiredness decay rate
	double tirednessDecayRate = 0.001;
	//! A double for storing agents oxygen decay rate
	double oxygenDecayRate = 0.1;

	//! Stores where the agent is along the path
	int pathPointIterator = 0;
};

