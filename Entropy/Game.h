#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "GameStateMachine.h"
#include "DeltaTimer.h"

class Level;

class Game
{
public:
	static Game* Instance()
	{
		// if no game instance then create new one and return it
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}

		// else return pntr to current game instance
		return s_pInstance;
	}

	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();
	void quit();

	SDL_Renderer* getRenderer() const { return m_pRenderer; };
	SDL_Window* getWindow() const { return m_pWindow; }
	GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

	void setCurrentLevel(int currentLevel);
	const int getCurrentLevel() { return m_currentLevel; }

	Level* getTheCurrentLevel() { return m_theCurrentLevel; }

	void setLevelComplete(bool levelComplete) { m_bLevelComplete = levelComplete; }
	const bool getLevelComplete() { return m_bLevelComplete; }

	void setNextLevel(int nextLevel) { m_nextLevel = nextLevel; }
	const int getNextLevel() { return m_nextLevel; }

	void setPlayerLives(int numLives) { m_playerLives = numLives; }
	const int getPlayerLives() { return m_playerLives; }

	bool isRunning() { return m_bRunning; };

	const double getDelta() { return delta; }

	bool changingState() { return m_bChangingState; }
	void changingState(bool cs) { m_bChangingState = cs; }

	int getWindowHeight() { return m_windowHeight;  };
	int getWindowWidth() { return m_windowWidth; };
	float getScrollSpeed() { return m_scrollSpeed; }

	std::vector<std::string> getLevelFiles() { return m_levelFiles; }

private:

	Game();
	~Game();

	Game(const Game&);
	Game& operator=(const Game&);

	// Singleton
	static Game* s_pInstance;

	// Game Running bool
	bool m_bRunning = false;

	// Window and Renderer
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	// Game states
	GameStateMachine* m_pGameStateMachine;
	bool m_bChangingState;

	// Timer
	DeltaTimer Timer;
	double delta;

	// Game variables
	const char* m_gameTitle;
	int m_gameXpos;
	int m_gameYpos;

	int m_windowHeight;
	int m_windowWidth;

	float m_scrollSpeed;

	// Level files
	std::vector<std::string> m_levelFiles;

	// Level variables
	int m_playerLives;
	int m_nextLevel;
	int m_currentLevel;
	Level* m_theCurrentLevel;
	bool m_bLevelComplete;

};

typedef Game TheGame;