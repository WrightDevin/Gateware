#ifndef GVECTOR_H
#define GVECTOR_H
/*!
File: GVector.h
Purpose: A Gateware interface that handles vector functions.
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
		//! Unique Identifier for this interface. {1C92F468-4121-46E8-B2D6-2E843BADD205}
		static const GUUIID GVectorUUIID =
		{
			0x1c92f468, 0x4121, 0x46e8,{ 0xb2, 0xd6, 0x2e, 0x84, 0x3b, 0xad, 0xd2, 0x5 }
		};

		class GVector : public CORE::GMultiThreaded
		{
		public:
			//float vector
			virtual GReturn AdditionVector(GVECTORF _vector1, GVECTORF _vector2, GVECTORF& _outVector) = 0;
			virtual GReturn SubtractionVector(GVECTORF _vector1, GVECTORF _vector2, GVECTORF& _outVector) = 0;

			virtual GReturn MultiplyNum(GVECTORF _vector, float _scale, GMATRIXF& _outMatrix) = 0;
			virtual GReturn DivideNum(GVECTORF _vector, float _scale, GMATRIXF& _outMatrix) = 0;

			virtual GReturn Dot(GVECTORF _vector1, GVECTORF _vector2, float& _outValue) = 0;
			virtual GReturn Cross(GVECTORF _vector1, GVECTORF _vector2, GVECTORF& _outVector) = 0;


			virtual GReturn MultiplyMatrix(GVECTORF _vector, GMATRIXF _matrix, GVECTORF& _outVector) = 0;
			virtual GReturn TransformMatrix(GVECTORF _vector, GMATRIXF _matrix, GVECTORF& _outVector) = 0;


			virtual GReturn Magnitude(GVECTORF _vector, float& _outMagnitude) = 0;
			virtual GReturn Normalize(GVECTORF& _outVector) = 0;
			
			//double vector
			virtual GReturn AdditionVector(GVECTORD _vector1, GVECTORD _vector2, GVECTORD& _outVector) = 0;
			virtual GReturn SubtractionVector(GVECTORD _vector1, GVECTORD _vector2, GVECTORD& _outVector) = 0;

			virtual GReturn MultiplyNum(GVECTORD _vector, double _scale, GMATRIXD& _outMatrix) = 0;
			virtual GReturn DivideNum(GVECTORD _vector, double _scale, GMATRIXD& _outMatrix) = 0;

			virtual GReturn Dot(GVECTORD _vector1, GVECTORD _vector2, float& _outValue) = 0;
			virtual GReturn Cross(GVECTORD _vector1, GVECTORD _vector2, GVECTORD& _outVector) = 0;

			virtual GReturn MultiplyMatrix(GVECTORD _vector, GMATRIXD _matrix, GVECTORD& _outVector) = 0;
			virtual GReturn TransformMatrix(GVECTORD _vector, GMATRIXD _matrix, GVECTORD& _outVector) = 0;

			virtual GReturn Magnitude(GVECTORD _vector, float& _outMagnitude) = 0;
			virtual GReturn Normalize(GVECTORD& _outVector) = 0;

		}; //! end GVector class

	};//! end SYSTEM namespace
} //! end GW namespace


#endif