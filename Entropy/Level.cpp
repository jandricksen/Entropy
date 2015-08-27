#include "Level.h"
#include "TextureManager.h"
#include "Game.h"
#include "Layer.h"
#include "ObjectLayer.h"
#include "TileLayer.h"


Level::Level()
{
}


Level::~Level()
{
	for (std::vector<Layer*>::const_iterator it = m_layers.begin(); it != m_layers.end(); ++it)
	{
		delete *it;
	}

	m_layers.clear();
}

void Level::render()
{
	for (size_t i = 0; i < m_layers.size(); ++i)
	{
		m_layers[i]->render();
	}
}

void Level::update(double delta)
{
	for (size_t i = 0; i < m_layers.size(); ++i)
	{
		m_layers[i]->update(this, delta);
	}

	if (m_pPlayer->isFiring())
	{
		m_pPlayer->FireWeapon(&m_projectileObjects);
	}

}
