#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
#include "../src/TextureManager.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	SDL_Texture* texture;
	SDL_Rect srcR;
	SDL_Rect destR;

	TransformComponent *transform;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	ColliderComponent(std::string t, int xPos, int yPos, int width, int height)
	{
		tag = t;
		collider.x = xPos;
		collider.y = yPos;
		collider.w = width;
		collider.h = height;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		texture = TextureManager::LoadTexture("assets/collider.png");
		srcR = { 0, 0, 64, 64 };
		destR = { collider.x, collider.y, collider.w, collider.h };


	}

	void update() override
	{
		if (tag != "terrain")
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}
	
		destR.x = collider.x - Game::camera.x;
		destR.y = collider.y - Game::camera.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcR, destR, SDL_FLIP_NONE);
	}
};
