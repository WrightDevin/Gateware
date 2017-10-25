#ifndef GMATRIX_H
#define GMATRIX_H
/*!
File: GMatrix.h
Purpose: A Gateware interface that handles Martix functions.
Author: Shuo-Yi Chang
Contributors: N/A
Last Modified: 10/18/2016
Interface Status: Beta
Copyright: 7thGate Software LLC.
License: MIT
*/

//! GMathDefines inherits directly from GMultiThreaded.
#include "../G_Core/GSingleThreaded.h"
#include "GMathDefines.h"

//! The core namespace to which all Gateware interfaces/structures/defines must belong.
namespace GW
{
	//! The namespace to which all math library interface must belong.
	namespace MATH
	{
		//! Unique Identifier for this interface. {AD50013E-94F3-40B6-8FB9-715635F0B8FE}
		static const GUUIID GMatrixUUIID =
		{
			0xad50013e, 0x94f3, 0x40b6,{ 0x8f, 0xb9, 0x71, 0x56, 0x35, 0xf0, 0xb8, 0xfe }
		};

		//! Matrix functions
		/*!
		*	Include float vector and double matrix's functions
		*/
		class GMatrix : public CORE::GSingleThreaded
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
			virtual GReturn AddMatrixF(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF& _outMatrix) = 0;
			
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
			virtual GReturn SubtractMatrixF(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF& _outMatrix) = 0;
			
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
			virtual GReturn MultiplyMatrixF(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF& _outMatrix) = 0;
			
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
			virtual GReturn VectorXMatrixF(GMATRIXF _matrix, GVECTORF _vector, GVECTORF& _outVector) = 0;
			
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
			virtual GReturn ConvertQuaternionF(GQUATERNIONF _quaternion, GMATRIXF& _outMatrix) = 0;

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
			virtual GReturn MultiplyNumF(GMATRIXF _matrix, float _scalar, GMATRIXF& _outMatrix) = 0;

			//! Calculate the determinant of the specified matirx
			/*!
			*	Calculates the determinant of the specified matirx and stores the result in the output value.
			*
			*	\param [in]  _matrix			The specified matirx
			*	\param [out] _outValue			The result of the determinant
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn DeterminantF(GMATRIXF _matrix, float& _outValue) = 0;

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
			virtual GReturn TransposeF(GMATRIXF _matrix, GMATRIXF& _outMatrix) = 0;

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
			virtual GReturn InverseF(GMATRIXF _matrix, GMATRIXF& _outMatrix) = 0;

			//! Identity the specified matrix
			/*!
			*	Set the output matrix as an identity matrix
			*
			*	\param [out] _outMatrix			The result of the identity
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn IdentityF(GMATRIXF& _outMatrix) = 0;

			//! Get the quaternion which represents the roataion of the specified matrix
			/*!
			*	Get the quaternion which represents the roataion of the specified matrix
			*	and stores the result in the output quaternion.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [out] _quaternion		The quaternion of the specified matirx
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn GetRotationF(GMATRIXF _matrix, GQUATERNIONF& _outQuaternion) = 0;

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
			virtual GReturn GetTranslationF(GMATRIXF _matrix, GVECTORF& _outMatrix) = 0;

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
			virtual GReturn GetScaleF(GMATRIXF _matrix, GVECTORF& _outMatrix) = 0;

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
			virtual GReturn RotationXF(GMATRIXF _matrix, float _radian, GMATRIXF& _outMatrix) = 0;

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
			virtual GReturn RotationYF(GMATRIXF _matrix, float _radian, GMATRIXF& _outMatrix) = 0;

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
			virtual GReturn RotationZF(GMATRIXF _matrix, float _radian, GMATRIXF& _outMatrix) = 0;

			//! Builds a matrix based on specified yaw, pitch, and roll angles in radian. 
			/*!
			*	Uses Left-handed coordinate system to build the rotation matrix. 
			*	Angles are measured clockwise when looking along the rotation axis toward the origin.
			*	The mathematic formula will like: Mat_Rotation = ( Mat_Roll * ( Mat_Pitch * Mat_Yaw))
			*
			*	\param [in]  _pitch				Angle of rotation around the x-axis, in radians.
			*	\param [in]  _yaw				Angle of rotation around the y-axis, in radians.
			*	\param [in]  _roll				Angle of rotation around the z-axis, in radians.
			*	\param [out] _outMatrix			The result of the rotation
			*
			*	\retval SUCCESS					The building succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The building failed
			*/
			virtual GReturn RotationYawPitchRollF(float _pitch, float _yaw, float _roll, GMATRIXF& _outMatrix) = 0;

