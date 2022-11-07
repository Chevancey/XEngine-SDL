//#pragma once
//#include <iostream>
////#include "LIB_COMPILING.h"
//
//
//template <typename R>
//struct Matrix3x3
//{
//
//	Matrix3x3() = default;
//
//	Matrix3x3( R m00, R m01, R m02, 
//			   R m10, R m11, R m12,
//			   R m20, R m21, R m22 );
//
//	Matrix3x3(R m[3][3]);
//
//	//Matrix3x3(int arg1, int agr2);
//
//	Matrix3x3(const Matrix3x3& other);
//
//	int& at(int i1, int i2);
//
//	~Matrix3x3() {}
//
//	Matrix3x3 operator+=(const Matrix3x3& matrix);
//	Matrix3x3 operator+(const Matrix3x3& matrix) const;
//
//	Matrix3x3 operator-=(const Matrix3x3& matrix);
//	Matrix3x3 operator-(const Matrix3x3& matrix) const;
//
//	Matrix3x3 operator*=(R s);
//	Matrix3x3 operator*(R s);
//
//	Matrix3x3 operator/=(R s);
//	Matrix3x3 operator/(R s);
//
//	bool operator==(const Matrix3x3& matrix) const;
//	bool operator!=(const Matrix3x3& matrix) const;
//
//	operator Matrix3x3<int>() const;
//	operator Matrix3x3<float>() const;
//
//	void printvalues();
//
//	int m_sizex;
//	int m_sizey;
//	R m_matrix[3][3];
//};
//
//template<typename R> Matrix3x3<R> operator*(R value, const Matrix3x3<R>& vec);
//template<typename R> Matrix3x3<R> operator/(R value, const Matrix3x3<R>& vec);
//
//using Matrix3x3f = Matrix3x3<float>;
//using Matrix3x3i = Matrix3x3<int>;
//
//#include <Matrix3x3.inl>