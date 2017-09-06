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
	//! The namespace to which all math library interface must belong.
	namespace MATH
	{
		//! Unique Identifier for this interface. {7FD30A77-340C-485B-9B32-F1EFA3717331}
		static const GUUIID GMatrixUUIID =
		{
			0x7fd30a77, 0x340c, 0x485b,{ 0x9b, 0x32, 0xf1, 0xef, 0xa3, 0x71, 0x73, 0x31 }
		};

		//! Matrix functions
		/*!
		*	Include float vector and double matrix's functions
		*/
		class GMatrix : public GMathDefines
		{
		public:
			//float Matrix

			//! Add two specified matirxs
			/*!
			*	Adds the two specified matirxs and stores the result in the output matirx.
			*
			*	\param [in]  _matrix1		The first matrix
			*	\param [in]  _matrix2		The second matrix
			*	\param [out] _outVector		The result of addition
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid matrix was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn AddMatrix(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF& _outMatrix) = 0;
			
			//! Subtract two specified matirxs
			/*!
			*	Subtracts the two specified matirxs and stores the result in the output matirx.
			*
			*	\param [in]  _matrix1		The first matrix
			*	\param [in]  _matrix2		The second matrix
			*	\param [out] _outVector		The result of subtraction
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid matrix was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn SubtractMatrix(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF& _outMatrix) = 0;
			
			//! Multiply two specified matirxs
			/*!
			*	Multiplies the two specified matirxs and stores the result in the output matirx.
			*
			*	\param [in]  _matrix1		The first matrix
			*	\param [in]  _matrix2		The second matrix
			*	\param [out] _outVector		The result of Multiplication
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid matrix was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn MultiplyMatrix(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF& _outMatrix) = 0;
			
			//! Multiply the specified matrix by the specified vector.
			/*!
			*	Multiplies the specified matrix by the specified vector
			*	and stores the result in the output vector.
			*	The input vectors' w value will be returned with 0.
			*
			*	\param [in]  _matrix		The input matrix
			*	\param [in]  _vector		The input vector
			*	\param [out] _outVector		The result of multiplicataion
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid matrix or vector was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn MatrixXVector(GMATRIXF _matrix, GVECTORF _vector, GVECTORF& _outVector) = 0;


			//virtual GReturn MultiplyNormal(GMATRIXF _matrix, GVECTORF _vector, GMATRIXF& _outMatrix) = 0;
			
			//! Convert the specified quaternion to a matrix
			/*!
			*	Converts the specified quaternion to a matrix and stores the result in the output matrix.
			*
			*	\param [in]  _quaternion		The specified quaternion
			*	\param [out] _outMatrix			The result of the convert
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn ConvertQuaternion(GQUATERNIONF _quaternion, GMATRIXF& _outMatrix) = 0;

			//! Scale the matrix
			/*!
			*	Scales the specified matrix with a number and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The matirx
			*	\param [in]  _scalar				The specified value to scale
			*	\param [out] _outMatrix			The result of the scaling
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn MultiplyNum(GMATRIXF _matrix, float _scalar, GMATRIXF& _outMatrix) = 0;

			//! Calculate the determinant of the specified matirx
			/*!
			*	Calculates the determinant of the specified matirx and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matirx
			*	\param [out] _outMatrix			The result of the determinant
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn Determinant(GMATRIXF _matrix, GMATRIXF& _outMatrix) = 0;

			//! Transpose the specified matirx
			/*!
			*	Transposes the specified matirx and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matirx
			*	\param [out] _outMatrix			The result of the transpose
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn Transpose(GMATRIXF _matrix, GMATRIXF& _outMatrix) = 0;

			//! Inverse the specified matirx
			/*!
			*	Inverses the specified matirx and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matirx
			*	\param [out] _outMatrix			The result of the inverse
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn Inverse(GMATRIXF _matrix, GMATRIXF& _outMatrix) = 0;

			//! Identity the specified matrix
			/*!
			*	Identities the specified matrix and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [out] _outMatrix			The result of the identity
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn Identity(GMATRIXF _matrix, GMATRIXF& _outMatrix) = 0;

			//! Get the rotation matrix from the specified matrix
			/*!
			*	Gets the rotation matrix from the specified matrix
			*	and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [out] _outMatrix			The rotation matirx of the specified matirx
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn GetRotation(GMATRIXF _matrix, GMATRIXF& _outMatrix) = 0;

			//! Get the translation matrix from the specified matrix
			/*!
			*	Gets the translation matrix from the specified matrix
			*	and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [out] _outMatrix			The translation matirx of the specified matirx
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn GetTranslation(GMATRIXF _matrix, GMATRIXF& _outMatrix) = 0;

			//! Get the scaling matrix from the specified matrix
			/*!
			*	Gets the scaling matrix from the specified matrix
			*	and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [out] _outMatrix			The scaling matirx of the specified matirx
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn GetScale(GMATRIXF _matrix, GMATRIXF& _outMatrix) = 0;

			//! Roatate the specified matrix around the x-axis by multiplying a rotation matrix
			/*!
			*	Roatate the specified matrix around the x-axis by multiplying a rotation matrix
			*	and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [in]  _radian			The radian to rotate
			*	\param [out] _outMatrix			The result of the rotation
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn RotationX(GMATRIXF _matrix, float _radian, GMATRIXF& _outMatrix) = 0;

			//! Roatate the specified matrix around the y-axis by multiplying a rotation matrix
			/*!
			*	Roatate the specified matrix around the y-axis by multiplying a rotation matrix
			*	and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [in]  _radian			The radian to rotate
			*	\param [out] _outMatrix			The result of the rotation
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn RotationY(GMATRIXF _matrix, float _radian, GMATRIXF& _outMatrix) = 0;

			//! Roatate the specified matrix around the z-axis by multiplying a rotation matrix
			/*!
			*	Roatate the specified matrix around the z-axis by multiplying a rotation matrix
			*	and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [in]  _radian			The radian to rotate
			*	\param [out] _outMatrix			The result of the rotation
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn RotationZ(GMATRIXF _matrix, float _radian, GMATRIXF& _outMatrix) = 0;

			//! Translate the matrix by the specified vector
			/*!
			*	Translates the matrix by the specified vector
			*	and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [in]  _vector			The vector to translate
			*	\param [out] _outMatrix			The result of the trasnlation
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn Translate(GMATRIXF _matrix, GVECTORF _vector, GMATRIXF& _outMatrix) = 0;


			//! Scale the matrix by the specified vector
			/*!
			*	Scales the matrix by the specified vector
			*	and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [in]  _vector			The vector to scale
			*	\param [out] _outMatrix			The result of the scaling
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn  Scaling(GMATRIXF _matrix, GVECTORF _vector, GMATRIXF& _outMatirx) = 0;



			//double Matrix

			//! Add two specified matirxs
			/*!
			*	Adds the two specified matirxs and stores the result in the output matirx.
			*
			*	\param [in]  _matrix1		The first matrix
			*	\param [in]  _matrix2		The second matrix
			*	\param [out] _outVector		The result of addition
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid matrix was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn  AddMatrix(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD& _outMatrix) = 0;
			
			//! Subtract two specified matirxs
			/*!
			*	Subtracts the two specified matirxs and stores the result in the output matirx.
			*
			*	\param [in]  _matrix1		The first matrix
			*	\param [in]  _matrix2		The second matrix
			*	\param [out] _outVector		The result of subtraction
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid matrix was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn  SubtractMatrix(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD& _outMatrix) = 0;

			//! Multiply two specified matirxs
			/*!
			*	Multiplies the two specified matirxs and stores the result in the output matirx.
			*
			*	\param [in]  _matrix1		The first matrix
			*	\param [in]  _matrix2		The second matrix
			*	\param [out] _outVector		The result of Multiplication
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid matrix was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn  MultiplyMatrix(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD& _outMatrix) = 0;
		

			//! Multiply the specified matrix by the specified vector.
			/*!
			*	Multiplies the specified matrix by the specified vector
			*	and stores the result in the output vector.
			*	The input vectors' w value will be returned with 0.
			*
			*	\param [in]  _matrix		The input matrix
			*	\param [in]  _vector		The input vector
			*	\param [out] _outVector		The result of multiplicataion
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid matrix or vector was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn MatrixXVector(GMATRIXD _matrix, GMATRIXD _vector, GMATRIXD& _outVector) = 0;

			//virtual GReturn MultiplyNormal(GMATRIXF _matrix, GVECTORF _vector, GMATRIXF& _outMatrix) = 0;

			//! Convert the specified quaternion to a matrix
			/*!
			*	Converts the specified quaternion to a matrix and stores the result in the output matrix.
			*
			*	\param [in]  _quaternion		The specified quaternion
			*	\param [out] _outMatrix			The result of the convert
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn ConvertQuaternion(GQUATERNIOND _quaternion, GMATRIXD& _outMatrix) = 0;

			//! Scale the matrix
			/*!
			*	Scales the specified matrix with a number and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The matirx
			*	\param [in]  _scalar				The specified value to scale
			*	\param [out] _outMatrix			The result of the scaling
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn MultiplyNum(GMATRIXD _matrix, double _scalar, GMATRIXD& _outMatrix) = 0;

			//! Calculate the determinant of the specified matirx
			/*!
			*	Calculates the determinant of the specified matirx and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matirx
			*	\param [out] _outMatrix			The result of the determinant
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn Determinant(GMATRIXD _matrix, GMATRIXD& _outMatrix) = 0;

			//! Transpose the specified matirx
			/*!
			*	Transposes the specified matirx and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matirx
			*	\param [out] _outMatrix			The result of the transpose
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn Transpose(GMATRIXD _matrix, GMATRIXD& _outMatrix) = 0;

			//! Inverse the specified matirx
			/*!
			*	Inverses the specified matirx and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matirx
			*	\param [out] _outMatrix			The result of the inverse
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn Inverse(GMATRIXD _matrix, GMATRIXD& _outMatrix) = 0;

			//! Identity the specified matrix
			/*!
			*	Identities the specified matrix and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [out] _outMatrix			The result of the identity
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn Identity(GMATRIXD _matrix, GMATRIXD& _outMatrix) = 0;

			//! Get the rotation matrix from the specified matrix
			/*!
			*	Gets the rotation matrix from the specified matrix
			*	and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [out] _outMatrix			The rotation matirx of the specified matirx
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn GetRotation(GMATRIXD _matrix, GMATRIXD& _outMatrix) = 0;

			//! Get the translation matrix from the specified matrix
			/*!
			*	Gets the translation matrix from the specified matrix
			*	and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [out] _outMatrix			The translation matirx of the specified matirx
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn GetTranslation(GMATRIXD _matrix, GMATRIXD& _outMatrix) = 0;

			//! Get the scaling matrix from the specified matrix
			/*!
			*	Gets the scaling matrix from the specified matrix
			*	and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [out] _outMatrix			The scaling matirx of the specified matirx
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn GetScale(GMATRIXD _matrix, GMATRIXD& _outMatrix) = 0;

			//! Roatate the specified matrix around the x-axis by multiplying a rotation matrix
			/*!
			*	Roatate the specified matrix around the x-axis by multiplying a rotation matrix
			*	and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [in]  _radian			The radian to rotate
			*	\param [out] _outMatrix			The result of the rotation
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn RotationX(GMATRIXD _matrix, double _radian, GMATRIXD& _outMatrix) = 0;

			//! Roatate the specified matrix around the y-axis by multiplying a rotation matrix
			/*!
			*	Roatate the specified matrix around the y-axis by multiplying a rotation matrix
			*	and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [in]  _radian			The radian to rotate
			*	\param [out] _outMatrix			The result of the rotation
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn RotationY(GMATRIXD _matrix, double _radian, GMATRIXD& _outMatrix) = 0;

			//! Roatate the specified matrix around the z-axis by multiplying a rotation matrix
			/*!
			*	Roatate the specified matrix around the z-axis by multiplying a rotation matrix
			*	and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [in]  _radian			The radian to rotate
			*	\param [out] _outMatrix			The result of the rotation
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn RotationZ(GMATRIXD _matrix, double _radian, GMATRIXD& _outMatrix) = 0;

			//! Translate the matrix by the specified vector
			/*!
			*	Translates the matrix by the specified vector
			*	and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [in]  _vector			The vector to translate
			*	\param [out] _outMatrix			The result of the trasnlation
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn Translate(GMATRIXD _matrix, GVECTORD _vector, GMATRIXD& _outMatrix) = 0;


			//! Scale the matrix by the specified vector
			/*!
			*	Scales the matrix by the specified vector
			*	and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [in]  _vector			The vector to scale
			*	\param [out] _outMatrix			The result of the scaling
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn  Scaling(GMATRIXD _matrix, GVECTORD _vector, GMATRIXD& _outMatirx) = 0;

			
		}; //! end GMatrix class

	};//! end SYSTEM namespace
} //! end GW namespace


#endif