#include "stdafx.h"
#include "SpaceGame.h"
#include "InitialisationError.h"

SpaceGame::SpaceGame() : backgroundTexture("Resources\\background5.jpg")
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw InitialisationError("SDL_Init failed");
	}
	gameSettings.getScreenResolution();
	WINDOW_HEIGHT = gameSettings.WINDOW_HEIGHT;
	WINDOW_WIDTH = gameSettings.WINDOW_WIDTH;
	window = SDL_CreateWindow("SpaceGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
	
	if (window == nullptr)
	{
		throw InitialisationError("SDL_CreateWindow failed");
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		throw InitialisationError("SDL_CreateRenderer failed");
	}
	
}

SpaceGame::~SpaceGame()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}



void SpaceGame::run()
{
	// Level generation
	level.makeGrid(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Choose whether to generate or load a map
	//mapLoader.LoadMap("Resources\\Map\\Default_map.txt", level);
	//mapLoader.generateMap(level, designroom);


	running = true;
	unsigned int timer = 0;
	int cellSize = level.getCellSize();

	while (running)
	{
		// Handle events
		SDL_Event ev;
		if (SDL_PollEvent(&ev))
		{
			const Uint8 *state = SDL_GetKeyboardState(NULL);
			switch (ev.type)
			{
			case SDL_QUIT:
				running = false;
				break;

			default:
				break;
			}
			if (state[SDL_SCANCODE_ESCAPE] && menu == false)
			{
				menu = true;

			}
			else if (state[SDL_SCANCODE_ESCAPE] && menu == true)
			{
				menu = false;
			}
			else if (state[SDL_SCANCODE_0])
			{
				agentManager.EraseAllAgents(agentManager.allAgents);
			}
			else if (state[SDL_SCANCODE_9])
			{
				agentManager.EraseAllAgentPaths(agentManager.allAgents);
			}

		}//End pollevent if

		// Checks the keyboard for input
		const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

		// Rendering process:
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Renders the background image
		backgroundTexture.render(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT);


		/* Opens the door when a player goes through
		//characterInteraction.Interaction(room, characterOne, oxygen);

		//ship management
		shipmanager.shiptimer(room, allships);
		//ship rendering
		shipmanager.rendership(allships, renderer);
		*/
		
		if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_RIGHT))
		{

			if (level.grid[mouse_X / cellSize][mouse_Y / cellSize]->isRoom)
				agentManager.SpawnAgent("NPC", agentManager.allAgents, mouse_X, mouse_Y);
		}
		

		
		

		//////////////////////////////////
		//MAIN LOOP
		///////////////////////////////////
		
		for (int x = 0; x < level.grid.size(); x++)
		{
			for (int y = 0; y < level.grid[x].size(); y++)
			{
				//Renders all he cells
				cellrenderer.RenderCells(level, renderer, x, y);

				
				agentManager.agentBehaviour.UpdateLevelInfo(level, x, y);
				
				/* Fill the screen with room cells
				if (x > 0 && y > 0 && x < room.getLevelWidth() - 1 && y < room.getLevelHeight() - 1 )
				{
					room.grid[x][y]->isRoom = true;
					//designroom.designRoom(room, x, y);
				}
				*/

				// Object Updates
				//Spawns fire randomly in rooms over time
				//fire.spawn(room, x, y);
				//fire.fireSpread(room, x, y);

				// Runs Oxygen spread function
				//oxygen.update(level, x, y);

				
				//hydroponics.update(level, allHydroponicsFarms, x, y);

			} //End for Y loop
		}//End for X loop

		 // Render the vector of hydroponics
		hydroponics.renderItems(renderer, level, allHydroponicsFarms);

		// Render characters
		agentManager.UpdateAgents(agentManager.allAgents, renderer, level);

		// TOOLBAR
		toolbar.ToolBarFunctionality(level, designroom, dockingdoors, hydroponics, allHydroponicsFarms, renderer, mouse_X, mouse_Y);
		toolbar.RenderToolbar(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, mouse_X, mouse_Y);


		// All agents move to mouse position
		if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_MIDDLE) )
		{
			for (int i = 0; i < agentManager.allAgents.size(); i++)
			{
				agentManager.allAgents[i].path.erase(agentManager.allAgents[i].path.begin(), agentManager.allAgents[i].path.end());
				Point StartPoint(agentManager.allAgents[i].getX() / cellSize, agentManager.allAgents[i].getY() / cellSize);
				Point EndPoint(mouse_X / cellSize, mouse_Y / cellSize);

				agentManager.allAgents[i].Move(level, StartPoint, EndPoint);
			}
		}
		
		// UPDATE ALL AGENTS POSITION
		for (int i = 0; i < agentManager.allAgents.size(); i++)
		{
			agentManager.allAgents[i].Update(level);


			// DRAW THE PATH FOR ALL AGENTS (VERY RESOURCE INTENSIVE)
			for (int it = 0; it < agentManager.allAgents[i].path.size(); it++)
			{
				drawPath(agentManager.allAgents[i].path[i], level, agentManager.allAgents[i].path);
			}
			
		}
		
		
		

		///////////////////////////////////////
		//MENU
		//////////////////////////////////////

		if (menu)
		{
			escapemenu.RunEscapeMenu(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, mouse_X, mouse_Y, running);
			if (escapemenu.exit)
			{
				running = false;
			}
			if (escapemenu.restart)
			{
				deleteVectors();
				SpaceGame::run();
			}
		}
		SDL_RenderPresent(renderer);
	}
}// End while running


void SpaceGame::deleteVectors()
{
	allHydroponicsFarms.erase(allHydroponicsFarms.begin(), allHydroponicsFarms.end());
}

void SpaceGame::drawPath(Point& point, Level& level, std::vector<Point>& path)
{
	// Start at the start point

	// tileSize / 2 is added to all coordinates to put them in the centre of the tile
	int lastX = point.getX() * (level.getCellSize() + level.getCellSize() / 2);
	int lastY = point.getY() * (level.getCellSize() + level.getCellSize() / 2);


	// Step through the path
	for (const Point& point : path)
	{
		int nextX = point.getX() * level.getCellSize() + level.getCellSize() / 2;
		int nextY = point.getY() * level.getCellSize() + level.getCellSize() / 2;

		SDL_RenderDrawLine(renderer, lastX, lastY, nextX, nextY);
		lastX = nextX;
		lastY = nextY;

	}
}

bool static isMouseOverRoomCell(Level& level)
{
	int mouse_X, mouse_Y;
	SDL_GetMouseState(&mouse_X, &mouse_Y);
	if (level.grid[mouse_X / level.getCellSize()][mouse_Y / level.getCellSize()]->isRoom)
	{
		return true;
	}
	else
	{
		return false;
	}
}