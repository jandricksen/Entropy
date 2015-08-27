#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic()
{
}

AnimatedGraphic::~AnimatedGraphic()
{
}

void AnimatedGraphic::load(std::unique_ptr<LoaderParams> const &pParams)
{

	Actor::load(pParams);
	m_animSpeed = pParams->getAnimSpeed();

}

void AnimatedGraphic::draw()
{
	Actor::draw();
}

void AnimatedGraphic::update(double delta)
{
	m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames));
}

void AnimatedGraphic::clean()
{
	Actor::clean();
}