#pragma once

#include "Actor.h"
#include "GameObjectFactory.h"


class MenuButton : public Actor
{
public:

	MenuButton();
	~MenuButton();

	virtual void load(std::unique_ptr<LoaderParams> const &pParams);
	virtual void draw();
	virtual void update(double delta);
	virtual void clean();

	void setCallback(void(*callback) ()) { m_callback = callback; };
	int getCallBackID() { return m_callbackID; };

private:

	// funtion pointer to handle button clicks
	int m_callbackID;
	void(*m_callback) ();

	// bool to handle button clicks
	bool m_bReleased;

	// enum of current mouse pos/button states
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

};


class MenuButtonCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new MenuButton();
	}
};

