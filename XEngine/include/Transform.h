#pragma once
#include <iostream>
//#include <numbers>
#include "Vector2.h"
#include "DegRad.h"

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
		m_position = vector;
		std::cout << m_position.x << " | " << m_position.y << std::endl;
	}
	
	void SetRotation(float r)
	{
		m_rotation = Deg2Rad(r);
		float sinAngle = sin(m_rotation);
		float cosAngle = cos(m_rotation);

		float tmpX = (cosAngle * m_position.x - sinAngle * m_position.y);
		float tmpY = (sinAngle * m_position.x + cosAngle * m_position.y);

		m_position.x = tmpX;
		m_position.y = tmpY;
		std::cout << m_position.x << " | " << m_position.y << std::endl;
	}

	void SetScale(const Vector2<T>& vector)
	{
		m_scale = vector;
		m_position.x *= m_scale.x;

		m_position.y *= m_scale.y;
		std::cout << m_position.x << " | " << m_position.y << std::endl;
	}

	void TransformPoint(Vector2<T>& vector)
	{
		vector.x = m_position.x;
		vector.y = m_position.y;

		std::cout << vector.x << " | " << vector.y << std::endl;
	}

private:
	Vector2<T> m_position;
	float m_rotation;
	Vector2<T> m_scale;
};

typedef TransformSpecific<float> Transform;