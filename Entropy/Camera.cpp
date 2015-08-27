#include "Camera.h"
#include "Game.h"
#include <iostream>

Camera* Camera::s_pCamera = 0;

Camera::Camera()
{
}


Camera::~Camera()
{
}


const Vector2D Camera::getPosition() const
{
	if (m_pTarget != 0)
	{
		Vector2D pos(m_pTarget->m_x - (TheGame::Instance()->getWindowWidth() / 2), m_pTarget->m_y - (TheGame::Instance()->getWindowHeight() / 2));


		if (pos.m_x < 0)
		{
			pos.m_x = 0;
		}

		if (pos.m_x > TheGame::Instance()->getWindowWidth() * 2)
		{
			pos.m_x = TheGame::Instance()->getWindowWidth() * 2;
		}

		if (pos.m_y < 0)
		{
			pos.m_y = 0;
		}

		if (pos.m_y > TheGame::Instance()->getWindowWidth() * 2)
		{
			pos.m_y = TheGame::Instance()->getWindowWidth() * 2;
		}

		return pos;
	}

	return m_position;
}