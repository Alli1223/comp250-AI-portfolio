#pragma once
#include "Point.h"
#include "Level.h"
#include "Character.h"

class TraversePath
{
public:
	TraversePath();

	//! Choses which direction the player should move
	void TraversePath::Move(Agent& agent, Point& point);

	//! Gets the next node for the object to walk to
	void TraversePath::IterateToNextNode(Agent& agent, Point point);

	//! Returns the point of the next node in the path
	Point TraversePath::getNextPoint(std::vector<Point> path);

	//! Controls how he player moves vertiacally
	void TraversePath::VerticalMovement(Agent& agent, Point point);

	//! Controls how he player moves horizontally
	void TraversePath::HorizontalMovement(Agent& agent, Point point);

	//! contains a point of the previous node
	Point previousNode;

	//! Used for determineing what node the player is at in the path
	int pathPointIterator = 0;

	//! Using another instance of level instead
	Level level;

	//! Gets the cell size
	int cellSize = level.getCellSize();

	// Used for determineing if the path has finished
	bool pathComplete = false;

	~TraversePath();
	
};

