#pragma once

#include <iostream>
#include <string>
#include <map>
#include "GameObject.h"


class BaseCreator
{
public:

	virtual GameObject* createGameObject() const = 0;
	virtual ~BaseCreator() {};

};


class GameObjectFactory
{
public:

	static GameObjectFactory* Instance()
	{
		// if no game instance create new one
		if (s_pInstance == 0)
		{
			s_pInstance = new GameObjectFactory();
			return s_pInstance;
		}

		// else return pntr to instance
		return s_pInstance;
	}

	~GameObjectFactory() { if (s_pInstance) { delete s_pInstance; }; };


	bool registerType(std::string typeID, BaseCreator* pCreator);
	GameObject* create(std::string typeID); // create new object

private:
	// Singleton game instance
	static GameObjectFactory* s_pInstance;

	std::map<std::string, BaseCreator*> m_creators;
};

typedef GameObjectFactory TheGameObjectFactory;