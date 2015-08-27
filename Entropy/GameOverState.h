#pragma once
#include "MenuState.h"
#include "GameObject.h"

class GameOverState : public MenuState
{
public:

	GameOverState();
	~GameOverState();

	virtual void update(double delta);
	virtual void render();
	 
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_gameOverID; };

private:

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	static void s_gameOverToMain();
	static void s_restartPlay();

	static const std::string s_gameOverID;
	std::vector<GameObject*> m_gameObjects;
};

