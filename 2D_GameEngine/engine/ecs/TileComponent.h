#pragma once
#include "ECS.h"
#include "SDL.h"


class TileComponent : public Component
{
public:
	SDL_Texture *texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;

	TileComponent() = default;

	TileComponent(int srcX, int srcY, int srcW, int srcH, int xPos, int yPos, const char* path)
	{
		texture = TextureManager::LoadTexture(path);

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcW;
		srcRect.h = srcH;

		destRect.x = xPos;
		destRect.y = yPos;
		destRect.w = 64;
		destRect.h = 64;
	}

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};
