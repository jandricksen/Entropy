#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include "Vector2D.h"

// define int values for mouse buttons
enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};


// Input Handler class
class InputHandler
{
public:
	static InputHandler* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new InputHandler();

			return s_pInstance;
		}

		return s_pInstance;
	}

	void update();
	void clean();

	// joystick/gamepad specific
	void initialiseJoysticks();
	bool joysticksInitalised() { return m_bJoysticksInitialised; };

	int xValue(int joy, int stick);
	int yValue(int joy, int stick);

	bool getButtonState(int joy, int buttonNumber) { return m_buttonStates[joy][buttonNumber]; };

	// mouse specific
	bool getMouseButtonState(int buttonNumber) { return m_mouseButtonStates[buttonNumber]; };
	Vector2D* getMousePosition() { return m_mousePosition; };

	// keyboard specific
	bool isKeyDown(SDL_Scancode key) const;

	// reset mouse button states
	void reset();


private:
	InputHandler();
	~InputHandler();

	// joystick/gamepad specific
	bool m_bJoysticksInitialised;

	std::vector<SDL_Joystick*> m_joysticks;
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
	std::vector<std::vector<bool>> m_buttonStates;

	const int m_joystickDeadZone = 20000;

	void onJoystickAxisMove(SDL_Event& event);
	void onJoystickButtonDown(SDL_Event& event);
	void onJoystickButtonUp(SDL_Event& event);

	// mouse specific
	std::vector<bool> m_mouseButtonStates;
	Vector2D* m_mousePosition;

	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

	// keyboard specific
	const Uint8* m_keystates;

	void onKeyUp();
	void onKeyDown();

	// singleton
	static InputHandler* s_pInstance;
};


typedef InputHandler TheInputHandler;