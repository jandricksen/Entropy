#pragma once

//This class is a layer of tiles

#include <vector>
#include "Layer.h"
#include "Vector2D.h"
#include "Level.h"

class TileLayer : public Layer
{
public:

	TileLayer(int tileSize, int mapWidth, int mapHeight, const std::vector<Tileset> &tilesets);

	virtual ~TileLayer() {}

	virtual void update(Level* pLevel, double delta);
	virtual void render();

	void setTileIDs(const std::vector<std::vector<int>>& data)
	{
		m_tileIDs = data;
	}

	void setTileSize(int tileSize)
	{
		m_tileSize = tileSize;
	}

	void setMapSize(int mapWidth, int mapHeight) { m_mapWidth = mapWidth, m_mapHeight = mapHeight; }
	int getMapWidth() { return m_mapWidth; }
	int getMapHeight() { return m_mapWidth; }

	int getTileSize() { return m_tileSize; }

	Tileset getTilesetByID(int tileID);

	const std::vector<std::vector<int>>& getTileIDs() { return m_tileIDs; };
	const Vector2D getPosition() { return m_position; }

private:

	int m_numColumns;
	int m_numRows;
	int m_tileSize;

	int m_mapWidth;
	int m_mapHeight;

	Vector2D m_position;
	Vector2D m_velocity;

	const std::vector<Tileset> &m_tilesets;
	std::vector<std::vector<int>> m_tileIDs;

};

