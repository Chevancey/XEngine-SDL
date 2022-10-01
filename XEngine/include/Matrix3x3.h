#pragma once
#include <iostream>
#include <math.h>

template<typename T>
struct Matrix3x3
{
	Matrix3x3();
	Matrix3x3(T x, T y);
	Matrix3x3(const Vector2& other);
	Matrix3x3(T value);


	~Matrix3x3() {}

	Matrix3x3 operator+=(Matrix3x3 Vector2& vector);
	Matrix3x3 operator+(Matrix3x3 Vector2& vector) const;

	Matrix3x3 operator-=(Matrix3x3 Vector2& vector);
	Matrix3x3 operator-(Matrix3x3 Vector2& vector) const;

	Matrix3x3 operator*=(T s);
	Matrix3x3 operator*(T s);

	Matrix3x3 operator/=(T s);
	Matrix3x3 operator/(T s);

	bool operator==(const Matrix3x3& vector) const;
	bool operator!=(const Matrix3x3& vector) const;

	operator Matrix3x3<int>() const;
	operator Matrix3x3<float>() const;

	void printValues();

	T[,] m_matrix;
};