#ifndef GMATRIX_H
#define GMATRIX_H
/*!
File: GMatrix.h
Purpose: A Gateware interface that handles Martix functions.
Author: Shuo-Yi Chang
Contributors: N/A
Last Modified: 8/30/2016
Interface Status: Beta
Copyright: 7thGate Software LLC.
License: MIT
*/

//! GMathDefines inherits directly from GMultiThreaded.
#include "../G_Core/GMultiThreaded.h"
#include "GMathDefines.h"

//! The core namespace to which all Gateware interfaces/structures/defines must belong.
namespace GW
{
	//! The namespace to which all Gateware library interfaces must belong.
	namespace MATH
	{
		//! Unique Identifier for this interface. {7FD30A77-340C-485B-9B32-F1EFA3717331}
		static const GUUIID GMatrixUUIID =
		{
			0x7fd30a77, 0x340c, 0x485b,{ 0x9b, 0x32, 0xf1, 0xef, 0xa3, 0x71, 0x73, 0x31 }
		};

		class GMatrix : public CORE::GMultiThreaded
		{
		public:
			//float Matrix
			virtual GReturn AdditionMatrix(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF& _outMatrix) = 0;
			virtual GReturn SubtractionMatrix(GMATRIXF _matrix1, GMATRIXF _matrix2,	GMATRIXF& _outMatrix) = 0;
			virtual GReturn MultiplyMatrix(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF& _outMatrix) = 0;
			virtual GReturn DivideMatrix(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF& _outMatrix) = 0;
			virtual GReturn MultiplyVector(GMATRIXF _matrix, GVECTORF _vector, GMATRIXF& _outMatrix) = 0;
			virtual GReturn MultiplyNormal(GMATRIXF _matrix, GVECTORF _vector, GMATRIXF& _outMatrix) = 0;
			virtual GReturn ConvertQuaternion(GQUATERNIONF _quaternion, GMATRIXF& _outMatrix) = 0;
			virtual GReturn MultiplyNum(GMATRIXF _matrix, float _num, GMATRIXF& _outMatrix) = 0;
			virtual GReturn DivideNum(GMATRIXF _matrix, float _num, GMATRIXF& _outMatrix) = 0;
			virtual GReturn DeterminantMatrix(GMATRIXF _matrix, GMATRIXF& _outMatrix) = 0;
			virtual GReturn TransposeMatrix(GMATRIXF _matrix, GMATRIXF& _outMatrix) = 0;
			virtual GReturn Inverse(GMATRIXF _matrix, GMATRIXF& _outMatrix) = 0;
			virtual GReturn Identity(GMATRIXF& _outMatrix) = 0;
			virtual GReturn GetRotation(GMATRIXF _matrix, GMATRIXF& _outMatrix) = 0;
			virtual GReturn GetTranslation(GMATRIXF _matrix, GMATRIXF& _outMatrix) = 0;
			virtual GReturn GetScale(GMATRIXF _matrix, GMATRIXF& _outMatrix) = 0;
			virtual GReturn RotationX(GMATRIXF _matrix, float _radian, GMATRIXF& _outMatrix) = 0;
			virtual GReturn RotationY(GMATRIXF _matrix, float _radian, GMATRIXF& _outMatrix) = 0;
			virtual GReturn RotationZ(GMATRIXF _matrix, float _radian, GMATRIXF& _outMatrix) = 0;
			virtual GReturn Scaling(GMATRIXF _matrix, GVECTORF _vector, GMATRIXF& _outMatrix) = 0;
			virtual GReturn Translation(GMATRIXF _matrix, GVECTORF _vector, GMATRIXF& _outMatrix) = 0;

			//double Matrix
			virtual GReturn AdditionMatrix(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD& _outMatrix) = 0;
			virtual GReturn SubtractionMatrix(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD& _outMatrix) = 0;
			virtual GReturn MultiplyMatrix(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD& _outMatrix) = 0;
			virtual GReturn DivideMatrix(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD& _outMatrix) = 0;
			virtual GReturn MultiplyVector(GMATRIXD _matrix, GVECTORD _vector, GMATRIXD& _outMatrix) = 0;
			virtual GReturn MultiplyNormal(GMATRIXD _matrix, GVECTORD _vector, GMATRIXD& _outMatrix) = 0;
			virtual GReturn ConvertQuaternion(GQUATERNIOND _quaternion, GMATRIXD& _outMatrix) = 0;
			virtual GReturn MultiplyNum(GMATRIXD _matrix, double _num, GMATRIXD& _outMatrix) = 0;
			virtual GReturn DivideNum(GMATRIXD _matrix, double _num, GMATRIXD& _outMatrix) = 0;
			virtual GReturn DeterminantMatrix(GMATRIXD _matrix, GMATRIXD& _outMatrix) = 0;
			virtual GReturn TransposeMatrix(GMATRIXD _matrix, GMATRIXD& _outMatrix) = 0;
			virtual GReturn Inverse(GMATRIXD _matrix, GMATRIXD& _outMatrix) = 0;
			virtual GReturn Identity(GMATRIXD& _outMatrix) = 0;
			virtual GReturn GetRotation(GMATRIXD _matrix, GMATRIXD& _outMatrix) = 0;
			virtual GReturn GetTranslation(GMATRIXD _matrix, GMATRIXD& _outMatrix) = 0;
			virtual GReturn GetScale(GMATRIXD _matrix, GMATRIXD& _outMatrix) = 0;
			virtual GReturn RotationX(GMATRIXD _matrix, double _radian, GMATRIXD& _outMatrix) = 0;
			virtual GReturn RotationY(GMATRIXD _matrix, double _radian, GMATRIXD& _outMatrix) = 0;
			virtual GReturn RotationZ(GMATRIXD _matrix, double _radian, GMATRIXD& _outMatrix) = 0;
			virtual GReturn Scaling(GMATRIXD _matrix, GVECTORD _vector, GMATRIXD& _outMatrix) = 0;
			virtual GReturn Translation(GMATRIXD _matrix, GVECTORD _vector, GMATRIXD& _outMatrix) = 0;
		}; //! end GMatrix class

	};//! end SYSTEM namespace
} //! end GW namespace


#endif