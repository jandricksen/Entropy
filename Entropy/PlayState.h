#pragma once
#include "GameState.h"

class Level;
class GameObject;
class Actor;

class PlayState : public GameState
{
public:

	PlayState();
	~PlayState() { delete pLevel; };

	virtual void update(double delta);
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_playID; };

	bool checkCollision(Actor* p1, Actor* p2);

	Level* getCurrentLevel() { return pLevel; }

private:

	//The Level 
	Level* pLevel;

	//State ID
	static const std::string s_playID;
};

