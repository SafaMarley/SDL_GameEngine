#include "../../game/Game.h"
#include "main.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{

	const int frameDelay = 1000 / Main::FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init("SomehowGameEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Main::windowW, Main::windowH, Main::fullscreen);

	while (game->isRunning)
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}
