#include "GameStateMachine.h"


GameStateMachine::GameStateMachine()
{
}


GameStateMachine::~GameStateMachine()
{
}

void GameStateMachine::pushState(GameState* pState)
{
	m_gameStates.push_back(pState);
	m_gameStates.back()->onEnter();
}

void GameStateMachine::changeState(GameState* pState)
{
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->getStateID() == pState->getStateID())
		{
			return; // do nothing
		}

		if (m_gameStates.back()->onExit())
		{
			m_gameStates.pop_back();
		}
	}

	// push back our new state
	m_gameStates.push_back(pState);

	// initilise it
	m_gameStates.back()->onEnter();
}

void GameStateMachine::popState()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->onExit();
		m_gameStates.pop_back();
	}
}

GameState* GameStateMachine::getCurrentState()
{
	if (!m_gameStates.empty())
	{
		return m_gameStates.back();
	}
}

void GameStateMachine::update(double delta)
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->update(delta);
	}
}

void GameStateMachine::render()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->render();
	}
}

void GameStateMachine::clean()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->onExit();

		delete m_gameStates.back();

		m_gameStates.clear();
	}
}