			//! Translate the matrix by the specified vector
			/*!
			*	Translates the matrix by the specified vector
			*	and stores the result in the output matrix.
			*	The translation values along the x, y and z axes.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [in]  _vector			The vector to translate
			*	\param [out] _outMatrix			The result of the trasnlation
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn TranslatelocalF(GMATRIXF _matrix, GVECTORF _vector, GMATRIXF& _outMatrix) = 0;

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
			virtual GReturn  ScalingF(GMATRIXF _matrix, GVECTORF _vector, GMATRIXF& _outMatirx) = 0;

			//! Linearly interpolates between two matrices.
			/*!
			*	Linearly interpolates between two matrices
			*	and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The first matrix
			*	\param [in]  _matrix			The second matrix
			*	\param [in]  _ratio				The interpolation coefficient
			*	\param [out] _outMatrix			The result of the scaling
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn  LerpF(GMATRIXF _matrix1, GMATRIXF _matrix2, float _ratio, GMATRIXF& _outMatrix) = 0;

			//! Builds a left-handed perspective matrix
			/*!
			*	Builds a left-handed perspective matrix
			*
			*	\param [in]  _fieldOfView		Field of view in the y direction, in radians
			*	\param [in]  _aspect			Aspect ratio, defined as view space width divided by height
			*	\param [in]  _zn				Z-value of the near view-plane
			*	\param [in]  _zf				Z-value of the far view-plane
			*	\param [out] _outMatrix			The result of the projection matrix
			*
			*	\retval SUCCESS					The building succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The building failed
			*/
			virtual GReturn ProjectionLHF(float _fovY, float _aspect, float _zn, float _zf, GMATRIXF& _outMatrix) = 0;

			//! Builds a left-handed view matrix
			/*!
			*	Builds a left-handed view matrix
			*
			*	\param [in]  _eye				The position of eye
			*	\param [in]  _at				The position of the camera look-at target
			*	\param [in]  _out				The direction of the world's up
			*	\param [out] _outMatrix			The result of the look-at matrix
			*
			*	\retval SUCCESS					The building succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The building failed
			*/
			virtual GReturn LookAtLHF(GVECTORF _eye, GVECTORF _at, GVECTORF _up, GMATRIXF& _outMatrix) = 0;


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
			virtual GReturn  AddMatrixD(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD& _outMatrix) = 0;
			
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
			virtual GReturn  SubtractMatrixD(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD& _outMatrix) = 0;

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
			virtual GReturn  MultiplyMatrixD(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD& _outMatrix) = 0;
		

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
			virtual GReturn VectorXMatrixD(GMATRIXD _matrix, GVECTORD _vector, GVECTORD& _outVector) = 0;

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
			virtual GReturn ConvertQuaternionD(GQUATERNIOND _quaternion, GMATRIXD& _outMatrix) = 0;

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
			virtual GReturn MultiplyNumD(GMATRIXD _matrix, double _scalar, GMATRIXD& _outMatrix) = 0;

