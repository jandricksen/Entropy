#include "Actor.h"
#include "Game.h"
#include "TileLayer.h"

Actor::Actor() : GameObject(),
	m_projectileFiringSpeed(0),
	m_projectileCounter(0),
	m_moveSpeed(0),
	m_dyingTime(0),
	m_dyingCounter(0),
	m_bPlayedDeathSound(false),
	m_bMoveUp(false),
	m_bMoveDown(false),
	m_bMoveLeft(false),
	m_bMoveRight(false),
	m_bRunning(false)
{
}


void Actor::load(std::unique_ptr<LoaderParams> const &pParams)
{
	// get position
	m_position = Vector2D(pParams->getX(), pParams->getY());

	// get drawing variables
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_numFrames = pParams->getNumFrames();
}


// draw the object to the screen
void Actor::draw()
{
	TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
		m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), m_angle, m_alpha, m_flip);
}

// apply velocity to current position
void Actor::update()
{
	m_position += m_velocity;
	m_currentFrame = int(((SDL_GetTicks() / (1000 / 3)) % m_numFrames));
}

bool Actor::checkCollideTile(Vector2D newPos)
{
	// if Actor out of bounds don't check
	if (newPos.m_y + m_height >= TheGame::Instance()->getWindowHeight() - 32)
	{
		return false;
	}
	else if (newPos.m_y <= 32)
	{
		return false;
	}

	else
	{
		for (std::vector<TileLayer*>::iterator it = m_pCollisionLayers->begin(); it != m_pCollisionLayers->end(); ++it)
		{
			TileLayer* pTileLayer = (*it);
			std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();

			//if (type() == "Projectile")
			//{
			//	std::cout << "Projectile" << std::endl;
			//}

			Vector2D layerPos = pTileLayer->getPosition();

			int x, y, tileColumn, tileRow, tileID = 0;

			// get specific tile
			x = layerPos.getX() / pTileLayer->getTileSize();
			y = layerPos.getY() / pTileLayer->getTileSize();

			//Vector2D startPos = newPos;
			//startPos.m_x += 15;
			//startPos.m_y += 20;
			//Vector2D endPos(newPos.m_x + (m_width - 15), (newPos.m_y) + m_height - 4);

			Vector2D startPos = newPos;
			startPos.m_x;
			startPos.m_y;
			Vector2D endPos(newPos.m_x + (m_width), newPos.m_y + (m_height));

			for (int i = startPos.m_x; i < endPos.m_x; ++i)
			{
				for (int j = startPos.m_y; j < endPos.m_y; ++j)
				{
					tileColumn = i / pTileLayer->getTileSize();
					tileRow = j / pTileLayer->getTileSize();

					tileID = tiles[tileRow + y][tileColumn + x];

					if (tileID != 0)
					{
						//std::cout << "COLLLLLLLLLLLLLLLLLL";
						return true;
					}
				}
			}
		}

		return false;
	}
}

void Actor::doDyingAnimation()
{
	m_currentFrame = int(((SDL_GetTicks() / (1000 / 10)) % m_numFrames));

	if (m_dyingCounter == m_dyingTime)
	{
		m_bDead = true;
	}
	m_dyingCounter++;
}
