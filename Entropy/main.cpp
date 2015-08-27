// Side-Kick Prototype Engine v0.01 - 16/02/15


#ifdef _WIN32 //This checks to see if windows compilation
#define _CRT_SECURE_NO_DEPRECATE // if windows then define a ignore vs2013 compiler deprecation decleration. Otherwise compiler won't allow for freopen() 
#endif

#include "Game.h"
#include <Windows.h>
#include <iostream>

const int WINDOW_WIDTH = 640;
const int WIDOW_HEIGHT = 480;

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

Game* g_game = 0; // global game pointer for engine


int main(int argc, char* argv[])
{
	//REMOVE FOR RELEASE // START *
		AllocConsole(); // this allows for console and std::cout
		freopen("CON", "w", stdout); // this allows for console and std::cout - deprecated in vs2013
	//REMOVE FOR RELEASE // END *
	
	// two unsigned ints to handle frames
	Uint32 frameStart, frameTime;

	// instantiate game engine
	if (TheGame::Instance()->init(
			"Entropy",												//DEFAULT WINDOW NAME
			SDL_WINDOWPOS_CENTERED,									//DEFAULT WINDOW X_POS
			SDL_WINDOWPOS_CENTERED,									//DEFAULT WINDOW Y_POS
			WINDOW_WIDTH,											//DEFAULT WINDOW WIDTH
			WIDOW_HEIGHT,											//DEFAULT WINDOW HEIGHT
			false													//DEFAULT WINDOW FULLSCREEN Y/N
		))
	{
		while (TheGame::Instance()->isRunning())
		{
			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();
		}
	}
	else
	{
		// failed init print error
		std::cout << SDL_GetError();
		return -1;
	}


	// clean on finish
	TheGame::Instance()->clean();

	return 0;
}