#pragma once
#include "Components.h"
#include "Vector2D.h"
#include "../../main.h"

class TransformComponent : public Component
{
public:
	Vector2D position;
	Vector2D velocity;

	int middleX = Main::windowW / 2;
	int middleY = Main::windowH / 2;

	int height = 64;
	int width = 64;
	int scale = 1;

	int speed = 2;

	TransformComponent()
	{
		//position.Zero();
		position.x = middleX;
		position.y = middleY;
	}

	TransformComponent(int s)
	{
		//position.Zero();
		position.x = middleX;
		position.y = middleY;
		scale = s;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, int s)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = s;
	}

	void init() override
	{
		velocity.Zero();
	}
	
	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};