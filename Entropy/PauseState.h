#include "MenuState.h"

class GameObject;

class PauseState : public MenuState
{
public:

	PauseState();
	~PauseState();

	virtual void update(double delta);
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_pauseID; };

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:

	static void s_pauseToMain();
	static void s_resumePlay();

	static const std::string s_pauseID;

	std::vector<GameObject*> m_gameObjects;
};