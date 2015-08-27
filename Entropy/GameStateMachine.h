#pragma once
#include <vector>
#include "GameState.h"


class GameStateMachine
{
public:

	GameStateMachine();
	~GameStateMachine();

	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();
	GameState* getCurrentState();

	void update(double delta);
	void render();

	void clean();

private:
	std::vector<GameState*> m_gameStates;
};

