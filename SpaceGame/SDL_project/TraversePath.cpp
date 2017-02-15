#include "stdafx.h"
#include "TraversePath.h"

TraversePath::TraversePath()
{
}


TraversePath::~TraversePath()
{
}

// Moves the player across the cell to the next cell
void TraversePath::Move(Agent& agent, Point& point)
{
	//if the x axis is the same as before, move vertically
	if (point.getX() == previousNode.getX())
	{
		int pointY = point.getY() * cellSize;
		//move down
		if (agent.getY() < pointY)
		{
			agent.setY(agent.getY() + 1);
			agent.movementDirection = "Down";
		}
		//move up
		if (agent.getY() > pointY)
		{
			agent.setY(agent.getY() - 1);
			agent.movementDirection = "Up";
		}
		else if (agent.getY() == pointY)
			IterateToNextNode(agent, point);
	}

	// If the Y axis is the same as before move horizontally 
	if (point.getY() == previousNode.getY())
	{
		int pointX = point.getX() * cellSize;
		//move right
		if (agent.getX() < pointX)
		{
			agent.setX(agent.getX() + 1);
			agent.movementDirection = "Right";
		}
		//move left
		if (agent.getX() > pointX)
		{
			agent.setX(agent.getX() - 1);
			agent.movementDirection = "Left";
		}

		else if (agent.getX() == pointX && agent.getY() == point.getY())
			IterateToNextNode(agent, point);
	}

	//set the previous point to the current one
	previousNode = point;
}
void TraversePath::VerticalMovement(Agent& agent, Point point)
{
	
}

void TraversePath::HorizontalMovement(Agent& characterOne, Point point)
{

}
void TraversePath::IterateToNextNode(Agent& agent, Point point)
{
	int pointX = point.getX() * cellSize;
	int pointY = point.getY() * cellSize;
	if (agent.getX() == pointX && agent.getY() == pointY)
	{
		pathPointIterator++;
	}
}

Point TraversePath::getNextPoint(std::vector<Point> path)
{
	if (pathPointIterator < path.size())
		return path[pathPointIterator];

	// Completed
	else
		pathPointIterator = 0;
		path.erase(path.begin(), path.end());
		pathComplete = false;
}