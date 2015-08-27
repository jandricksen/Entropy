#pragma once
#include <math.h>
#include "Actor.h"
#include "GameObjectFactory.h"
#include <iostream>


//	Handles Player Projectile
class Projectile : public Actor
{
public:

	Projectile();

	virtual ~Projectile() {};

	virtual std::string type() { return "Projectile"; }

	virtual void load(std::unique_ptr<LoaderParams> pParams);

	void spawn(int x, int y, Vector2D heading);

	virtual	void draw();

	virtual void collision();

	virtual void update(double delta);

	virtual void clean()
	{
		Actor::clean();
	}


private:
	

	Vector2D m_heading;

	void RemoveFromPlay();

};


//Projectile creator class
class ProjectileCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Projectile();
	}

};



//	Handles Enemy Projectiles
class EnemyProjectile : public Projectile
{
public:

	EnemyProjectile() : Projectile()
	{
	};

	virtual ~EnemyProjectile() {};

	virtual std::string type() { return "EnemyProjectile"; };

};