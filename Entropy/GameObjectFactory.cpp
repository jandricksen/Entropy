#include "GameObjectFactory.h"

/*
Class Description:

*Singleton*

This Class stores Object ID's with thier matching Object Creators, so they can be created from the Level File if ID is recognised.

Methods:

@registerType - registers type id's for game objects and stores them with a reference to their creator
@create - matches object id's passed in from the level parser to registered id's and if found creates the object
*/


// Init Singleton
GameObjectFactory* GameObjectFactory::s_pInstance = 0;

///registers type id's for game objects and stores them with a reference to their creator
bool GameObjectFactory::registerType(std::string typeID, BaseCreator* pCreator)
{
	std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

	//if the type already registered then do nothing
	if (it != m_creators.end())
	{
		delete pCreator;
		return false;
	}

	m_creators[typeID] = pCreator;

	return true;
}


///matches object id's passed in from the level parser to registered id's and if found creates the object
GameObject* GameObjectFactory::create(std::string typeID)
{
	std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

	if (it == m_creators.end())
	{
		std::cout << "could not find type: " << typeID << "\n";
		return NULL;
	}

	BaseCreator* pCreator = it->second;
	return pCreator->createGameObject();
}