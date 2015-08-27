#pragma once

#include <vector>
#include "Layer.h"
#include "CollisionManager.h"



class GameObject;

class ObjectLayer : public Layer
{
public:

	virtual ~ObjectLayer();

	// pass a level object through
	virtual void update(Level* pLevel, double delta);
	virtual void render();

	// return a pointer to this layers objects, the level parser will fill this
	std::vector<GameObject*>* getGameObject()
	{
		return &m_gameObjects;
	}

	virtual std::string type() { return "ObjectLayer"; };

private:

	// check for collisions between game objects
	CollisionManager m_collisionManager;

	// a list of game objects
	std::vector<GameObject*> m_gameObjects;
};