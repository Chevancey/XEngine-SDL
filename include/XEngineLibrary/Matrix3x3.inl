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
			result(x, y) = result(x, y) + matrix(x,y);
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
			result(x, y) = result(x, y) - matrix(x, y);
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
std::vector<std::vector<R>>& Matrix3x3<R>::GetDataAsUnsized() const
{
	std::vector<std::vector<float>> result(m_Matrix.size(), std::vector<R>(m_Matrix.size(), 0));

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
	std::array<std::array<R, 3>, 3> result();

	for (auto i = 0; i < m_Matrix.size(); i++)
	{
		for (auto j = 0; j < m_Matrix[0].size(); j++)
		{
			result[i][j] = m_Matrix[i][j];
		}
	}

	return result;
}