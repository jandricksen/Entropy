#include "Player.h"
#include "Camera.h"
#include "Game.h"
#include "Projectile.h"

Player::Player() : Actor(),
m_invulnerable(false),
m_invulnerableTime(200),
m_invulnerableCounter(0),
weaponCoolDown(500),
previousShotTime(0)
{
}

void Player::load(std::unique_ptr<LoaderParams> const &pParams)
{
	Actor::load(std::move(pParams));

	//Not shooting
	m_bFiring = false;

	m_moveSpeed = 3;

	// time it takes for death explosion
	m_dyingTime = 2;

	// flip player image horizontally
	m_flip = SDL_FLIP_HORIZONTAL;

	TheCamera::Instance()->setTarget(&m_position);
}

void Player::draw()
{
	TheTextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX() - TheCamera::Instance()->getPosition().m_x, (Uint32)m_position.getY() - TheCamera::Instance()->getPosition().m_y,
		m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), m_angle, m_alpha);
}

void Player::handleAnimation()
{
	// if the player is invulnerable we can flash its alpha to let people know
	if (m_invulnerable)
	{
		// invulnerability is finished, set values back
		if (m_invulnerableCounter == m_invulnerableTime)
		{
			m_invulnerable = false;
			m_invulnerableCounter = 0;
			m_alpha = 255;
		}
		else // otherwise, flash the alpha on and off
		{
			if (m_alpha == 255)
			{
				m_alpha = 0;
			}
			else
			{
				m_alpha = 255;
			}
		}

		// increment our counter
		m_invulnerableCounter++;
	}

	m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));
}


void Player::update(double delta)
{
	// if the player is not doing its death animation then update it normally
	if (!m_bDying)
	{
		// get input
		handleInput();

		if (m_bMoveLeft)
		{
			if (m_bRunning)
			{
				m_velocity.m_x = -5 * delta;
			}
			else
			{
				m_velocity.m_x = -2 * delta;
			}
		}
		else if (m_bMoveRight)
		{
			if (m_bRunning)
			{
				m_velocity.m_x = 5 * delta;
			}
			else
			{
				m_velocity.m_x = 2 * delta;
			}
		}
		else
		{
			m_velocity.m_x = 0;
		}


		if (m_bMoveUp && m_position.m_y > 32)
		{
			if (m_bRunning)
			{
				m_velocity.m_y = -5 * delta;
			}
			else
			{
				m_velocity.m_y = -2 * delta;
			}
		}
		else if (m_bMoveDown)
		{
			if (m_bRunning)
			{
				m_velocity.m_y = 5 * delta;
			}
			else
			{
				m_velocity.m_y = 2 * delta;
			}
		}
		else
		{
			m_velocity.m_y = 0;
		}

		// do normal position += velocity update
		Actor::update();

		// update the animation
		handleAnimation();

		// update movement
		handleMovement(m_velocity);
	}
	else // if the player is doing the death animation
	{
		m_velocity.m_x = 0;
		m_alpha = 0;
	}
}


void Player::handleMovement(Vector2D velocity)
{
	Vector2D newPos = m_position;

	// add velocity to the x position
	newPos.m_x = m_position.m_x + velocity.m_x;

	// add velocity to the y position
	newPos.m_y = m_position.m_y + velocity.m_y;

	// check if the new x position would collide with a tile
	if (!checkCollideTile(newPos))
	{
		// no collision, add to the actual x position
		m_position.m_x = newPos.m_x;
	}
	else
	{
		// collision, stop x movement
		m_velocity.m_x = 0;
		collision();
	}

	// get the current position after x movement
	newPos = m_position;

	// add velocity to y position
	newPos.m_y += velocity.m_y;

	// check if new y position would collide with a tile
	if (!checkCollideTile(newPos))
	{
		// no collision, add to the actual y position
		m_position.m_y = newPos.m_y;
	}
	else
	{
		// collision, stop y movement
		m_velocity.m_y = 0;
		collision();
	}
}

void Player::ressurect()
{
	TheGame::Instance()->setPlayerLives(TheGame::Instance()->getPlayerLives() - 1);

	m_position.setX(10);
	m_position.setY(200);
	m_bDying = false;

	m_textureID = "player";

	m_currentFrame = 0;
	m_numFrames = 5;
	m_width = 101;
	m_height = 46;

	m_dyingCounter = 0;
	m_invulnerable = true;
}

void Player::clean()
{
	Actor::clean();
}

void Player::handleInput()
{
	if (!m_bDead)
	{
		// KEY HANDLER

		// move up and down (w/s/up/down)
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_W) ||
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) &&
			m_position.getY() > 0
			)
		{
			m_bMoveUp = true;
			m_bMoveDown = false;
		}
		else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_S) ||
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN) &&
			(m_position.getY() + m_height) < TheGame::Instance()->getWindowHeight() - 10
			)
		{
			m_bMoveDown = true;
			m_bMoveUp = false;
		}
		else
		{
			m_bMoveUp = false;
			m_bMoveDown = false;
		}

		// move left and right (a/d/left/right)
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A) ||
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) &&
			m_position.getX() > 0)
		{
			m_bMoveLeft = true;
			m_bMoveRight = false;
		}
		else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) ||
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) &&
			(m_position.getX() + m_width) < TheGame::Instance()->getWindowWidth() - 10)
		{
			m_bMoveRight = true;
			m_bMoveLeft = false;
		}
		else
		{
			m_bMoveLeft = false;
			m_bMoveRight = false;
		}

		// LEFT MOUSE BUTTON FIRE WEAPON
		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) == true)
		{
			m_bFiring = true;
		}
		else if (TheInputHandler::Instance()->getMouseButtonState(LEFT) == false)
		{
			m_bFiring = false;
		}
	}
}


void Player::collision()
{
	m_bDying = true;
}

void Player::FireWeapon(std::vector<Projectile*>* projectileObjects)
{
	if (SDL_GetTicks() - previousShotTime >= weaponCoolDown) // Check Weapon Cooldown Time Ok
	{
		previousShotTime = SDL_GetTicks();

		for (std::vector<Projectile*>::iterator it = projectileObjects->begin(); it != projectileObjects->end(); ++it)
		{
			if ((*it)->inPlay() == false)
			{
				// Get correct Mouse Pos Relative to Camera & Map Pos
				int MouseX = TheInputHandler::Instance()->getMousePosition()->m_x + TheCamera::Instance()->getPosition().m_x;
				int MouseY = TheInputHandler::Instance()->getMousePosition()->m_y + TheCamera::Instance()->getPosition().m_y;

				// Create Target Vector 
				Vector2D targetVector(MouseX - m_position.getX(), MouseY - m_position.getY());
				targetVector.normalize();

				// Spawn Projectile
				(*it)->spawn(m_position.getX(), m_position.getY(), targetVector);
				break;
			}
		}
	}
}
