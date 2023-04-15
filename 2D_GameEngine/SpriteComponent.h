#pragma once
#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component
{

private:
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;

public:
	SpriteComponent() = default;

	SpriteComponent(const char *path)
	{
		setTexture(path);
	}

	void setTexture(const char *path)
	{
		texture = TextureManager::LoadTexture(path);
	}
	
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = 64;
		srcRect.h = 64;

		destRect.w = 64;
		destRect.h = 64;
	}
	
	void update() override
	{
		destRect.x = (int) transform->position.x;
		destRect.y = (int) transform->position.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}
};