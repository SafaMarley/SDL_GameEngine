#pragma once
#include "ECS.h"
#include "SDL.h"


class TileComponent : public Component
{
public:
	SDL_Texture *texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;
	Vector2D position;

	TileComponent() = default;

	TileComponent(int srcX, int srcY, int srcW, int srcH, int xPos, int yPos, const char* path, int scale = 1)
	{
		texture = TextureManager::LoadTexture(path);

		position.x = xPos;
		position.y = yPos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcW;
		srcRect.h = srcH;

		destRect.x = xPos;
		destRect.y = yPos;
		destRect.w = srcW * scale;
		destRect.h = srcH * scale;
	}

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void update() override
	{
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};
