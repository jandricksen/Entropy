#pragma once
/*
	Base Class for all Enemy types. Child of Actor
	Updated: 07.06.2015
*/

#include "Actor.h"

class Enemy : public Actor
{
public:
	virtual std::string type() { return "Enemy"; }

protected:
	int m_health;

	Enemy() : Actor() {};
	virtual ~Enemy() {} // for polymorphism
};
