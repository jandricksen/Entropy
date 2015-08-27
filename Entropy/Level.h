#pragma once
#include <string>
#include <vector>
#include "LevelParser.h"
#include "Layer.h"
#include "Player.h"
#include "Projectile.h"

struct Tileset
{
	int firstGridID;
	int tileWidth;
	int tileHeight;
	int spacing;
	int margin;
	int width;
	int height;
	int numColumns;
	std::string name;
};


class Level
{
public:

	~Level();

	void update(double delta);
	void render();

	std::vector<Tileset>* getTilesets()
	{
		return &m_tilesets;
	}

	std::vector<Layer*>* getLayers()
	{
		return &m_layers;
	}
	std::vector<TileLayer*>* getCollisionLayers() 
	{ 
		return &m_collisionLayers; 
	}

	const std::vector<TileLayer*>& getCollidableLayers() 
	{ 
		return m_collisionLayers; 
	}

	void setMapSize(int width, int height) { m_mapWidth = width, m_mapHeight = height; }
	int getMapWidth() { return m_mapWidth; }
	int getMapHeight() { return m_mapHeight; }


	Player* getPlayer() { return m_pPlayer; }
	void setPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

	std::vector<Projectile*>* getProjectileObjects()
	{
		return &m_projectileObjects;
	}


private:

	friend class LevelParser;
	Level();

	std::vector<Tileset> m_tilesets;
	std::vector<Layer*> m_layers;
	std::vector<TileLayer*> m_collisionLayers;

	int m_mapWidth;
	int m_mapHeight;

	Player* m_pPlayer;

	std::vector<Projectile*> m_projectileObjects;

};

