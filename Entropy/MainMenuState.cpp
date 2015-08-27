#include "MainMenuState.h"

#include <iostream>
#include "StateParser.h"
#include "Game.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "MenuButton.h"

// Set static ID for Menu State
const std::string MainMenuState::s_menuID = "MENU";


bool MainMenuState::onEnter()
{

	//parse the state
	StateParser stateParser;
	stateParser.parseState("assets/test.xml", s_menuID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0); //push back 0 callbackID start from 1
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);

	//set the callbacks for menu items
	setCallbacks(m_callbacks);

	m_loadingComplete = true;
	std::cout << "entering Menu State\n";

	return true;

}

void MainMenuState::update(double delta)
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
	{
		s_menuToPlay();
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
void MainMenuState::render()
{
	if (m_loadingComplete && !m_gameObjects.empty())
	{
		for (size_t i = 0; i < m_gameObjects.size(); ++i)
		{
			m_gameObjects[i]->draw();
		}
	}
}

void MainMenuState::s_menuToPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
	TheGame::Instance()->quit();
}


void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{ 
	// go through the game objects
	for (size_t i = 0; i < m_gameObjects.size(); ++i)
	{
		// if they are of type MenuButton then assign a callback based on the id passed from the file
		if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallBackID()]);
		}
	}
}

bool MainMenuState::onExit()
{
	m_exiting = true;

	if (m_loadingComplete && !m_gameObjects.empty())
	{
		for (size_t i = 0; i < m_gameObjects.size(); ++i)
		{
			m_gameObjects[i]->clean();
		}

		m_gameObjects.pop_back();
	}

	m_gameObjects.clear();


	// Reset input handler
	TheInputHandler::Instance()->reset();

	std::cout << "Exiting Menu State\n";
	return true;
}
