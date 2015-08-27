#pragma once

#include <iostream>
#include <vector>

class Player;
class GameObject;
class TileLayer;

class CollisionManager
{

public:

	void checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*> &objects);
	void checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*> &collisionLayers);

};

