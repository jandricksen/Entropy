#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>

#include "GameObject.h"
#include "TextureManager.h"


class Actor : public GameObject
{
public:

	virtual ~Actor() {}; // for polymorphism

	// load from file
	virtual void load(std::unique_ptr<LoaderParams> const &pParams);

	virtual void draw();
	virtual void update();

	virtual void clean() {};

	virtual void collision() {};

	virtual std::string type() { return "Actor"; }

protected:

	// we won't directly create Actors
	Actor();

	bool checkCollideTile(Vector2D newPos);
	void doDyingAnimation();

	int m_projectileFiringSpeed;
	int m_projectileCounter;
	int m_moveSpeed;

	bool m_bFiring;
	bool m_bMoveUp;
	bool m_bMoveDown;
	bool m_bMoveLeft;
	bool m_bMoveRight;
	bool m_bRunning;

	int m_dyingTime;
	int m_dyingCounter;

	bool m_bPlayedDeathSound;

};

