#include "PlayState.h"

#include <iostream>

#include "LevelParser.h"
#include "PlayState.h"
#include "GameOverState.h"
#include "PauseState.h"
#include "Game.h"
#include "InputHandler.h"
#include "LevelParser.h"
#include "Level.h"


// Set static ID for Play State
const std::string PlayState::s_playID = "PLAY";

PlayState::PlayState()
{
}

bool PlayState::onEnter()
{
	LevelParser levelParser;
	//Parse Map File and return into pLevel
	pLevel = levelParser.parseLevel("assets/map1.tmx");

	if (pLevel != 0)
	{
		m_loadingComplete = true;
	}

	std::cout << "Entering Play State" << std::endl;
	return true;
}


void PlayState::update(double delta)
{

	if (m_loadingComplete && !m_exiting)
	{
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
		{
			TheGame::Instance()->getStateMachine()->pushState(new PauseState());
		}

		if (pLevel != 0)
		{
			pLevel->update(delta);
		}
	}
}
void PlayState::render()
{
	if (m_loadingComplete)
	{

		// render level
		if (pLevel != 0)
		{
			pLevel->render();
		}

	}
}

bool PlayState::onExit()
{
	m_exiting = true;

	// clear texture manager
	for (size_t i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}


	// Reset input handler
	TheInputHandler::Instance()->reset();

	std::cout << "Exiting Play State\n";
	return true;
}