			//! Calculate the determinant of the specified matirx
			/*!
			*	Calculates the determinant of the specified matirx and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The specified matirx
			*	\param [out] _outValue			The result of the determinant
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn DeterminantD(GMATRIXD _matrix, double& _outValue) = 0;

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
			virtual GReturn TransposeD(GMATRIXD _matrix, GMATRIXD& _outMatrix) = 0;

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
			virtual GReturn InverseD(GMATRIXD _matrix, GMATRIXD& _outMatrix) = 0;

			//! Identity the specified matrix
			/*!
			*	Set the output matrix as an identity matrix
			*
			*	\param [out] _outMatrix			The result of the identity
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn IdentityD(GMATRIXD& _outMatrix) = 0;

			//! Get the quaternion which represents the roataion of the specified matrix
			/*!
			*	Get the quaternion which represents the roataion of the specified matrix
			*	and stores the result in the output quaternion.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [out] _quaternion		The quaternion of the specified matirx
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn GetRotationD(GMATRIXD _matrix, GQUATERNIOND& _outQuaternion) = 0;

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
			virtual GReturn GetTranslationD(GMATRIXD _matrix, GVECTORD& _outMatrix) = 0;

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
			virtual GReturn GetScaleD(GMATRIXD _matrix, GVECTORD& _outMatrix) = 0;

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
			virtual GReturn RotationXD(GMATRIXD _matrix, double _radian, GMATRIXD& _outMatrix) = 0;

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
			virtual GReturn RotationYD(GMATRIXD _matrix, double _radian, GMATRIXD& _outMatrix) = 0;

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
			virtual GReturn RotationZD(GMATRIXD _matrix, double _radian, GMATRIXD& _outMatrix) = 0;

			//! Builds a matrix based on specified yaw, pitch, and roll angles in radian. 
			/*!
			*	Uses Left-handed coordinate system to build the rotation matrix.
			*	Angles are measured clockwise when looking along the rotation axis toward the origin.
			*
			*	\param [in]  _pitch				Angle of rotation around the x-axis, in radians.
			*	\param [in]  _yaw				Angle of rotation around the y-axis, in radians.
			*	\param [in]  _roll				Angle of rotation around the z-axis, in radians.
			*	\param [out] _outMatrix			The result of the rotation
			*
			*	\retval SUCCESS					The building succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The building failed
			*/
			virtual GReturn RotationYawPitchRollD(double _pitch, double _yaw, double _roll, GMATRIXD& _outMatrix) = 0;

			//! Translate the matrix by the specified vector
			/*!
			*	Translates the matrix by the specified vector
			*	and stores the result in the output matrix.
			*	The translation values along the x, y and z axes.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [in]  _vector			The vector to translate
			*	\param [out] _outMatrix			The result of the trasnlation
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn TranslatelocalD(GMATRIXD _matrix, GVECTORD _vector, GMATRIXD& _outMatrix) = 0;


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
			virtual GReturn  ScalingD(GMATRIXD _matrix, GVECTORD _vector, GMATRIXD& _outMatrix) = 0;

			//! Linearly interpolates between two matrices.
			/*!
			*	Linearly interpolates between two matrices
			*	and stores the result in the output matrix.
			*
			*	\param [in]  _matrix			The first matrix
			*	\param [in]  _matrix			The second matrix
			*	\param [in]  _ratio				The interpolation coefficient
			*	\param [out] _outMatrix			The result of the scaling
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn  LerpD(GMATRIXD _matrix1, GMATRIXD _matrix2, double _ratio, GMATRIXD& _outMatrix) = 0;

			//! Builds a left-handed perspective matrix
			/*!
			*	Builds a left-handed perspective matrix
			*
			*	\param [in]  _fieldOfView		Field of view in the y direction, in radians
			*	\param [in]  _aspect			Aspect ratio, defined as view space width divided by height
			*	\param [in]  _zn				Z-value of the near view-plane
			*	\param [in]  _zf				Z-value of the far view-plane
			*	\param [out] _outMatrix			The result of the projection matrix
			*
			*	\retval SUCCESS					The building succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The building failed
			*/
			virtual GReturn ProjectionLHD(double _fovY, double _aspect, double _zn, double _zf, GMATRIXD& _outMatrix) = 0;
			
			//! Builds a left-handed view matrix
			/*!
			*	Builds a left-handed view matrix
			*
			*	\param [in]  _eye				The position of eye
			*	\param [in]  _at				The position of the camera look-at target
			*	\param [in]  _out				The direction of the world's up
			*	\param [out] _outMatrix			The result of the look-at matrix
			*
			*	\retval SUCCESS					The building succeed
			*	\retval INVALID_ARGUMENT		An invalid matrix was passed in
			*	\retval FAILURE					The building failed
			*/
			virtual GReturn LookAtLHD(GVECTORD _eye, GVECTORD _at, GVECTORD _up, GMATRIXD& _outMatrix) = 0;
			
		}; //! end GMatrix class
		

		GATEWARE_EXPORT_IMPLICIT GReturn CreateGMatrix(GMatrix** _outMatrix);
	};//! end SYSTEM namespace
} //! end GW namespace


#endif