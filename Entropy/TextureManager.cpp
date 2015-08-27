#include "TextureManager.h"
#include <iostream>

TextureManager* TextureManager::s_pInstance = 0; 

bool TextureManager::load(std::string filename, std::string id, SDL_Renderer* pRenderer)
{

	std::string fileLocation = "assets/";
	fileLocation.append(filename);

	SDL_Surface* pTempSurface = IMG_Load(fileLocation.c_str());

	if (pTempSurface == 0)
	{
		std::cout << IMG_GetError();
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	// everything went ok, add the texture to our list
	if (pTexture != 0)
	{
		m_textureMap[id] = pTexture;
		return true;
	}

	// if you get here then something went wrong :(
	return false;
}

// draw
void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, int alpha, int angle, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	// set the alpha of the texture
	SDL_SetTextureAlphaMod(m_textureMap[id], alpha);

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}


// draw and stretch
void TextureManager::drawStretch(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, int angle, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

// drawframe
void TextureManager::drawFrame(
	std::string id, 
	int x, 
	int y, 
	int width, 
	int height, 
	int currentRow, 
	int currentFrame, 
	SDL_Renderer* pRenderer, 
	double angle,
	int alpha,
	SDL_RendererFlip flip
	)
{

	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	// set the alpha of the texture
	SDL_SetTextureAlphaMod(m_textureMap[id], alpha);

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, NULL, flip);
}

//draw a tile
void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = margin + (spacing + width) * currentFrame;
	srcRect.y = margin + (spacing + height) * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::clearTextureMap()
{
	m_textureMap.clear();
}