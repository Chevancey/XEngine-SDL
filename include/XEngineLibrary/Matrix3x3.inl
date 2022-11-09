#pragma once
#include <iostream>
#include "Matrix3x3.h"
#include <math.h>

template<typename R>
Matrix3x3<R>::Matrix3x3(std::array<std::array<R, 3>, 3> matrix) :
		m_Matrix(matrix)
{
}

template<typename R>
Matrix3x3<R>::Matrix3x3(R data[3][3])
{
	std::copy(&data[0][0], &data[0][0] + 3 * 3, &_data[0][0]);
}

template<typename R>
Matrix3x3<R>::Matrix3x3
(
	R m00, R m01, R m02,
	R m10, R m11, R m12,
	R m20, R m21, R m22		)
{

	m_Matrix[0][0] = m00;
	m_Matrix[0][1] = m01;
	m_Matrix[0][2] = m02;
	m_Matrix[1][0] = m10;
	m_Matrix[1][1] = m11;
	m_Matrix[1][2] = m12;
	m_Matrix[2][0] = m20;
	m_Matrix[2][1] = m21;
	m_Matrix[2][2] = m22;
}

// DATA OPERATORS
template<typename R>
const R& Matrix3x3<R>::operator()(int rows, int cols) const
{
	return m_Matrix[rows][cols];
}

template<typename R>
R& Matrix3x3<R>::operator()(int rows, int cols)
{
	return m_Matrix[rows][cols];
}

// DATA GETTERS
template<typename R>
std::vector<std::vector<R>>& Matrix3x3<R>::GetDataAsUnsized() const
{
	std::vector<std::vector<R>> result(m_Matrix.size(), std::vector<R>(m_Matrix.size(), 0));

	for (auto i = 0; i < m_Matrix.size(); i++)
	{
		for (auto j = 0; j < m_Matrix[0].size(); j++)
		{
			result[i][j] = m_Matrix[i][j];
		}
	}

	return result;
}

template<typename R>
const std::array<std::array<R, 3>, 3>& Matrix3x3<R>::GetData() const
{
	return m_Matrix;
}


// ADDITIONS AND SUBSTRACTIONS
// ===================================================================================
template<typename R>
Matrix3x3<R> Matrix3x3<R>::operator+(const Matrix3x3& matrix) const
{
	Matrix3x3<R> result(m_Matrix);

	for (int x = 0; x < m_rows; ++x)
	{
		for (int y = 0; y < m_columns; ++y)
		{
			result(x, y) = operator()(x, y) + matrix(x,y);
		}
	}

	for (int x = 0; x < m_rows; ++x)
	{
		for (int y = 0; y < m_columns; ++y)
		{
			std::cout << result.m_Matrix[x][y] << ",";
		}
		std::cout << " " << std::endl;
	}

	return result;
}

template<typename R>
Matrix3x3<R> Matrix3x3<R>::operator-(const Matrix3x3& matrix) const
{
	Matrix3x3<R> result(m_Matrix);

	for (int x = 0; x < m_rows; ++x)
	{
		for (int y = 0; y < m_columns; ++y)
		{
			result(x, y) = operator()(x, y) - matrix(x, y);
		}
	}

	for (int x = 0; x < m_rows; ++x)
	{
		for (int y = 0; y < m_columns; ++y)
		{
			std::cout << result.m_Matrix[x][y] << ",";
		}
		std::cout << " " << std::endl;
	}

	return result;
}

template<typename R>
Matrix3x3<R>& Matrix3x3<R>::operator+=(const Matrix3x3& matrix)
{
	Matrix3x3<R> result(m_Matrix);

	for (int x = 0; x < m_rows; ++x)
	{
		for (int y = 0; y < m_columns; ++y)
		{
			result(x, y) += matrix(x, y);
		}
	}

	for (int x = 0; x < m_rows; ++x)
	{
		for (int y = 0; y < m_columns; ++y)
		{
			std::cout << result.m_Matrix[x][y] << ",";
		}
		std::cout << " " << std::endl;
	}

	return result;
}

template<typename R>
Matrix3x3<R>& Matrix3x3<R>::operator-=(const Matrix3x3& matrix)
{
	Matrix3x3<R> result(m_Matrix);

	for (int x = 0; x < m_rows; ++x)
	{
		for (int y = 0; y < m_columns; ++y)
		{
			result(x, y) -= matrix(x, y);
		}
	}

	for (int x = 0; x < m_rows; ++x)
	{
		for (int y = 0; y < m_columns; ++y)
		{
			std::cout << result.m_Matrix[x][y] << ",";
		}
		std::cout << " " << std::endl;
	}

	return result;
}



// MULTIPLICATIONS AND DIVISION
// ===================================================================================

