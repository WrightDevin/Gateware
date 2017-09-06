#ifndef GVECTOR_H
#define GVECTOR_H
/*!
File: GVector.h
Purpose: A Gateware interface that handles all vector functions.
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
		//! Unique Identifier for this interface. {1C92F468-4121-46E8-B2D6-2E843BADD205}
		static const GUUIID GVectorUUIID =
		{
			0x1c92f468, 0x4121, 0x46e8,{ 0xb2, 0xd6, 0x2e, 0x84, 0x3b, 0xad, 0xd2, 0x5 }
		};

		//! Vector functions
		/*!
		*	Include float vector and double vector's functions
		*/
		class GVector : public GMathDefines
		{
		public:
			//float vector

			//! Add two vectors
			/*!
			*	Adds the two specified vectors and stores the result in the output vector.
			*
			*	\param [in]  _vector1		The first vector
			*	\param [in]  _vector2		The second vecotr
			*	\param [out] _outVector		The result of addition
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid vector was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn AddVector(GVECTORF _vector1, GVECTORF _vector2, GVECTORF& _outVector) = 0;

			//! Subtract two vector
			/*!
			*	Subtracts the two specified vectors and stores the result in the output vector.
			*
			*	\param [in]  _vector1		The first vector
			*	\param [in]  _vector2		The second vecotr
			*	\param [out] _outVector		The vector for store the result
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid vector was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn SubtractVector(GVECTORF _vector1, GVECTORF _vector2, GVECTORF& _outVector) = 0;

			//! Scale the vector
			/*!
			*	Scales all elements of the input vector by the specified value 
			*	and stores the result in the output vector.
			*
			*	\param [in]  _vector1		The first vector
			*	\param [in]  _scalar		The specified value to scale
			*	\param [out] _outVector		The vector for store the result
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid vector was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn Scale(GVECTORF _vector, float _scalar, GVECTORF& _outVector) = 0;
		
			//! Calculates the dot product of the two vectors
			/*!
			*	Calculates the dot product of two specified vectors and stores the result in the output Value.
			*
			*	\param [in]  _vector1		The first vector
			*	\param [in]  _vector2		The second vecotr
			*	\param [out] _outValue		The value of the dot product
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid vector was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn Dot(GVECTORF _vector1, GVECTORF _vector2, float& _outValue) = 0;

			//! Calculates the Cross product of the two vectors which are treated as 2 elements vector 
			/*!
			*	Calculates the cross product of two specified vectors which are treated as 2 elements vectors 
			*	and stores the result in the output value. The input vectors' z and w value will be ignored.
			*
			*	\param [in]  _vector1		The first vector
			*	\param [in]  _vector2		The second vecotr
			*	\param [out] _outValue		The value of 2D vecotrs' cross product
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid vector was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn CrossVector2(GVECTORF _vector1, GVECTORF _vector2, GVECTORF& _outVector) = 0;

			//! Calculates the cross product of the two vectors which are treated as 3 elements vectors. 
			/*!
			*	Calculates the cross product of two specified vectors which are treated as 2 elements vector
			*	and stores the result in the output vector. The input vectors' w value will be returned with 0.
			*
			*	\param [in]  _vector1		The first vector
			*	\param [in]  _vector2		The second vecotr
			*	\param [out] _outVector		The vector of 3D vectors' cross product
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid vector was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn CrossVector3(GVECTORF _vector1, GVECTORF _vector2, GVECTORF& _outVector) = 0;

			//! multiply the specified vector by the specified matrix.
			/*!
			*	Multiplies the specified vector by the specified matrix
			*	and stores the result in the output vector. The input vectors' w value will be returned with 0.
			*
			*	\param [in]  _vector		The input vector
			*	\param [in]  _matrix		The input matrix
			*	\param [out] _outVector		The result of multiplicataion
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid vector was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn VectorXMatrix(GVECTORF _vector, GMATRIXF _matrix, GVECTORF& _outVector) = 0;

			//! Transform specified specified vector by specified matrix.
			/*!
			*	Transforms the specified vector by the specified matrix by treating the fourth row as (0, 0, 0, 1).
			*	and stores the result in the output vector.
			*
			*	\param [in]  _vector		The specified vector
			*	\param [in]  _matrix		The transform matrix
			*	\param [out] _outVector		The result of the transformation
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid vector was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn TransformMatrix(GVECTORF _vector, GMATRIXF _matrix, GVECTORF& _outVector) = 0;
			
			//! Computes the magnitude of the specified vector.
			/*!
			*	Computes the magnitude of the specified vector,	and stores the result in the output value.
			*
			*	\param [in]  _vector		The specified vector
			*	\param [out] _outValue		The magnitude of the vector
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid vector was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn Magnitude(GVECTORF _vector, float& _outMagnitude) = 0;

			//! Normalizes the specified vector.
			/*!
			*	Normalizes the specified vector, and stores the result in the output vector.
			*
			*	\param [in]  _vector		The specified vector
			*	\param [out] _outVector		The result of the normalization.
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid vector was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn Normalize(GVECTORF _vector, GVECTORF& _outVector) = 0;

			//double vector

			//! Add two vectors
			/*!
			*	Adds the two specified vectors and stores the result in the output vector.
			*
			*	\param [in]  _vector1		The first vector
			*	\param [in]  _vector2		The second vecotr
			*	\param [out] _outVector		The result of addition
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid vector was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn AddVector(GVECTORD _vector1, GVECTORD _vector2, GVECTORD& _outVector) = 0;

			//! Subtract two vector
			/*!
			*	Subtracts the two specified vectors and stores the result in the output vector.
			*
			*	\param [in]  _vector1		The first vector
			*	\param [in]  _vector2		The second vecotr
			*	\param [out] _outVector		The vector for store the result
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid vector was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn SubtractVector(GVECTORD _vector1, GVECTORD _vector2, GVECTORD& _outVector) = 0;

			//! Scale the vector
			/*!
			*	Scales all elements of the input vector by the specified value
			*	and stores the result in the output vector.
			*
			*	\param [in]  _vector1		The first vector
			*	\param [in]  _scalar		The specified value to scale
			*	\param [out] _outVector		The vector for store the result
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid vector was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn Scale(GVECTORD _vector, double _scalar, GMATRIXD& _outMatrix) = 0;

			//! Calculates the dot product of the two vectors
			/*!
			*	Calculates the dot product of two specified vectors and stores the result in the output Value.
			*
			*	\param [in]  _vector1		The first vector
			*	\param [in]  _vector2		The second vecotr
			*	\param [out] _outValue		The value of the dot product
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid vector was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn Dot(GVECTORD _vector1, GVECTORD _vector2, double& _outValue) = 0;

			//! Calculates the Cross product of the two vectors which are treated as 2 elements vector 
			/*!
			*	Calculates the cross product of two specified vectors which are treated as 2 elements vectors
			*	and stores the result in the output value. The input vectors' z and w value will be ignored.
			*
			*	\param [in]  _vector1		The first vector
			*	\param [in]  _vector2		The second vecotr
			*	\param [out] _outValue		The value of 2D vecotrs' cross product
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid vector was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn CrossVec2(GVECTORD _vector1, GVECTORD _vector2, double& _outValue) = 0;

			//! multiply the specified vector by the specified matrix.
			/*!
			*	Multiplies the specified vector by the specified matrix
			*	and stores the result in the output vector. The input vectors' w value will be returned with 0.
			*
			*	\param [in]  _vector		The input vector
			*	\param [in]  _matrix		The input matrix
			*	\param [out] _outVector		The result of multiplicataion
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid vector was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn CrossVec3(GVECTORD _vector1, GVECTORD _vector2, GVECTORD& _outVector) = 0;

			//! multiply the specified vector by the specified matrix.
			/*!
			*	Multiplies the specified vector by the specified matrix
			*	and stores the result in the output vector. The input vectors' w value will be returned with 0.
			*
			*	\param [in]  _vector		The input vector
			*	\param [in]  _matrix		The input matrix
			*	\param [out] _outVector		The result of multiplicataion
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid vector was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn VectorXMatrix(GVECTORD _vector, GMATRIXD _matrix, GVECTORD& _outVector) = 0;

			//! Transform specified specified vector by specified matrix.
			/*!
			*	Transforms the specified vector by the specified matrix by treating the fourth row as (0, 0, 0, 1).
			*	and stores the result in the output vector.
			*
			*	\param [in]  _vector		The specified vector
			*	\param [in]  _matrix		The transform matrix
			*	\param [out] _outVector		The result of the transformation
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid vector was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn TransformMatrix(GVECTORD _vector, GMATRIXD _matrix, GVECTORD& _outVector) = 0;

			//! Computes the magnitude of the specified vector.
			/*!
			*	Computes the magnitude of the specified vector,	and stores the result in the output value.
			*
			*	\param [in]  _vector		The specified vector
			*	\param [out] _outValue		The magnitude of the vector
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid vector was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn Magnitude(GVECTORD _vector, float& _outMagnitude) = 0;

			//! Normalizes the specified vector.
			/*!
			*	Normalizes the specified vector, and stores the result in the output vector.
			*
			*	\param [in]  _vector		The specified vector
			*	\param [out] _outVector		The result of the normalization.
			*
			*	\retval SUCCESS				The calculation succeed
			*	\retval INVALID_ARGUMENT	An invalid vector was passed in
			*	\retval FAILURE				The calculation failed
			*/
			virtual GReturn Normalize(GVECTORD _vector, GVECTORD& _outVector) = 0;

		}; //! end GVector class

	};//! end SYSTEM namespace
} //! end GW namespace


#endif