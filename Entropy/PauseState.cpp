#include "PauseState.h"

#include "Game.h"
#include "TextureManager.h"
#include "StateParser.h"
#include "MainMenuState.h"
#include "InputHandler.h"
#include "MenuButton.h"

const std::string PauseState::s_pauseID = "PAUSE";

PauseState::PauseState()
{
}


PauseState::~PauseState()
{
}


bool PauseState::onEnter()
{
	StateParser stateParser;

	stateParser.parseState("assets/test.xml", s_pauseID, &m_gameObjects, &m_textureIDList);

	//push back 0 callbackID so we start from 1. The order of push_back should match ID's
	m_callbacks.push_back(0);
	m_callbacks.push_back(s_resumePlay);
	m_callbacks.push_back(s_pauseToMain);
	//

	//set the callbacks for menu items
	setCallbacks(m_callbacks);

	std::cout << "Entering Pause State\n";

	m_loadingComplete = true;
	return true;
}

void PauseState::s_pauseToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay()
{
	TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::update(double delta)
{
	if (m_loadingComplete && !m_gameObjects.empty())
	{
		for (size_t i = 0; i < m_gameObjects.size(); ++i)
		{
			m_gameObjects[i]->update(delta);
		}
	}
}

void PauseState::render()
{
	if (m_loadingComplete && !m_gameObjects.empty())
	{
		for (size_t i = 0; i < m_gameObjects.size(); ++i)
		{
			m_gameObjects[i]->draw();
		}
	}
}


void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
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


bool PauseState::onExit()
{
	m_exiting = true;

	//saftey check that loading complete before unloading
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

	std::cout << "Exiting Pause State\n";
	return true;
}