template<typename R>
Matrix3x3<R> Matrix3x3<R>::operator*(R value) const
{
	Matrix3x3<R> result(m_Matrix);

	for (int x = 0; x < m_rows; ++x)
	{
		for (int y = 0; y < m_columns; ++y)
		{
			result(x, y) = operator()(x, y) * value;
		}
	}

	for (int x = 0; x < m_rows; ++x)
	{
		for (int y = 0; y < m_columns; ++y)
		{
			std::cout << result.m_Matrix[x][y] << ",";
		}
		std::cout << " " << std::endl;
	}

	return result;
}


template<typename R>
Matrix3x3<R> Matrix3x3<R>::operator*(Matrix3x3& matrix) const
{
	Matrix3x3<R> result(m_Matrix);

	for (auto i = 0; i < result.m_rows; i++) 
	{
		for (auto j = 0; j < result.m_columns; j++) 
		{
			R tmp = 0.f;
			for (auto k = 0; k < m_columns; k++)
			{
				tmp += operator()(i, k) * matrix(k, j);
			}
			result(i, j) = tmp;
		}
	}

	for (int x = 0; x < m_rows; ++x)
	{
		for (int y = 0; y < m_columns; ++y)
		{
			std::cout << result.m_Matrix[x][y] << ",";
		}
		std::cout << " " << std::endl;
	}

	return result;
}

template<typename R>
Matrix3x3<R> Matrix3x3<R>::operator/(R value) const
{
	Matrix3x3<R> result(m_Matrix);

	for (int x = 0; x < m_rows; ++x)
	{
		for (int y = 0; y < m_columns; ++y)
		{
			result(x, y) = operator()(x, y) / value;
		}
	}

	for (int x = 0; x < m_rows; ++x)
	{
		for (int y = 0; y < m_columns; ++y)
		{
			std::cout << result.m_Matrix[x][y] << ",";
		}
		std::cout << " " << std::endl;
	}

	return result;
}

template<typename R>
Matrix3x3<R> Matrix3x3<R>::operator/(const Matrix3x3& matrix) const
{
	Matrix3x3<R> result(m_Matrix);

	for (auto i = 0; i < result.m_rows; i++)
	{
		for (auto j = 0; j < result.m_columns; j++)
		{
			R tmp = 0.f;
			for (auto k = 0; k < m_columns; k++)
			{
				tmp += operator()(i, k) / matrix(k, j);
			}
			result(i, j) = tmp;
		}
	}

	for (int x = 0; x < m_rows; ++x)
	{
		for (int y = 0; y < m_columns; ++y)
		{
			std::cout << result.m_Matrix[x][y] << ",";
		}
		std::cout << " " << std::endl;
	}

	return result;
}


template<typename R>
Matrix3x3<R>& Matrix3x3<R>::operator*=(R value)
{
	Matrix3x3<R> result(m_Matrix);

	for (int x = 0; x < m_rows; ++x)
	{
		for (int y = 0; y < m_columns; ++y)
		{
			result(x, y) *= value;
		}
	}

	for (int x = 0; x < m_rows; ++x)
	{
		for (int y = 0; y < m_columns; ++y)
		{
			std::cout << result.m_Matrix[x][y] << ",";
		}
		std::cout << " " << std::endl;
	}

	return result;
}

template<typename R>
Matrix3x3<R>& Matrix3x3<R>::operator*=(const Matrix3x3& matrix)
{
	Matrix3x3<R> result(m_Matrix);

	for (auto i = 0; i < result.m_rows; i++)
	{
		for (auto j = 0; j < result.m_columns; j++)
		{
			R tmp = 0.f;
			for (auto k = 0; k < m_columns; k++)
			{
				tmp += operator()(i, k) * matrix(k, j);
			}
			result(i, j) = tmp;
		}
	}

	for (int x = 0; x < m_rows; ++x)
	{
		for (int y = 0; y < m_columns; ++y)
		{
			std::cout << result.m_Matrix[x][y] << ",";
		}
		std::cout << " " << std::endl;
	}

	return result;
}

template<typename R>
Matrix3x3<R>& Matrix3x3<R>::operator/=(R value)
{
	Matrix3x3<R> result(m_Matrix);

	for (int x = 0; x < m_rows; ++x)
	{
		for (int y = 0; y < m_columns; ++y)
		{
			result(x, y) /= value;
		}
	}

	for (int x = 0; x < m_rows; ++x)
	{
		for (int y = 0; y < m_columns; ++y)
		{
			std::cout << result.m_Matrix[x][y] << ",";
		}
		std::cout << " " << std::endl;
	}

	return result;
}

