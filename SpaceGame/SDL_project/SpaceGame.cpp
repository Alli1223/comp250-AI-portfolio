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
	Level room;
	room.makeGrid(WINDOW_WIDTH, WINDOW_HEIGHT);
	Map mapLoader;
	RoomDesign designroom;

	// Choose whether to generate or load a map
	//mapLoader.LoadMap("Resources\\Map\\Default_map.txt", room);
	//mapLoader.generateMap(room, designroom);

	
	auto hydroponics = std::make_shared<Hydroponics>();


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

		if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			characters.SpawnCharacter("NPC", allCharacters, mouse_X / cellSize, mouse_Y / cellSize);
		}
		else if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_RIGHT))
		{
			characters.SpawnCharacter("Player", allCharacters, mouse_X / cellSize, mouse_Y / cellSize);
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

				// Fill the screen with room cells
				bool doOnce = false;
				if (x > 1 && y > 1 && x < room.getLevelWidth() - 2 && y < room.getLevelHeight() - 2 && doOnce == false)
				{
					room.grid[x][y]->isRoom = true;
					doOnce = true;
					designroom.designRoom(room, x, y);
				}

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
		hydroponics->renderItems(renderer, room, allHydroponicsFarms);

		// Render characters
		characters.RenderCharacters(allCharacters, renderer, room);
		

		// TOOLBAR
		toolbar.ToolBarFunctionality(room, designroom, renderer, mouse_X, mouse_Y);
		toolbar.RenderToolbar(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, mouse_X, mouse_Y);

		//playerstats.renderAndUpdatePlayerStats(renderer, characterOne, WINDOW_WIDTH, WINDOW_HEIGHT);


		if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_LEFT) && toolbar.getToolbarSelection() == 4)
		{
			if (room.grid[mouse_X / cellSize][mouse_Y / cellSize]->isRoom && toolbar.numberOfItem4 > 0)
			{
				hydroponics->spawnHydroponicBase(renderer, room, allHydroponicsFarms, mouse_X, mouse_Y);
				//toolbar.numberOfItem4--;
			}
		}

		if (toolbar.getToolbarSelection() == 5)
		{
			if (toolbar.numberOfItem4 > 0)
			{
				dockingdoors.placeDockingDoors(renderer, room);
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
				traversepath.pathComplete = false;
				traversepath.pathPointIterator = 0;
				SpaceGame::run();
			}
		}
		SDL_RenderPresent(renderer);
	}
}// End while running


void SpaceGame::deleteVectors()
{
	path.erase(path.begin(), path.end());
	allHydroponicsFarms.erase(allHydroponicsFarms.begin(), allHydroponicsFarms.end());
}

void SpaceGame::drawPath(Point& point, Level& level)
{
	// Start at the start point
	
	// tileSize / 2 is added to all coordinates to put them in the centre of the tile
	int lastX = point.getX() * (level.getCellSize() + level.getCellSize()  / 2);
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