#pragma once

//Texture Manager Class
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>


class TextureManager
{
public:

	// instantiate texture class
	static TextureManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new TextureManager();
			return s_pInstance;
		}

		return s_pInstance;
	}

	// load texture
	bool load(std::string filename, std::string id, SDL_Renderer* pRenderer);

	// clear whole texture map
	void clearTextureMap();
	// release specific texture
	void clearFromTextureMap(std::string id) { m_textureMap.erase(id); };

	// draw
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, int alpha, int angle, SDL_RendererFlip flip);

	// stretch and draw
	void drawStretch(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, int angle, SDL_RendererFlip flip);

	// draw the frame
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// draw a Tile
	void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer);

	std::map<std::string, SDL_Texture*> getTextureMap() { return m_textureMap; }


private:
	TextureManager() {};

	TextureManager(const TextureManager&);
	TextureManager& operator=(const TextureManager&);

	static TextureManager* s_pInstance;

	std::map<std::string, SDL_Texture*> m_textureMap;
};


// typedef
typedef TextureManager TheTextureManager;