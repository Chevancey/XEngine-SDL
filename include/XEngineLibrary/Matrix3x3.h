
#pragma once
#include <iostream>
#include <array>
//#include "LIB_COMPILING.h"


template <typename R>
struct Matrix3x3
{
	Matrix3x3(std::array<std::array<R, 3>, 3> matrix);
	Matrix3x3(R data[3][3]);

	Matrix3x3() = default;

	Matrix3x3(R m00, R m01, R m02,
		R m10, R m11, R m12,
		R m20, R m21, R m22);

	~Matrix3x3() = default;

	const R& operator()(int row, int col) const;
	R& operator()(int row, int col);

	Matrix3x3 operator+(const Matrix3x3& matrix) const;
	Matrix3x3 operator-(const Matrix3x3& matrix) const;
	Matrix3x3 operator*(Matrix3x3& matrix) const;
	Matrix3x3 operator*(R value) const;
	Matrix3x3 operator/(const Matrix3x3& matrix) const;
	Matrix3x3 operator/(R value) const;

	Matrix3x3& operator+=(const Matrix3x3& matrix);
	Matrix3x3& operator-=(const Matrix3x3& matrix);
	Matrix3x3& operator*=(const Matrix3x3& matrix);
	Matrix3x3& operator*=(R value);
	Matrix3x3& operator/=(const Matrix3x3& matrix);
	Matrix3x3& operator/=(R value);
	
	std::array<std::array<R, 3>, 3> m_Matrix;


	int m_rows = 3;
	int m_columns = 3;

private:
	//void MatrixInit();
};

using Matrix3x3f = Matrix3x3<float>;
using Matrix3x3i = Matrix3x3<int>;

#include <Matrix3x3.inl>