template<typename R>
Matrix3x3<R>& Matrix3x3<R>::operator/=(const Matrix3x3& matrix)
{
	Matrix3x3<R> result(m_Matrix);

	for (auto i = 0; i < result.m_rows; i++)
	{
		for (auto j = 0; j < result.m_columns; j++)
		{
			R tmp = 0.f;
			for (auto k = 0; k < m_columns; k++)
			{
				tmp += operator()(i, k) / matrix(k, j);
			}
			result(i, j) = tmp;
		}
	}

	for (int x = 0; x < m_rows; ++x)
	{
		for (int y = 0; y < m_columns; ++y)
		{
			std::cout << result.m_Matrix[x][y] << ",";
		}
		std::cout << " " << std::endl;
	}

	return result;
}
template<typename R>
static Matrix3x3<R> Matrix3x3<R>::Identity() 
{
	Matrix3x3<R> result;

	for (auto i = 0; i < 3; i++) 
	{
		result(i, i) = 1;
	}

	return result;
}

template<typename R>
Matrix3x3<R> Matrix3x3<R>::Transpose() const 
{
	Matrix3x3<R> result(m_Matrix);

	for (auto row = 0; row < _rows; row++)
	{
		for (auto col = 0; col < _cols; col++) 
		{
			result(row, col) = operator()(col, row);
		}
	}

	return result;
}

template<typename R>
Matrix3x3<R> Matrix3x3<R>::Inverse() const 
{
	auto d = Determinant(GetDataAsUnsized());
	if (d == 0)
		throw std::runtime_error("Matrix is singular.");
	return Adjugate() / d;
}

template<typename R>
Matrix3x3<R> Matrix3x3<R>::Adjugate() const 
{
	return CofactorMatrix().Transpose();
}

template<typename R>
Matrix3x3<R> Matrix3x3<R>::CofactorMatrix() const 
{
	Matrix3x3<R> result(m_Matrix);

	for (auto row = 0; row < _rows; row++)
	{
		for (auto col = 0; col < _cols; col++)
		{
			result(row, col) = Cofactor(row, col);
		}
	}

	return result;
}

template<typename R>
R Matrix3x3<R>::Cofactor(int row, int col) const 
{
	auto minor = 0.f;
	minor = GetMinor(row, col);
	return (row + col) % 2 == 0 ? minor : -minor;
}

template<typename R>
R Matrix3x3<R>::GetMinor(int row, int col) const 
{
	return Determinant(Submatrix(GetDataAsUnsized(), row, col));
}

template<typename R>
R Matrix3x3<R>::Determinant(std::vector<std::vector<R>> matrix) 
{
	auto rows = matrix.size();
	auto d = 0.f;

	if (rows == 2)
		return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
	else
		for (auto col = 0; col < rows; col++)
			d += (R)std::pow(-1, col) * matrix[0][col] *
			Determinant(SubMatrix(matrix, 0, col));

	return d;
}

template<typename R>
std::vector<std::vector<R>> Matrix3x3<R>::SubMatrix(const std::vector<std::vector<R>>& matrix, int row, int col) 
{
	auto rows = matrix.size();
	auto cols = matrix[0].size();

	std::vector<std::vector<R>> result(rows - 1,
		std::vector<R>(cols - 1, 0));

	auto subi = 0;
	for (auto i = 0; i < rows; i++) {
		auto subj = 0;
		if (i == row)
			continue;
		for (auto j = 0; j < cols; j++) {
			if (j == col)
				continue;
			result[subi][subj] = matrix[i][j];
			subj++;
		}
		subi++;
	}

	return result;
}

template<typename R>
Matrix3x3<R> Matrix3x3<R>::Translate(Vector2<R> position)
{
	return Matrix3({ {
	  { 1, 0, position.x },
	  { 0, 1, position.y },
	  { 0, 0, 1			 },
	} });
}

template<typename R>
Matrix3x3<R> Matrix3x3<R>::Rotate(R angle)
{
	auto a = Deg2Rad(angle);
	auto cos = std::cos(a);
	auto sin = std::sin(a);

	return Matrix3x3<R>({ {
	  { cos, -sin, 0 },
	  { sin, cos,  0 },
	  { 0,    0,   1 },
	} });
}

template<typename R>
Matrix3x3<R> Matrix3x3<R>::Scale(Vector2<R> scale)
{
	return Matrix3({ {
	  { scale.x, 0, 0 },
	  { 0, scale.y, 0 },
	  { 0,   0,		1 },
	} });
}

template<typename R>
Matrix3x3<R> Matrix3x3<R>::SRT(Vector2<R> scale, R angle, Vector2<R> position)
{

	return Matrix3x3<R>::Scale(scale) * Matrix3x3<R>::Rotate(angle) *
		Matrix3x3<R>::Translate(position);
}

template<typename R>
Matrix3x3<R> Matrix3x3<R>::TRS(Vector2<R> position, R angle, Vector2<R> scale)
{
	return Matrix3x3<R>::Translate(position) * Matrix3x3<R>::Rotate(angle) *
		Matrix3x3<R>::Scale(scale);
}