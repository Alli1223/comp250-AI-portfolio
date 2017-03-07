#include "stdafx.h"
#include "Texture.h"
#include "InitialisationError.h"

/*
Texture class that manages the rendering of textures in the game
*/
Texture::Texture(const std::string& fileName)
	: fileName(fileName), texture(nullptr)
{
}


Texture::~Texture()
{
	if (texture)
		SDL_DestroyTexture(texture);
}

void Texture::render(SDL_Renderer* renderer, int x, int y, int width, int height)
{
	if (!texture)
	{
		texture = IMG_LoadTexture(renderer, fileName.c_str());


		if (!texture)
		{
			throw InitialisationError("IMG_LoadTexture failed");
		}
	}

	SDL_Rect dest;
	dest.x = x - width / 2;
	dest.y = y - height / 2;
	dest.w = width;
	dest.h = height;
	
	SDL_RenderCopy(renderer, texture, nullptr, &dest);
}
void Texture::renderRotation(SDL_Renderer* renderer, int x, int y, int width, int height, int angle)
{
	if (!texture)
	{
		texture = IMG_LoadTexture(renderer, fileName.c_str());


		if (!texture)
		{
			throw InitialisationError("IMG_LoadTexture failed");
		}
	}

	SDL_Rect dest;
	dest.x = x - width / 2;
	dest.y = y - height / 2;
	dest.w = width;
	dest.h = height;
	SDL_Point *center;
	center->x = x - width / 2;
	center->y = y - height / 2;
	SDL_RendererFlip flip;

	SDL_RenderCopyEx(renderer, texture, nullptr, &dest, angle, center, flip );
}

void Texture::alterTransparency(int transparencyLevel)
{
	SDL_SetTextureAlphaMod(texture, transparencyLevel);
}

void Texture::alterTextureColour(int r, int g, int b)
{
	SDL_SetTextureColorMod(texture, r, g, b);
}

int SDL_RenderCopyEx(SDL_Renderer*       renderer,
	SDL_Texture*           texture,
	const SDL_Rect*        srcrect,
	const SDL_Rect*        dstrect,
	const double           angle,
	const SDL_Point*       center,
	const SDL_RendererFlip flip)