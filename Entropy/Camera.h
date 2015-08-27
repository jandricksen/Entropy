#pragma once

#include "Vector2D.h"

class Camera
{
public:

	static Camera* Instance()
	{
		if (s_pCamera == 0)
		{
			s_pCamera = new Camera();
		}

		return s_pCamera;
	}

	void update(Vector2D velocity);

	void setTarget(Vector2D* target) { m_pTarget = target; }
	void setPosition(const Vector2D& position) { m_position = position; }

	const Vector2D getPosition() const;

private:

	Camera();
	~Camera();

	static Camera* s_pCamera;

	// Camera's Target
	Vector2D* m_pTarget;

	//Camera's Position
	Vector2D m_position;
};

typedef Camera TheCamera;

