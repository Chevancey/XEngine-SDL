#include "Vector2.h"

Vector2::Vector2(float inputX, float inputY) :
	m_vector2({inputX, inputY}),
	x(inputX),
	y(inputY)
{
}

Vector2::~Vector2()
{
}

Vector2 Vector2::operator=(const Vector2& vector)
{
 	std::cout << vector.x << " | " << vector.y << std::endl;
	return { vector.x, vector.y };
}

Vector2 Vector2::operator+=(const Vector2& vector)
{
	std::cout << x + vector.x << " | " << y + vector.y << std::endl;

	return { x + vector.x, y + vector.y };
}

Vector2 Vector2::operator+(const Vector2& vector)
{
	std::cout << x + vector.x << " | " << y + vector.y << std::endl;

	return { x + vector.x, y + vector.y };
}

Vector2 Vector2::operator-=(const Vector2& vector)
{
	std::cout << x - vector.x << " | " << y - vector.y << std::endl;

	return { x - vector.x, y - vector.y };
}

Vector2 Vector2::operator-(const Vector2& vector)
{
	std::cout << x - vector.x << " | " << y - vector.y << std::endl;

	return { x - vector.x, y - vector.y };
}
