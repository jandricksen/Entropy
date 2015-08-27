#include "LoaderParams.h"


LoaderParams::LoaderParams(int x, int y, int width, int height, std::string textureID, int numFrames, int callbackID, int animSpeed) : m_x(x), m_y(y), 
m_width(width), m_height(height), m_numFrames(numFrames), m_texture(textureID), m_animSpeed(animSpeed), m_callbackID(callbackID)
{

}


LoaderParams::~LoaderParams()
{
}

int LoaderParams::getX() const
{
	return m_x;
}

int LoaderParams::getY() const
{
	return m_y;
}

int LoaderParams::getWidth() const
{
	return m_width;
}

int LoaderParams::getHeight() const
{
	return m_height;
}

int LoaderParams::getNumFrames() const
{
	return m_numFrames;
}

int LoaderParams::getCallbackID() const
{
	return m_callbackID;
}

int LoaderParams::getAnimSpeed() const
{
	return m_animSpeed;
}

std::string LoaderParams::getTextureID() const
{
	return m_texture;
}

