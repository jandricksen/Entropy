#pragma once
#include <string>
#include <vector>


// Abstract Base Class for Game States
class GameState
{
public:

	virtual void update(double delta) = 0;
	virtual void render() = 0;

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual std::string getStateID() const = 0;

protected:

	GameState() : m_loadingComplete(false), m_exiting(false)
	{
	}

	std::vector<std::string> m_textureIDList;
	bool m_loadingComplete;
	bool m_exiting;
};