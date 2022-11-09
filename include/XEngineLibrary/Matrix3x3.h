
#pragma once
#include <iostream>
#include <array>
#include <vector>
#include "Vector2.h"

// The template allows it to have either floats or int values. WHY NOT USE THE POWER OF C++
template <typename R>
struct Matrix3x3
{
	// Matrix constructor with a std array of arrays
	Matrix3x3(std::array<std::array<R, 3>, 3> matrix);

	// Matrix constructor with a default int/float 2 dimensional array
	Matrix3x3(R data[3][3]);

	Matrix3x3(R m00, R m01, R m02,
			  R m10, R m11, R m12,
		      R m20, R m21, R m22);

	Matrix3x3() = default;
	~Matrix3x3() = default;

	// Equivalent of a get value at function in operator form
	const R& operator()(int row, int col) const;
	R& operator()(int row, int col);

	// get data
	const std::array<std::array<R, 3>, 3>& GetData() const;
	std::vector<std::vector<R>>& GetDataAsUnsized() const;

	// operations with simple sign resulting functions are constant.
	Matrix3x3 operator+(const Matrix3x3& matrix) const;
	Matrix3x3 operator-(const Matrix3x3& matrix) const;
	Matrix3x3 operator*(Matrix3x3& matrix) const;
	Matrix3x3 operator*(R value) const;
	Matrix3x3 operator/(const Matrix3x3& matrix) const;
	Matrix3x3 operator/(R value) const;

	// operations with = sign resulting functions are not constant.
	Matrix3x3& operator+=(const Matrix3x3& matrix);
	Matrix3x3& operator-=(const Matrix3x3& matrix);
	Matrix3x3& operator*=(const Matrix3x3& matrix);
	Matrix3x3& operator*=(R value);
	Matrix3x3& operator/=(const Matrix3x3& matrix);
	Matrix3x3& operator/=(R value);

	//Identity matrix
	static Matrix3x3 Identity();

	/// Special Operations for Matrix
	// make column rows and rows columns
	Matrix3x3 Transpose() const;

	// Inverse of a matrix
	Matrix3x3 Inverse() const;

	Matrix3x3 Adjugate() const;

	// the bomber man of matrices
	Matrix3x3 CofactorMatrix() const;

	float Cofactor(int row, int col) const;
	float GetMinor(int row, int col) const;
	
	static Matrix3x3 Translate(Vector2<R> position);
	static Matrix3x3 Rotate(R angle);
	static Matrix3x3 Scale(Vector2<R> scale);

	static float Determinant(std::vector<std::vector<R>> matrix);
	static std::vector<std::vector<R>>
	std::vector<std::vector<R>> SubMatrix(const std::vector<std::vector<R>>& matrix, int row, int col);

private:
	std::array<std::array<R, 3>, 3> m_Matrix;

	int m_rows = 3;
	int m_columns = 3;
};

//Instantiation of this class has special definitions to allow for shortcuts when specifying typenames
using Matrix3x3f = Matrix3x3<float>;
using Matrix3x3i = Matrix3x3<int>;

// Including .inl at the end for compilation. Which from my understanding is kind of like an extension of a .h file, however it allows for dynamic lib builds when dealing with templates.
#include <Matrix3x3.inl>