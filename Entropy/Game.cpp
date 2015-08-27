#include "Game.h"
#include "GameObjectFactory.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "ScrollingBackground.h"
#include "Level.h"


// Init Singleton
Game* Game::s_pInstance = 0;

Game::Game():
m_pWindow(0),
m_pRenderer(0),
m_bRunning(false),
m_pGameStateMachine(0),
m_playerLives(3),
m_scrollSpeed(0.8),
m_bLevelComplete(false),
m_bChangingState(false)
{
	// add some level files to an array
	//m_levelFiles.push_back("assets/map1.tmx");
	//m_levelFiles.push_back("assets/map2.tmx");

	// start at this level
	m_currentLevel = 1;
};


Game::~Game() 
{
	// clean up to prevent memory leaks
	m_pRenderer = 0;
	m_pWindow = 0;
};

// Initilise SDL, Create a Window, Initilise Renderer
bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{

	// Set flags
	int flags = 0;

	m_windowHeight = height;
	m_windowWidth = width;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// Begin init
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		// if SDL init succeeded create our window 
		m_pWindow = SDL_CreateWindow(
			title,
			xpos,
			ypos,
			width,
			height,
			flags
			);

		// if the window creation succeeded create our renderer 
		if (m_pWindow != 0)
		{

			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

			// if renderer creation succeeded set draw color to black
			if (m_pRenderer != 0)
			{
				SDL_SetRenderDrawColor(
					m_pRenderer,
					0, //RED
					0, //GREEN
					0, //BLUE
					255 //ALPHA
					);

				SDL_RenderSetLogicalSize(m_pRenderer, m_windowWidth, m_windowHeight);
			}
			else
			{
				std::cout << "renderer init failed!" << std::endl;
				return false; // renderer init failed
			}
		}
		else
		{
			std::cout << "window init failed!" << std::endl;
			return false; // window init failed
		}

	}
	else
	{
		std::cout << "SDL failed to initilise" << std::endl;
		return false; // SDL could not initilise
	}


	// Set Init Game Vars
	m_gameTitle = title;
	m_gameXpos = xpos;
	m_gameYpos = ypos;

	// Init Input Handler Joysticks
	TheInputHandler::Instance()->initialiseJoysticks();

	// Register types with Game Object Factory
	TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
	TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator);
	TheGameObjectFactory::Instance()->registerType("Projectile", new ProjectileCreator);
	//TheGameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator);
	TheGameObjectFactory::Instance()->registerType("ScrollingBackground", new ScrollingBackgroundCreator());
	TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());

	// Init GameStateMachine and load first state
	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MainMenuState);


	// start main loop
	m_bRunning = true;

	return true;
}

// Set the Current Level
void Game::setCurrentLevel(int currentLevel)
{
	m_currentLevel = currentLevel;
	m_pGameStateMachine->changeState(new PlayState());
	m_theCurrentLevel = dynamic_cast<PlayState*>(m_pGameStateMachine->getCurrentState())->getCurrentLevel();
	m_bLevelComplete = false;
}

// Init Renderer
void Game::render()
{
	// clear the window to draw color
	SDL_RenderClear(m_pRenderer); // clear to draw colour

	// render current state
	m_pGameStateMachine->render();

	// draw to the screen
	SDL_RenderPresent(m_pRenderer);
}

// Input Event Handler
void Game::handleEvents()
{
	TheInputHandler::Instance()->update();
}


// Update Loop
void Game::update()
{
	delta = Timer.GetDelta() * 100;

	// update current state
	m_pGameStateMachine->update(delta);
}

// Clean Game
void Game::clean()
{
	TheInputHandler::Instance()->clean();

	m_pGameStateMachine->clean();

	m_pGameStateMachine = 0;
	delete m_pGameStateMachine;

	TheTextureManager::Instance()->clearTextureMap();

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::quit()
{
	m_bRunning = false;
}