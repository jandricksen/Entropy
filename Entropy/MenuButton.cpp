#include "MenuButton.h"

#include "InputHandler.h"

MenuButton::MenuButton() : Actor(), m_callback(0), m_bReleased(true)
{
}


MenuButton::~MenuButton()
{
}

void MenuButton::load(std::unique_ptr<LoaderParams> const &pParams)
{
	Actor::load(std::move(pParams));
	m_callbackID = pParams->getCallbackID();
	m_currentFrame = MOUSE_OUT;
}


void MenuButton::draw()
{
	Actor::draw(); // use base class drawing
}

void MenuButton::update(double delta)
{
	Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition(); // get co-ords of mouse pointer and store them

	if ( pMousePos->getX() < (m_position.getX() + m_width) // check if mouse over button
		&& pMousePos->getX() > m_position.getX()
		&& pMousePos->getY() < (m_position.getY() + m_height)
		&& pMousePos->getY() > m_position.getY() )
	{
		m_currentFrame = MOUSE_OVER; // if so then mouse over button

		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
		{
			m_currentFrame = CLICKED;

			m_callback();

			m_bReleased = false;
		}
		else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
	}
	else
	{
		m_currentFrame = MOUSE_OUT; // else mouse outside button
	}
}

void MenuButton::clean()
{
	Actor::clean();
}