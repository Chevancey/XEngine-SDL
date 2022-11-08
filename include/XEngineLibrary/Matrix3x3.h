
#pragma once
#include <iostream>
//#include "LIB_COMPILING.h"


//template <typename R>
struct Matrix3x3
{
	Matrix3x3();
	Matrix3x3(const float (&m)[3][3]);


	float** m_Matrix;
	int row, column;

private:
	void MatrixInit();
};

//using Matrix3x3f = Matrix3x3<float>;
//using Matrix3x3i = Matrix3x3<int>;

//#include <Matrix3x3.inl>