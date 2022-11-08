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
Matrix3x3<R>::Matrix3x3(const R (&m)[3][3])
{
	for (int x = 0; x < 3; ++x)
	{
		for (int y = 0; y < 3; ++y)
		{
			std::cout << m[x][y] << ",";
		}
		std::cout << std::endl;
	}
}
