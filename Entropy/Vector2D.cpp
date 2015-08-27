#include "Vector2D.h"


Vector2D::Vector2D(double x, double y) : m_x(x), m_y(y)
{
}


Vector2D::~Vector2D()
{
}


// getters
double Vector2D::getX()
{
	return m_x;
}
double Vector2D::getY()
{
	return m_y;
}

float Vector2D::length()
{
	return sqrt( (m_x*m_x) + (m_y*m_y) );
}

// setters
void Vector2D::setX(double x)
{
	m_x = x;
}

void Vector2D::setY(double y)
{
	m_y = y;
}

void Vector2D::normalize()
{
	double l = length();

	if (l > 0) // we never want to attempt to divide by 0
	{
		(*this) *= 1 / l;
	}
}

// overloaded operators
Vector2D Vector2D::operator+ (const Vector2D& v2) const
{
	return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
}

Vector2D Vector2D::operator* (double scalar)
{
	return Vector2D(m_x * scalar, m_y * scalar);
}

Vector2D& Vector2D::operator*= (double scalar)
{
	m_x *= scalar;
	m_y *= scalar;

	return *this;
}

Vector2D Vector2D::operator- (const Vector2D& v2) const
{
	return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
}

Vector2D Vector2D::operator/ (double scalar)
{
	return Vector2D(m_x / scalar, m_y / scalar);
}

Vector2D& Vector2D::operator/= (double scalar)
{
	m_x /= scalar;
	m_y /= scalar;

	return *this;
}
