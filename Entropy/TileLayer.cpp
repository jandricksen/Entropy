#include <iostream>
#include "TileLayer.h"
#include "Camera.h"
#include "Game.h"
#include "TextureManager.h"


TileLayer::TileLayer(int tileSize, int mapWidth, int mapHeight, const std::vector<Tileset> &tilesets) :
	m_tileSize(tileSize), 
	m_tilesets(tilesets), 
	m_position(0, 0), 
	m_velocity(0, 0)
{
	m_numColumns = mapWidth;
	m_numRows = mapHeight;

	m_mapWidth = mapWidth;
	m_mapHeight = mapHeight;


	std::cout << "m_tileSize : " << m_tileSize << "\n";
	std::cout << "Width : " << TheGame::Instance()->getWindowWidth() << "\n";
	std::cout << "Height : " << TheGame::Instance()->getWindowHeight() << "\n";
	std::cout << "m_Rows : " << m_numRows << "\n";
	std::cout << "m_Columns : " << m_numColumns << "\n";
}


void TileLayer::update(Level* pLevel, double delta)
{
}

void TileLayer::render()
{
	int x, y, x2, y2 = 0;

	x = m_position.getX() / m_tileSize; // Gives us the x tile to start drawing from e.g. If position is 100 and tile width is 32 then this equals 3. Therefore we draw from 3rd Tile
	y = m_position.getY() / m_tileSize; // This works the same way as above but for y axis

	x2 = int(m_position.getX()) % m_tileSize; // This ensures smooth scrolling by giving use the remaining amount of tile width after int calculation
	y2 = int(m_position.getY()) % m_tileSize; // This ensures smooth scrolling by giving use the remaining amount of tile width after int calculation

	for (int i = 0; i < m_numRows; i++)
	{
		for (int j = 0; j < m_numColumns; j++)
		{

			int id = m_tileIDs[i + y][j + x];

			if (id == 0)
			{
				continue;
			}

			// if outside viewable area then skip tile
			if (((j * m_tileSize) - x2) - TheCamera::Instance()->getPosition().m_x < -m_tileSize || 
				((j * m_tileSize) - x2) - TheCamera::Instance()->getPosition().m_x > TheGame::Instance()->getWindowWidth() || 
				(((i * m_tileSize) - y2) - TheCamera::Instance()->getPosition().m_y < -m_tileSize ||
				((i * m_tileSize) - y2) - TheCamera::Instance()->getPosition().m_y > TheGame::Instance()->getWindowHeight()))
			{
				continue;
			}

			Tileset tileset = getTilesetByID(id);

			id--;

			//draw the tile into position by offsetting its x & y position by subtracting the camera
			TheTextureManager::Instance()->drawTile(tileset.name, tileset.margin, tileset.spacing,
				((j * m_tileSize) - x2) - TheCamera::Instance()->getPosition().m_x, ((i * m_tileSize) - y2) - TheCamera::Instance()->getPosition().m_y, // Subtract smooth scrolling amounts & camera pos
				m_tileSize, m_tileSize,
				(id - (tileset.firstGridID - 1)) / tileset.numColumns,
				(id - (tileset.firstGridID - 1)) % tileset.numColumns, 
				TheGame::Instance()->getRenderer());
		}
	}
}

Tileset TileLayer::getTilesetByID(int tileID)
{
	for (int i = 0; i < m_tilesets.size(); i++)
	{
		if (i + 1 <= m_tilesets.size() - 1)
		{
			if (tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID)
			{
				return m_tilesets[i];
			}
		}
		else
		{
			return m_tilesets[i];
		}

		std::cout << "did not find tileset, returning empty tileset\n";
		Tileset t;
		return t;
	}
}