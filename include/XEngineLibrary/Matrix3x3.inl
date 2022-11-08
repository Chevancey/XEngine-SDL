#pragma once
#include <iostream>
#include "Matrix3x3.h"
#include <math.h>

template<typename R>
Matrix3x3<R>::Matrix3x3()
{
	row = 3;
	column = 3;

	m_Matrix = new R * [row];

	for (int i = 0; i < row; ++i)
	{
		m_Matrix[i] = new R[column];
	}

	for (int x = 0; x < 3; ++x)
	{
		for (int y = 0; y < 3; ++y)
		{
			std::cout << m_Matrix[x][y] << ",";
		}
		std::cout << " " << std::endl;
	}
}

template<typename R>
Matrix3x3<R>::Matrix3x3
(
	R m00, R m01, R m02,
	R m10, R m11, R m12,
	R m20, R m21, R m22		)
{

	row = 3;
	column = 3;

	m_Matrix = new R * [row];

	for (int i = 0; i < row; ++i)
	{
		m_Matrix[i] = new R[column];
	}


	m_Matrix[0][0] = m00;
	m_Matrix[0][1] = m01;
	m_Matrix[0][2] = m02;
	m_Matrix[1][0] = m10;
	m_Matrix[1][1] = m11;
	m_Matrix[1][2] = m12;
	m_Matrix[2][0] = m20;
	m_Matrix[2][1] = m21;
	m_Matrix[2][2] = m22;


	for (int x = 0; x < 3; ++x)
	{
		for (int y = 0; y < 3; ++y)
		{
			std::cout << m_Matrix[x][y] << ",";
		}
		std::cout << " " << std::endl;
	}
}

template<typename R>
void Matrix3x3<R>::MatrixReplace(R m[][3])
{

}
