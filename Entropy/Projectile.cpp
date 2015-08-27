#include "Projectile.h"
#include "Game.h"
#include "Camera.h"


Projectile::Projectile() : Actor()
{
}

void Projectile::load(std::unique_ptr<LoaderParams> pParams)
{
	Actor::load(std::move(pParams));
}

void Projectile::spawn(int x, int y, Vector2D heading)
{
	m_position.setX(x);
	m_position.setY(y);

	m_heading = heading;

	// time it takes for death explosion
	m_dyingTime = 0.01;

	m_acceleration.setX(m_heading.getX());
	m_acceleration.setY(m_heading.getY());

	m_velocity.setX(m_heading.getX());
	m_velocity.setY(m_heading.getY());

	m_bInPlay = true;
}

void Projectile::draw()
{
	TheTextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX() - TheCamera::Instance()->getPosition().m_x, (Uint32)m_position.getY() - TheCamera::Instance()->getPosition().m_y,
		m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), m_angle, m_alpha);
}

void Projectile::collision()
{
	m_bDying = true;
}

void Projectile::update(double delta)
{
	if (!m_bDying && m_bInPlay)
	{
		m_position += m_velocity * 10 * delta;

		m_currentFrame = int(((SDL_GetTicks() / (1000 / 3)) % m_numFrames));

		Vector2D collisionVector(m_position.getX(), m_position.getY());
		if (checkCollideTile(collisionVector))
		{
			collision();
		}
	}
	else // if the Projectile is doing the death animation
	{
		// if the death animation has completed
		if (m_dyingCounter >= m_dyingTime)
		{
			m_dyingCounter = 0;
			m_bDead = true;
			RemoveFromPlay();
		}
		else
		{
			m_dyingCounter++;
		}
	}
}

void Projectile::RemoveFromPlay()
{
	m_velocity.setX(0);
	m_velocity.setY(0);
	m_position.setX(-100);
	m_position.setY(-100);
	m_bDead = false;
	m_bDying = false;
	m_bInPlay = false;
}