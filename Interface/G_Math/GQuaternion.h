#ifndef GQUATERNION_H
#define GQUATERNION_H
/*!
File: GQuaternion.h
Purpose: A Gateware interface that handles quaternion functions.
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
		//! Unique Identifier for this interface. {1B42F04F-5A3F-40C5-A506-479768629014}
		static const GUUIID GQuaternionUUIID =
		{
			0x1b42f04f, 0x5a3f, 0x40c5,{ 0xa5, 0x6, 0x47, 0x97, 0x68, 0x62, 0x90, 0x14 }
		};

		class GQuaternion : public CORE::GMultiThreaded
		{
		public:
			//float quaternion
			virtual GReturn AdditionQuaternion(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GQUATERNIONF& _outQuaternion) = 0;
			virtual GReturn SubtractionQuaternion(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GQUATERNIONF& _outQuaternion) = 0;
			virtual GReturn MultiplyQuaternion(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GQUATERNIONF& _outQuaternion) = 0;
			virtual GReturn DivideQuaternion(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GQUATERNIONF& _outQuaternion) = 0;
			virtual GReturn MultiplyVector(GQUATERNIONF _quaternion, GVECTORF _vector, GQUATERNIONF& _outQuaternion) = 0;
			virtual GReturn RotationVector(GQUATERNIONF _quaternion, GVECTORF _vector, float _angle, GQUATERNIONF& _outQuaternion) = 0;
			virtual GReturn RotationMatrix(GQUATERNIONF _quaternion, GMATRIXF _matrix, GQUATERNIONF& _outQuaternion) = 0;
			virtual GReturn Dot(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GQUATERNIONF& _outQuaternion) = 0;
			virtual GReturn Cross(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GQUATERNIONF& _outQuaternion) = 0;
			virtual GReturn Conjugate(GQUATERNIONF _quaternion, GQUATERNIONF& _outQuaternion) = 0;
			virtual GReturn Reciprocal(GQUATERNIONF _quaternion, GQUATERNIONF& _outQuaternion) = 0;
			virtual GReturn Magnitude(GQUATERNIONF _quaternion, float& _outMagnitude) = 0;
			virtual GReturn Normalize(GQUATERNIONF _quaternion, GQUATERNIONF& _outQuaternion) = 0;
			virtual GReturn Identity(GQUATERNIONF _quaternion, GQUATERNIONF _outQuaternion) = 0;
			virtual GReturn ConvertMatrix(GMATRIXF _matrix, GQUATERNIONF& _outQuaternion) = 0;
			virtual GReturn ConvertMatrix(GMATRIXF _matrix, GQUATERNIONF& _outQuaternion) = 0;

			//double quaternion
			virtual GReturn AdditionQuaternion(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND& _outQuaternion) = 0;
			virtual GReturn SubtractionQuaternion(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND& _outQuaternion) = 0;
			virtual GReturn MultiplyQuaternion(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND& _outQuaternion) = 0;
			virtual GReturn DivideQuaternion(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND& _outQuaternion) = 0;
			virtual GReturn MultiplyVector(GQUATERNIOND _quaternion, GVECTORD _vector, GQUATERNIOND& _outQuaternion) = 0;
			virtual GReturn RotationVector(GQUATERNIOND _quaternion, GVECTORD _vector, double _angle, GQUATERNIOND& _outQuaternion) = 0;
			virtual GReturn RotationMatrix(GQUATERNIOND _quaternion, GMATRIXD _matrix, GQUATERNIOND& _outQuaternion) = 0;
			virtual GReturn Dot(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND& _outQuaternion) = 0;
			virtual GReturn Cross(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND& _outQuaternion) = 0;
			virtual GReturn Conjugate(GQUATERNIOND _quaternion, GQUATERNIOND& _outQuaternion) = 0;
			virtual GReturn Reciprocal(GQUATERNIOND _quaternion, GQUATERNIOND& _outQuaternion) = 0;
			virtual GReturn Magnitude(GQUATERNIOND _quaternion, double& _outMagnitude) = 0;
			virtual GReturn Normalize(GQUATERNIOND _quaternion, GQUATERNIOND& _outQuaternion) = 0;
			virtual GReturn Identity(GQUATERNIOND _quaternion, GQUATERNIOND _outQuaternion) = 0;
			virtual GReturn ConvertMatrix(GMATRIXD _matrix, GQUATERNIOND& _outQuaternion) = 0;

		}; //! end GQuaternion class

	};//! end SYSTEM namespace
} //! end GW namespace


#endif