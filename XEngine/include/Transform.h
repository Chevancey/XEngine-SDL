#pragma once

#include <iostream>

class Vector2;

class Transform 
{
public:

	Transform();
	~Transform();

	void SetPosition(Vector2& vector2);
	void SetRotation(float r);
	void SetScale(Vector2& vector2);

	void TransformPoint(Vector2& vector2);

private:

	Vector2* m_position;
	float m_rotation;
	Vector2* m_scale;
};