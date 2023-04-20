#include "TextureManager.h"
#include <iostream>

SDL_Texture* TextureManager::LoadTexture(const char *texture)
{
	SDL_Surface* tempSurface = IMG_Load(texture);
	if (!tempSurface)
	{
		std::cout << "Error while loading " << texture << "!" << std::endl;
	}
	SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

void TextureManager::Draw(SDL_Texture * texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, texture, &src, &dest, NULL, NULL, flip);
}
