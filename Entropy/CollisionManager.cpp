#include "CollisionManager.h"
#include "Collision.h"
#include "Player.h"
#include "Enemy.h"
#include "TileLayer.h"


void CollisionManager::checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*> &objects)
{
	SDL_Rect* pRect1 = new SDL_Rect();
	pRect1->x = pPlayer->getPosition().getX();
	pRect1->y = pPlayer->getPosition().getY();
	pRect1->w = pPlayer->getWidth();
	pRect1->h = pPlayer->getHeight();

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->type() != std::string("Enemy") || !objects[i]->isUpdating())
		{
			continue;
		}

		SDL_Rect* pRect2 = new SDL_Rect();
		pRect2->x = objects[i]->getPosition().getX();
		pRect2->y = objects[i]->getPosition().getY();
		pRect2->w = objects[i]->getWidth();
		pRect2->h = objects[i]->getHeight();

		if (RectRect(pRect1, pRect2))
		{
			if (!objects[i]->dead() && !objects[i]->dying())
			{
				pPlayer->collision();
			}
		}

		delete pRect2;
	}

	delete pRect1;
}


void CollisionManager::checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*> &collisionLayers)
{

	// iterate through collision layers
	for (std::vector<TileLayer*>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); ++it)
	{

		TileLayer* pTileLayer = (*it);
		std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();

		Vector2D layerPos = pTileLayer->getPosition();

		int x, y, tileColumn, tileRow, tileid = 0;

		x = layerPos.getX() / pTileLayer->getTileSize();
		y = layerPos.getY() / pTileLayer->getTileSize();

		if (pPlayer->getVelocity().getX() >= 0 || pPlayer->getVelocity().getY() >= 0)
		{
			tileColumn = ((pPlayer->getPosition().getX() + pPlayer->getWidth()) / pTileLayer->getTileSize());
			tileRow = ((pPlayer->getPosition().getY() + pPlayer->getHeight()) / pTileLayer->getTileSize());
			tileid = tiles[tileRow + y][tileColumn + x];
		}
		else if (pPlayer->getVelocity().getX() < 0 || pPlayer->getVelocity().getY() < 0)
		{
			tileColumn = pPlayer->getPosition().getX() / pTileLayer->getTileSize();
			tileRow = pPlayer->getPosition().getY() / pTileLayer->getTileSize();
			tileid = tiles[tileRow + y][tileColumn + x];
		}

		if (tileid != 0) // if tileID not blank then collision
		{
			pPlayer->collision();
		}

	}

}