#pragma once

#include <iostream>
#include "Vector2.h"

template<typename T>
class TransformSpecific
{
public:

	TransformSpecific()
	{
	}

	~TransformSpecific()
	{
	}

	void SetPosition(const Vector2<T>& vector)
	{
		//m_position.x = vector2.x;
		//m_position.y = vector2.y;
		m_position = vector;
		std::cout << m_position.x << " | " << m_position.y << std::endl;
	}
	
	void SetRotation(float r)
	{
		m_rotation = r;
		float sinAngle = sin(r);
		float cosAngle = cos(r);

		float tmpX = (cosAngle * m_position.x - sinAngle * m_position.y);
		float tmpY = (sinAngle * m_position.x + cosAngle * m_position.y);

		m_position.x = tmpX;
		m_position.y = tmpY;
		std::cout << m_position.x << " | " << m_position.y << std::endl;
	}

	void SetScale(const Vector2<T>& vector)
	{
		m_scale = &vector;
	}

	void TransformPoint(const Vector2<T>& vector)
	{
		*m_position += vector;
		std::cout << m_position.x << " | " << m_position.y << std::endl;
	}

private:
	Vector2<T> m_position;
	float m_rotation;
	Vector2<T> m_scale;
};

typedef TransformSpecific<float> Transform;