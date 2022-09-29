#include "Transform.h"
////#include "Vector2.h"
//#include <cmath>
//
//
//Transform::Transform()
//{
//}
//Transform::~Transform()
//{
//}
//
//
//void Transform::SetPosition(Vector2<T>& vector2)
//{
//	m_position = &vector2;
//	std::cout << m_position->x << " | " << m_position->y << std::endl;
//}
//
//void Transform::SetRotation(float r)
//{
//	//m_position->x = cos(r) * m_position->x + sin(r) * m_position->y;
//	//m_position->y = -sin(r) * m_position->x + cos(r) * m_position->y;
//	m_rotation = r;
//	std::cout << m_position->x << " | " << m_position->y << std::endl;
//}
//
//template<typename T>
//void Transform::SetScale(Vector2<T>& vector2)
//{
//	m_scale = &vector2;
//}
//
//
//void Transform::TransformPoint(Vector2<T>& vector2)
//{
//	*m_position += vector2;
//	std::cout << m_position->x << " | " << m_position->y << std::endl;
//}