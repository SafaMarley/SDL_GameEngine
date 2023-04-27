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
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	}

	void update() override
	{
		if (tag != "terrain")
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
		}
	}
};
