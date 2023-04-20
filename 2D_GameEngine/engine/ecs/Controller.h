#pragma once
#include "../../game/Game.h"
#include "ECS.h"
#include "Components.h"

class Controller : public Component
{
public:
	TransformComponent *transform;
	SpriteComponent *sprite;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
			case SDLK_UP:
				transform->velocity.y = -1;
				sprite->Play("Walk");
				break;
			case SDLK_a:
			case SDLK_LEFT:
				transform->velocity.x = -1;
				sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_s:
			case SDLK_DOWN:
				transform->velocity.y = 1;
				sprite->Play("Walk");
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				transform->velocity.x = 1;
				sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			default:
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
			case SDLK_UP:
			case SDLK_s:
			case SDLK_DOWN:
				transform->velocity.y = 0;
				if (transform->velocity.x == 0)
				{
					sprite->Play("Idle");
				}
				break;
			case SDLK_a:
			case SDLK_LEFT:
			case SDLK_d:
			case SDLK_RIGHT:
				transform->velocity.x = 0;
				if (transform->velocity.y == 0)
				{
					sprite->Play("Idle");
				}
				break;

			case SDLK_ESCAPE:
				Game::isRunning = false;
			default:
				break;
			}
		}
	}
};
