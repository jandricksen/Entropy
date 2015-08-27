#pragma once
#include <string>

class LoaderParams
{
public:
	LoaderParams(int x, int y, int width, int height, std::string textureID, int numFrames, int callbackID = 0, int animSpeed = 0);
	~LoaderParams();

	// getters
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	int getNumFrames() const;
	int getCallbackID() const;
	int getAnimSpeed() const;
	std::string getTextureID() const;

private:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	int m_numFrames;
	int m_callbackID;
	int m_animSpeed;

	std::string m_texture;
};

