#pragma once

#include "Texture.h"
#include "Level.h"
#include "Map.h"
#include "Point.h"
#include "SDL2_image-2.0.1\include\SDL_image.h"
#include "Cell.h"
#include "MainCharacter.h"
#include "IdleState.h"
#include "Oxygen.h"
#include "Fire.h"
#include "RoomDesign.h"
#include "PlayerInteraction.h"
#include "PathFinder.h"
#include "TraversePath.h"
#include "ObjectiveManager.h"
#include "GameSettings.h"
#include "GUI.h"
#include "ToolBar.h"
#include "Items.h"
#include "Hydroponics.h"
#include "EscapeMenu.h"
#include "DockingDoors.h"
#include "ShipManager.h"
#include "PlayerStats.h"
#include "CellRendering.h"
#include "Agent.h"

//! The main class
/*!
This is the main class where the game is laoded and run. 
*/
class SpaceGame
{
public:
	//! A constructor
	SpaceGame();
	//! A deconstructor
	~SpaceGame();

	
	const Point& getStartPoint() const { return startPoint; }
	int getStartX() const { return startPoint.getX(); }
	int getStartY() const { return startPoint.getY(); }

	//! Main Run loop
	void run();

	//! Removes all the data from stored vectors
	void SpaceGame::deleteVectors();

	//! Initalising all classes needed for game
	GameSettings gameSettings;
	Oxygen oxygen;
	Fire fire;
	PlayerInteraction characterInteraction;
	Character characters;
	Cell cell;
	TraversePath traversepath;
	ObjectiveManager objectivemanager;
	ToolBar toolbar;
	EscapeMenu escapemenu;
	DockingDoors dockingdoors;
	ShipManager shipmanager;
	PlayerStats playerstats;
	CellRendering cellrenderer;
	
	//! Pathfinding function
	void SpaceGame::drawPath(Point& point, Level& level, std::vector<Point>& path);

	//! Conains the list of nodes that makes the path
	//std::vector<Point> path;
	
	//! Contains a list of all the hydroponic farms
	std::vector<Hydroponics> allHydroponicsFarms;

	//! Contains a list of all the characters
	std::vector<Agent> allAgents;

	//! Contains a list of all the ship
	std::vector<Ship> allShips;


	//! The window width 
	int WINDOW_WIDTH = gameSettings.WINDOW_WIDTH;
	//! The window height
	int WINDOW_HEIGHT = gameSettings.WINDOW_HEIGHT;
	//! Coordinates of the mouse 
	int mouse_X, mouse_Y;

	//! Fog of War distance
	int fogOfWar = WINDOW_WIDTH;
private:

	//! start point and end point for pathfinding
	Point startPoint, endPoint;

	//! Pointer to the window that the game will be rendered in
	SDL_Window* window;
	//" Pointer to the renderer
	SDL_Renderer* renderer;

	Texture backgroundTexture;

	//! Whether the game is running or not
	bool running;
	bool menu;
};

