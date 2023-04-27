#include "Game.h"
#include "../engine/src/TextureManager.h"
#include "../engine/src/Map.h"
#include "../engine/ecs/Components.h"
#include "../engine/src/Vector2D.h"
#include "../engine/ecs/Collision.h"
#include "../main.h"

const int mapW = 25;
const int mapH = 20;

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;

SDL_Event Game::event;

SDL_Rect Game::camera = { 0, 0, Main::windowW, Main::windowH };

bool Game::isRunning = false;

auto& player(manager.addEntity());


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

	std::cout << "Initializing subsystems!... | ";
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized!" << std::endl;

		std::cout << "Creating a window!... | ";
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		std::cout << "Creating a renderer!... | ";
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	std::cout << "Loading map!... | ";
	map = new Map("assets/mapTileset.png");
	map->LoadMap("assets/level_1.map", mapW, mapH);
	std::cout << "Map loaded!" << std::endl;


	player.addComponent<TransformComponent>();
	player.addComponent<SpriteComponent>("assets/mageAnimSet.png", true);
	player.addComponent<Controller>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	std::cout << "Game is running!" << std::endl;
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& players(manager.getGroup(Game::groupPlayers));

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
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	manager.refresh();
	manager.update();

	for (auto& c : colliders)
	{
		SDL_Rect colliderRef = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(colliderRef, playerCol))
		{
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

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

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleansed!" << std::endl;
}
