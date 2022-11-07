//#pragma once
//#include <iostream>
//#include "Matrix3x3.h"
//#include <math.h>
//
////template<typename R>
////Matrix3x3<R>::Matrix3x3()
////{
////	m_matrix[][] = { 
////
////		{0,0,0},
////		{0,0,0},
////		{0,0,0} 
////
////	};
////}
//
//template<typename R>
//Matrix3x3<R>::Matrix3x3(R m[3][3])
//{
//	for (int x = 0; x < 3; ++x) 
//	{
//		for (int y = 0; y < 3; ++y)
//		{
//			m_matrix[x][y] == m[x][y];
//		}
//	}
//	
//}
//
//template<typename R>
//Matrix3x3<R>::Matrix3x3
//(
//	R m00, R m01, R m02,
//	R m10, R m11, R m12,
//	R m20, R m21, R m22 
//)
//{
//	m_size = m00;
//
//	m_matrix[3] =
//	{
//		{ m00, m01, m02 },
//	};
//		//{ m10, m11, m12 },
//		//{ m20, m21, m22 }
//	//};
//}
//
//template<typename R>
//int& Matrix3x3<R>::at(int i1, int i2) {
//	return array[i1 * size1 + i2];
//}
//
//template<typename R>
//void Matrix3x3<R>::printvalues()
//{
//	for (int u = 0; u < size; u++) {
//		for (int v = 0; v < size; v++)
//			cout << adj[u][v] << " ";
//		cout << endl;
//	}
//}
