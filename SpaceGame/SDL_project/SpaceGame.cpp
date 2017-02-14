#include "stdafx.h"
#include "SpaceGame.h"
#include "InitialisationError.h"

SpaceGame::SpaceGame()
	// Texture file locations
	: roomCell("Resources\\roomSprites\\texturePack\\center.png"), emptyCell("Resources\\roomSprites\\emptyCell.png"),
	topRoomCell("Resources\\roomSprites\\texturePack\\top.png"), topRightRoomCell("Resources\\roomSprites\\texturePack\\topRight.png"), rightRoomCell("Resources\\roomSprites\\texturePack\\right.png"), bottomRightRoomCell("Resources\\roomSprites\\texturePack\\bottomRight.png"), bottomRoomCell("Resources\\roomSprites\\texturePack\\bottom.png"), bottomLeftRoomCell("Resources\\roomSprites\\texturePack\\bottomLeft.png"), leftRoomCell("Resources\\roomSprites\\texturePack\\left.png"), topLeftRoomCell("Resources\\roomSprites\\texturePack\\topLeft.png"),
	cargoBayTexture("Resources\\roomSprites\\texturePack\\cargoBayStorage.png"), cargoTexture("Resources\\roomSprites\\crate1.png"),
	characterTex("Resources\\crew2.png"), characterLeft("Resources\\Character\\crewLeft.png"), characterRight("Resources\\Character\\crewRight.png"), characterUp("Resources\\Character\\crewUp.png"), characterDown("Resources\\Character\\crewDown.png"),
	npcLeft("Resources\\Character\\npcLeft.png"), npcRight("Resources\\Character\\npcRight.png"), npcUp("Resources\\Character\\npcUp.png"), npcDown("Resources\\Character\\npcDown.png"),
	NpcTex("Resources\\Character\\NPC.png"),
	openDoorTexture("Resources\\roomSprites\\texturePack\\center.png"),
	closedDoorTexture("Resources\\roomSprites\\texturePack\\door.png"),
	oxygenTex("Resources\\oxygen.png"),
	oxygenTank("Resources\\SpawnItems\\oxygenTank.png"), healthPack("Resources\\SpawnItems\\healthPack.png"),
	healthBar("Resources\\health.png"),
	healthText("Resources\\healthText.png"),
	winTexture("Resources\\oxygenBar.png"),
	winText("Resources\\you_win.png"),
	oxygenBar("Resources\\oxygenBar.png"),
	oxygenText("Resources\\oxygenText.png"),
	gameOver("Resources\\health.png"),
	gameOverText("Resources\\game_over.png"),
	fireTexture("Resources\\SpawnItems\\fire1.png"),
	backgroundTexture("Resources\\background.png"),
	hullBreachTexture("Resources\\roomSprites\\hullBreach2.png"),
	deathAnim("Resources\\deathAnim.png"),
	goalTexture("Resources\\roomSprites\\crate1.png"){
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

	//Oxygen oxygen;
	//Fire fire;
	//PlayerInteraction characterInteraction;
	MainCharacter characterOne;
	//NPC NpcOne;
	Cell cell;
	Pathfinder pathfinder;
	//Point point;
	TraversePath traversepath;
	ObjectiveManager objectivemanager;
	ToolBar toolbar;
	auto hydroponics = std::make_shared<Hydroponics>();
	EscapeMenu escapemenu;
	DockingDoors dockingdoors;
	ShipManager shipmanager;
	PlayerStats playerstats;


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

		for (int x = 0; x < room.grid.size(); x++)
		{
			for (int y = 0; y < room.grid[x].size(); y++)
			{
				int xPos = x * cellSize + cellSize / 2;
				int yPos = y * cellSize + cellSize / 2;

				/* Object Updates
				//Spawns fire randomly in rooms over time
				fire.spawn(room, x, y);
				fire.fireSpread(room, x, y);

				// Runs Oxygen spread function
				oxygen.update(room, x, y);

				//hydroponics Update
				hydroponics->update(room, allHydroponicsFarms, x, y);
				*/

				//RENDERING THE CELLS

					// Checks if the cell is a room
				if (room.grid[x][y]->isRoom)
				{
					oxygenTex.alterTransparency(room.grid[x][y]->oxygenLevel);
					roomCell.render(renderer, xPos, yPos, cellSize, cellSize);
					oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);

					// Removes oxyen from rooms
					if (room.grid[x][y]->getOxygenLevel() > 0 && room.grid[x][y]->getOxygenLevel() <= 100)
						room.grid[x][y]->setOxygenLevel(room.grid[x][y]->getOxygenLevel() - 0.5);
				}
				if (!room.grid[x][y]->isRoom)
				{
					room.grid[x][y]->setOxygenLevel(0);
					emptyCell.alterTransparency(0);
					emptyCell.render(renderer, xPos, yPos, cellSize, cellSize);
				}

				// Renders the top cell orientation
				if (room.grid[x][y]->cellOrientation == 0)
				{
					oxygenTex.alterTransparency(room.grid[x][y]->oxygenLevel / 2);
					topRoomCell.render(renderer, xPos, yPos, cellSize, cellSize);
					oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
				}
				if (room.grid[x][y]->cellOrientation == 1)
				{
					oxygenTex.alterTransparency(room.grid[x][y]->oxygenLevel / 2);
					topRightRoomCell.render(renderer, xPos, yPos, cellSize, cellSize);
					oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
				}
				if (room.grid[x][y]->cellOrientation == 2)
				{
					oxygenTex.alterTransparency(room.grid[x][y]->oxygenLevel / 2);
					rightRoomCell.render(renderer, xPos, yPos, cellSize, cellSize);
					oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
				}
				if (room.grid[x][y]->cellOrientation == 3)
				{
					oxygenTex.alterTransparency(room.grid[x][y]->oxygenLevel / 2);
					bottomRightRoomCell.render(renderer, xPos, yPos, cellSize, cellSize);
					oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
				}
				if (room.grid[x][y]->cellOrientation == 4)
				{
					oxygenTex.alterTransparency(room.grid[x][y]->oxygenLevel / 2);
					bottomRoomCell.render(renderer, xPos, yPos, cellSize, cellSize);
					oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
				}
				if (room.grid[x][y]->cellOrientation == 5)
				{
					oxygenTex.alterTransparency(room.grid[x][y]->oxygenLevel / 2);
					bottomLeftRoomCell.render(renderer, xPos, yPos, cellSize, cellSize);
					oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
				}
				if (room.grid[x][y]->cellOrientation == 6)
				{
					oxygenTex.alterTransparency(room.grid[x][y]->oxygenLevel / 2);
					leftRoomCell.render(renderer, xPos, yPos, cellSize, cellSize);
					oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
				}
				if (room.grid[x][y]->cellOrientation == 7)
				{
					oxygenTex.alterTransparency(room.grid[x][y]->oxygenLevel / 2);
					topLeftRoomCell.render(renderer, xPos, yPos, cellSize, cellSize);
					oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
				}
				if (room.grid[x][y]->cellOrientation == 8)
				{
					oxygenTex.alterTransparency(room.grid[x][y]->oxygenLevel / 2);
					roomCell.render(renderer, xPos, yPos, cellSize, cellSize);
					oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
				}
				if (room.grid[x][y]->cellOrientation == 10)
				{
					oxygenTex.alterTransparency(room.grid[x][y]->oxygenLevel);
					roomCell.render(renderer, xPos, yPos, cellSize, cellSize);
					oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
				}
				if (room.grid[x][y]->cellOrientation == 11)
				{
					room.grid[x][y]->setOxygenLevel(0);
					emptyCell.alterTransparency(0);
					emptyCell.render(renderer, xPos, yPos, cellSize, cellSize);
				}

				// Checks if the cell is a door
				if (room.grid[x][y]->isOpenDoor)
				{
					openDoorTexture.render(renderer, xPos, yPos, cellSize, cellSize);
				}

				// Checks if the cell is a door
				if (room.grid[x][y]->isDockingPath)
				{
					hullBreachTexture.render(renderer, xPos, yPos, cellSize, cellSize);
				}

				// Renders the fire cells
				if (room.grid[x][y]->isOnFire)
				{
					fireTexture.alterTransparency(150);
					fireTexture.render(renderer, xPos, yPos, cellSize, cellSize);
				}
				// Renders the hullBreach
				if (room.grid[x][y]->isHullBreach)
				{
					room.grid[x][y]->setOxygenLevel(0);
					hullBreachTexture.alterTransparency(150);
					hullBreachTexture.render(renderer, xPos, yPos, cellSize, cellSize);
				}
				// Renders the oxygen Tanks
				if (room.grid[x][y]->isOxygenTank)
				{
					oxygenTank.alterTransparency(200);
					oxygenTank.render(renderer, xPos, yPos, cellSize, cellSize);
				}
				if (room.grid[x][y]->isHealthPack)
				{
					healthPack.alterTransparency(200);
					healthPack.render(renderer, xPos, yPos, cellSize, cellSize);
				}
				// Renders open doors
				if (room.grid[x][y]->isOpenDoor)
				{
					room.grid[x][y]->setOxygenLevel(0);
					closedDoorTexture.render(renderer, xPos, yPos, cellSize, cellSize);
				}
				// Renders closed doors
				if (room.grid[x][y]->isClosedDoor)
				{
					oxygenTex.alterTransparency(room.grid[x][y]->oxygenLevel);
					openDoorTexture.render(renderer, xPos, yPos, cellSize, cellSize);
					oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
				}
				//Checks if the cell has the goal on it.
				if (room.grid[x][y]->isGoal)
				{
					oxygenTex.alterTransparency(room.grid[x][y]->oxygenLevel);
					roomCell.render(renderer, xPos, yPos, cellSize, cellSize);
					oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
					goalTexture.render(renderer, xPos, yPos, cellSize, cellSize);
				}
				if (room.grid[x][y]->isVerticalAirlock)
				{
					closedDoorTexture.render(renderer, xPos, yPos, cellSize, cellSize);
				}
				if (room.grid[x][y]->isAirlockWall)
				{
					goalTexture.render(renderer, xPos, yPos, cellSize, cellSize);
				}
				if (room.grid[x][y]->isShipCargoBay)
				{
					oxygenTex.alterTransparency(room.grid[x][y]->oxygenLevel);
					cargoBayTexture.render(renderer, xPos, yPos, cellSize, cellSize);
					oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
				}
				if (room.grid[x][y]->isCargo)
				{
					cargoTexture.render(renderer, xPos, yPos, cellSize, cellSize);
				}


				// Update hydroponics
				hydroponics->update(room, allHydroponicsFarms, x, y);

			} //End for Y loop
		}//End for X loop

		/*Renders the path
		SDL_SetRenderDrawColor(renderer, 255, 10, 128, 255);
		drawPath(point, room);
		*/


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
		// Render the vector of hydroponics
		hydroponics->renderItems(renderer, room, allHydroponicsFarms);
		
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