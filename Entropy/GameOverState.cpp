#include "GameOverState.h"

#include <iostream>

#include "MainMenuState.h"
#include "StateParser.h"
#include "Game.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "MenuButton.h"
#include "InputHandler.h"


// Set static ID for Game Over State
const std::string GameOverState::s_gameOverID = "GAMEOVER";

// Load state
bool GameOverState::onEnter()
{
	//parse the state
	StateParser stateParser;
	stateParser.parseState("assets/test.xml", s_gameOverID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0); //push back 0 callbackID start from 1
	m_callbacks.push_back(s_gameOverToMain);
	m_callbacks.push_back(s_restartPlay);

	//set the callbacks for menu items
	setCallbacks(m_callbacks);

	m_loadingComplete = true;

	return true;
}


// Change the current state to Main Menu
void GameOverState::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}



// Restart the Play state
void GameOverState::s_restartPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
	// go through the game objects
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		// if they are of type MenuButton then assign a callback based on the id passed from the file
		if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallBackID()]);
		}
	}
}

void GameOverState::update(double delta)
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
	{
		s_restartPlay();
	}
	if (!m_gameObjects.empty())
	{
		for (size_t i = 0; i < m_gameObjects.size(); ++i)
		{
			if (m_gameObjects[i] != 0)
			{
				m_gameObjects[i]->update(delta);
			}
		}
	}
}

void GameOverState::render()
{
	if (m_loadingComplete && !m_gameObjects.empty())
	{
		for (size_t i = 0; i < m_gameObjects.size(); i++)
		{
			m_gameObjects[i]->draw();
		}
	}
}


// Exit the state
bool GameOverState::onExit()
{
	m_exiting = true;

	if (m_loadingComplete && !m_gameObjects.empty())
	{
		for (int i = 0; i < m_gameObjects.size(); i++)
		{
			m_gameObjects[i]->clean();
		}
	}

	m_gameObjects.clear();

	// clear texture manager
	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}


	// Reset input handler
	TheInputHandler::Instance()->reset();

	std::cout << "Exiting GameOver State\n";
	return true;
}