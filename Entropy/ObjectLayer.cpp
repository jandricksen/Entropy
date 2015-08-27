#include "ObjectLayer.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Camera.h"
#include "Game.h"
#include "Level.h"

ObjectLayer::~ObjectLayer()
{
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		delete (*it);
	}
	m_gameObjects.clear();
}

void ObjectLayer::update(Level* pLevel, double delta)
{
	
	m_collisionManager.checkPlayerEnemyCollision(pLevel->getPlayer(), (const std::vector<GameObject*>&)m_gameObjects);


	// iterate through the objects
	if (!m_gameObjects.empty())
	{
		for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();)
		{
			//Everything Updating All the Time
			(*it)->setUpdating(true);
			(*it)->update(delta);
	
			//Check if off map If So Collision Removal
			if  (

				(*it)->getPosition().getX() < (-200 - (*it)->getWidth()) || 
				(*it)->getPosition().getX() > (pLevel->getMapWidth() + (*it)->getWidth()) || 
				(*it)->getPosition().getY() > pLevel->getMapHeight() ||
				(*it)->getPosition().getY() < -200
				
				)
			{
				std::cout << "Off map";
				(*it)->collision();
				++it; // increment if all ok
			}
			else
			{
				++it; // increment if all ok
			}

		}
	}

}

void ObjectLayer::render()
{
	for (size_t i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->draw();
	}
}