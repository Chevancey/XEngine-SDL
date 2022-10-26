//#pragma once
//#include <iostream>
//#include <math.h>
//
//template <typename T>
//struct LIB_API Matrix3x3
//{
//
//	Matrix3x3();
//	//Matrix3x3(T x, T y);
//	Matrix3x3(const Matrix3x3& other);
//	Matrix3x3(int arg1, int agr2);
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
//	Matrix3x3 operator*=(T s);
//	Matrix3x3 operator*(T s);
//
//	Matrix3x3 operator/=(T s);
//	Matrix3x3 operator/(T s);
//
//	bool operator==(const Matrix3x3& matrix) const;
//	bool operator!=(const Matrix3x3& matrix) const;
//
//	operator Matrix3x3<int>() const;
//	operator Matrix3x3<float>() const;
//
//	void printValues();
//
//	int m_sizeX;
//	int m_sizeY;
//	int& m_matrix;
//};
//
//template<typename T>
//Matrix3x3<T>::Matrix3x3(int arg1, int arg2)
//{
//	m_sizeX = arg1;
//	m_sizeY = arg2;
//	m_matrix = new int[m_sizeX][m_sizeY];
//}
//
//
////template<typename T>
////Matrix3x3<T>::Matrix3x3(int arg1, int arg2)
////{
////	m_size = arg1;
////	array = new int[arg1 * arg2];
////}
////
////
////template<typename T>
////int& Matrix3x3<T>::at(int i1, int i2) {
////	return array[i1 * size1 + i2];
////}
////
////template<typename T>
////void Matrix3x3<T>::printValues()
////{
////	for (int u = 0; u < size; u++) {
////		for (int v = 0; v < size; v++)
////			cout << adj[u][v] << " ";
////		cout << endl;
////	}
////}
//
//typedef LIB_API Matrix3x3<int> Matrix3x3i;
//typedef LIB_API Matrix3x3<float> Matrix3x3f;