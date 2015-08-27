#pragma once

#include <iostream>
#include "GameObjectFactory.h"
#include "Actor.h"

class AnimatedGraphic : public Actor
{
public:

	AnimatedGraphic();
	~AnimatedGraphic();

	virtual void load(std::unique_ptr<LoaderParams> const &pParams);
	virtual void draw();
	virtual void update(double delta);
	virtual void clean();

private:

	// animation speed
	int m_animSpeed;
	int m_frameCount;
};


//AnimatedGraphic creator class
class AnimatedGraphicCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new AnimatedGraphic();
	}

};