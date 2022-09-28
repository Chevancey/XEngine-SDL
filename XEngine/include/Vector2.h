#include <vector>
#include <iostream>

class Vector2
{
public:
	Vector2(float x, float y);
	~Vector2();

	Vector2 operator=(const Vector2& vector);

	Vector2 operator+=(const Vector2& vector);
	Vector2 operator+(const Vector2& vector);

	Vector2 operator-=(const Vector2& vector);
	Vector2 operator-(const Vector2& vector);

	float x;
	float y;
private:
	std::vector<float> m_vector2;
};

