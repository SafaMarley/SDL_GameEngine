#pragma once
#include "Components.h"
#include "SDL.h"
#include "../src/TextureManager.h"
#include "../src/Animation.h"
#include <map>


class SpriteComponent : public Component
{

private:
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:
	int animIndex = 0;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(const char *path)
	{
		setTexture(path);
	}

	SpriteComponent(const char *path, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 6, 200);
		Animation walk = Animation(1, 8, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		Play("Idle");
		
		setTexture(path);
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
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
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}
	
	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;

		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void Play(const char* animName)
	{
		animIndex = animations[animName].index;
		frames = animations[animName].frames;
		speed = animations[animName].speed;
	}
};
