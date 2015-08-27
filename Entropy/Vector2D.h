#pragma once
#include <math.h>


class Vector2D
{
public:
	Vector2D()
	{
		m_x = 0;
		m_y = 0;
	}

	Vector2D(double x, double y);
	~Vector2D();

	// getters
	double getX();
	double getY();

	float length();

	// setters
	void setX(double x);
	void setY(double y);

	void normalize();

	// overloaded operators
	Vector2D operator+ (const Vector2D& v2) const;
	friend Vector2D& operator+= (Vector2D& v1, const Vector2D& v2)
	{
		v1.m_x += v2.m_x;
		v1.m_y += v2.m_y;

		return v1;
	}

	Vector2D operator* (double scalar);
	Vector2D& operator*= (double scalar);

	Vector2D operator- (const Vector2D& v2) const;
	friend Vector2D& operator-= (Vector2D& v1, const Vector2D& v2)
	{
		v1.m_x -= v2.m_x;
		v1.m_y -= v2.m_y;

		return v1;
	}

	Vector2D operator/ (double scalar);
	Vector2D& operator/= (double scalar);

	double m_x;
	double m_y;
};

