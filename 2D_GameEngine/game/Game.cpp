#include "Game.h"
#include "../engine/src/TextureManager.h"
#include "../engine/src/Map.h"
#include "../engine/ecs/Components.h"
#include "../engine/ecs/Vector2D.h"
#include "../engine/ecs/Collision.h"
#include "../main.h"

const int mapW = 25;
const int mapH = 20;

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;

SDL_Event Game::event;

SDL_Rect Game::camera = { 0, 0, Main::windowW, Main::windowH };

std::vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

auto& player(manager.addEntity());
//auto& wall(manager.addEntity());

const char *mapFile = "assets/mapTileset.png";

enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

Game::Game()
{
	
}

Game::~Game()
{

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen)
{
	int flags = 0;

	if (fullScreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialized!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!..." << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!..." << std::endl;
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	map = new Map();
	Map::LoadMap("assets/level_1.map", mapW, mapH);

	player.addComponent<TransformComponent>();
	player.addComponent<SpriteComponent>("assets/mageAnimSet.png", true);
	player.addComponent<Controller>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	/*
	wall.addComponent<TransformComponent>(300, 300, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/water.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);
	*/
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();

	camera.x = player.getComponent<TransformComponent>().position.x - Main::windowW / 2;
	camera.y = player.getComponent<TransformComponent>().position.y - Main::windowH / 2;

	maintainCamera();
}

void Game::maintainCamera()
{
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > camera.w)
	{
		camera.x = camera.w;
	}
	if (camera.y > camera.h)
	{
		camera.y = camera.h;
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	
	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& e : enemies)
	{
		e->draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleansed!" << std::endl;
}

void Game::AddTile(int srcX, int srcY, int srcW, int srcH, int xPos, int yPos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, srcW, srcH, xPos, yPos, mapFile);
	tile.addGroup(groupMap);
}