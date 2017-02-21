#include "stdafx.h"
#include "SpaceGame.h"
#include "InitialisationError.h"

SpaceGame::SpaceGame() : backgroundTexture("Resources\\background.png")
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
	room.makeGrid(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Choose whether to generate or load a map
	//mapLoader.LoadMap("Resources\\Map\\Default_map.txt", room);
	//mapLoader.generateMap(room, designroom);


	running = true;
	unsigned int timer = 0;
	int cellSize = room.getCellSize();

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
				agentManager.EraseAllAgents(allAgents);
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
		
		if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_RIGHT) )
		{
			agentManager.SpawnAgent("NPC", allAgents, mouse_X, mouse_Y);
		}
		

		
		

		//////////////////////////////////
		//MAIN LOOP
		///////////////////////////////////

		for (int x = 0; x < room.grid.size(); x++)
		{
			for (int y = 0; y < room.grid[x].size(); y++)
			{
				//Renders all he cells
				cellrenderer.RenderCells(room, renderer, x, y);

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
				//oxygen.update(room, x, y);

				//hydroponics Update
				//hydroponics->update(room, allHydroponicsFarms, x, y);

			} //End for Y loop
		}//End for X loop

		 // Render the vector of hydroponics
		hydroponics.renderItems(renderer, room, allHydroponicsFarms);

		// Render characters
		agentManager.RenderAgents(allAgents, renderer, room);

		



		// TOOLBAR
		toolbar.ToolBarFunctionality(room, designroom, dockingdoors, hydroponics, allHydroponicsFarms, renderer, mouse_X, mouse_Y);
		toolbar.RenderToolbar(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, mouse_X, mouse_Y);

		//playerstats.renderAndUpdatePlayerStats(renderer, characterOne, WINDOW_WIDTH, WINDOW_HEIGHT);


		if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_LEFT) && toolbar.getToolbarSelection() == 4)
		{
			
		}


		// All agents move to mouse position
		if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_MIDDLE) )
		{
			for (int i = 0; i < allAgents.size(); i++)
			{
				allAgents[i].path.erase(allAgents[i].path.begin(), allAgents[i].path.end());
				Point StartPoint(allAgents[i].getX() / cellSize, allAgents[i].getY() / cellSize);
				Point EndPoint(mouse_X / cellSize, mouse_Y / cellSize);

				allAgents[i].Move(room, StartPoint, EndPoint);
			}
		}

		// UPDATE ALL AGENTS POSITION
		for (int i = 0; i < allAgents.size(); i++)
		{
			allAgents[i].Update(room);
			/* DRAW THE PATH FOR ALL AGENTS (VERY RESOURCE INTENSIVE)
			for (int it = 0; it < allAgents[i].path.size(); it++)
			{
				drawPath(allAgents[i].path[it], room, allAgents[i].path);
			}
			*/
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
	allAgents.erase(allAgents.begin(), allAgents.end());
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