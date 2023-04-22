#pragma once
#include "SDL.h"
#include "../libs/SDL_image.h"
#include <iostream>
#include <vector>

class ColliderComponent;

class Game
{

private:
	SDL_Window *window;
	void maintainCamera();

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen);
	
	void handleEvents();
	void update();
	void render();
	void clean();

	static SDL_Renderer *renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;

	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders
	};
};

