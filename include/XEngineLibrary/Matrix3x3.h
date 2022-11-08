
#pragma once
#include <iostream>
//#include "LIB_COMPILING.h"


template <typename R>
struct Matrix3x3
{
	Matrix3x3();
	Matrix3x3(R m00, R m01, R m02,
		      R m10, R m11, R m12,
		      R m20, R m21, R m22);

	void MatrixReplace(R m[][3]);
	
	float** m_Matrix;
	int row, column;

private:
	void MatrixInit();
};

using Matrix3x3f = Matrix3x3<float>;
using Matrix3x3i = Matrix3x3<int>;

#include <Matrix3x3.inl>