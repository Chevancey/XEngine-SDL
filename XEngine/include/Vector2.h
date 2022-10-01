#pragma once
#include <iostream>
#include <math.h>

template<typename T>
struct Vector2
{
	Vector2();
	Vector2(T x, T y);
	Vector2(const Vector2& other);
	Vector2(T value);


	~Vector2() {}

	Vector2 operator+=(const Vector2& vector);
	Vector2 operator+(const Vector2& vector) const;

	Vector2 operator-=(const Vector2& vector);
	Vector2 operator-(const Vector2& vector) const;

	Vector2 operator*=(T s);
	Vector2 operator*(T s);

	Vector2 operator/=(T s);
	Vector2 operator/(T s);

	bool operator==(const Vector2& vector) const;
	bool operator!=(const Vector2& vector) const;

	operator Vector2<int>() const;
	operator Vector2<float>() const;

	void printValues();

	T x;
	T y;
};

template<typename T>
void Vector2<T>::printValues() {}

template<typename T>
Vector2<T>::Vector2()
{
	x = (T)0;
	y = (T)0;
}

//Operator
template<typename T>
Vector2<T>::Vector2(T inputX, T inputY)
{
	x = inputX;
	y = inputY;
}

template<typename T>
Vector2<T>::Vector2(const Vector2& vector)
{
	x = (T)vector.x;
	y = (T)vector.y;
}

template<typename T>
Vector2<T>::Vector2(T bothValues)
{
	x = bothValues;
	y = bothValues;
}

//Plus
template<typename T>
Vector2<T> Vector2<T>::operator+=(const Vector2& vector)
{
	std::cout << (x += vector.x) << " | " << (y += vector.y) << std::endl;

	return { x += vector.x, y += vector.y };
}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2& vector) const
{
	std::cout << x + vector.x << " | " << y + vector.y << std::endl;

	return { x + vector.x, y + vector.y };
}

//Minus
template<typename T>
Vector2<T> Vector2<T>::operator-=(const Vector2& vector)
{
	std::cout << (x -= vector.x) << " | " << (y -= vector.y) << std::endl;

	return { x -= vector.x , y -= y };
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& vector) const
{
	std::cout << x - vector.x << " | " << y - vector.y << std::endl;

	return { x - vector.x, y - vector.y };
}

//Multiply
template<typename T>
Vector2<T> Vector2<T>::operator*=(T s)
{
	std::cout << (x *= s) << " | " << (y *= s) << std::endl;

	return { x *= s, y *= s };
}

template<typename T>
Vector2<T> Vector2<T>::operator*(T s)
{
	std::cout << x * s << " | " << y * s << std::endl;

	return { x * s, y * s };
}

//Divide
template<typename T>
Vector2<T> Vector2<T>::operator/=(T s)
{
	std::cout << (x /= s) << " | " << (y /= s) << std::endl;

	return { x /= s, y /= s };
}

template<typename T>
Vector2<T> Vector2<T>::operator/(T s)
{
	std::cout << x / s << " | " << y / s << std::endl;

	return { x / s, y / s };
}

//BOOL return for equal to and not equal to
template<typename T>
bool Vector2<T>::operator==(const Vector2& vector) const
{
	if (x == vector.x && y == vector.y)
	{
		std::cout << "true" << std::endl;
		return true;
	}

	std::cout << "false" << std::endl;
	return false;
}

template<typename T>
bool Vector2<T>::operator!=(const Vector2& vector) const
{
	if ( x != vector.x && y != vector.y)
	{
		std::cout << "true" << std::endl;
		return true;
	}

	std::cout << "false" << std::endl;
	return false;
}

template <typename T>
Vector2<T>::operator Vector2<float>() const {
	return { static_cast<float>(this->x), static_cast<float>(this->y) };
}

template <typename T>
Vector2<T>::operator Vector2<int>() const {
	return { static_cast<int>(this->x), static_cast<int>(this->y) };
}

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;