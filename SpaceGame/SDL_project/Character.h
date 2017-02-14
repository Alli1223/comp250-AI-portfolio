#pragma once
#include"Level.h"

//!  The abstract character class 
/*!
  This class is the base for the main character and the NPC. It contains all the functions
  needed to make the character move and react to different states.
*/
class Character
{
public:
	//! A constructor
	Character();
	//! A destructor
	~Character();
		
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

	std::string movementDirection = "Down";


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
};

