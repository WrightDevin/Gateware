// Override export symbols for DLL builds (must be included before interface code).
#include "../DLL_Export_Symbols.h"


#include "../../Interface/G_Math/GQuaternion.h"

//The using statements for specifically what we are using.
using namespace GW;

class GQuaternionCpp : public::GW::MATH::GQuaternion
{
public:
	GQuaternionCpp();
	~GQuaternionCpp();
	
	//float quaternion

	GReturn AddQuaternion(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GQUATERNIONF& _outQuaternion) override;

	GReturn SubtractQuaternion(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GQUATERNIONF& _outQuaternion) override;

	GReturn MultiplyQuaternion(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GQUATERNIONF& _outQuaternion) override;

	GReturn Scale(GQUATERNIONF _quaternion, float _scalar, GQUATERNIONF& _outQuaternion) override;

	GReturn SetbyVectorAngle(GVECTORF _vector, float _angle, GQUATERNIONF& _outQuaternion) override;

	GReturn SetbyMatrix(GMATRIXF _matrix, GQUATERNIONF& _outQuaternion) override;

	GReturn Dot(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, float& _outValue) override;

	GReturn Cross(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GVECTORF& _outVector) override;

	GReturn Conjugate(GQUATERNIONF _quaternion, GQUATERNIONF& _outQuaternion) override;

	GReturn Inverse(GQUATERNIONF _quaternion, GQUATERNIONF& _outQuaternion) override;

	GReturn Magnitude(GQUATERNIONF _quaternion, float& _outMagnitude) override;

	GReturn Normalize(GQUATERNIONF _quaternion, GQUATERNIONF& _outQuaternion) override;

	GReturn Identity(GQUATERNIONF _quaternion, GQUATERNIONF _outQuaternion) override;

	GReturn Lerp(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, float _ratio, GQUATERNIONF& _outQuaternion) override;

	GReturn ConvertMatrix(GMATRIXF _matrix, GQUATERNIONF& _outQuaternion) override;

	GReturn Slerp(GMATRIXF _matrix, GQUATERNIONF& _outQuaternion) override;

	//double quaternion
	
	GReturn AddQuaternion(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND& _outQuaternion) override;

	GReturn SubtractQuaternion(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND& _outQuaternion) override;

	GReturn MultiplyQuaternion(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND& _outQuaternion) override;

	GReturn Scale(GQUATERNIOND _quaternion, GQUATERNIOND _quaternion2, GQUATERNIONF& _outQuaternion) override;

	GReturn SetByVectorAngle(GQUATERNIOND _quaternion, GVECTORD _vector, double _angle, GQUATERNIOND& _outQuaternion) override;

	GReturn SetByMatrix(GQUATERNIOND _quaternion, GMATRIXD _matrix, GQUATERNIOND& _outQuaternion) override;

	GReturn Dot(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND& _outQuaternion) override;

	GReturn Cross(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND& _outQuaternion) override;

	GReturn Conjugate(GQUATERNIOND _quaternion, GQUATERNIOND& _outQuaternion) override;

	GReturn Inverse(GQUATERNIOND _quaternion, GQUATERNIOND& _outQuaternion) override;

	GReturn Magnitude(GQUATERNIOND _quaternion, double& _outMagnitude) override;

	GReturn Normalize(GQUATERNIOND _quaternion, GQUATERNIOND& _outQuaternion) override;

	GReturn Identity(GQUATERNIOND _quaternion, GQUATERNIOND _outQuaternion) override;

	GReturn Lerp(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, float _ratio, GQUATERNIOND& _outQuaternion) override;

	GReturn ConvertMatrix(GMATRIXD _matrix, GQUATERNIOND& _outQuaternion) override;

	GReturn Slerp(GMATRIXD _matrix, GQUATERNIOND& _outQuaternion) override;
};

GQuaternionCpp::GQuaternionCpp()
{
}

GQuaternionCpp::~GQuaternionCpp()
{
}

//float quaternion

GW::GReturn GQuaternionCpp::AddQuaternion(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GQUATERNIONF& _outQuaternion)
{
	return FAILURE;
}

GW::GReturn GQuaternionCpp::SubtractQuaternion(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GQUATERNIONF& _outQuaternion)
{
	return FAILURE;
}


GW::GReturn GQuaternionCpp::MultiplyQuaternion(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GQUATERNIONF& _outQuaternion)
{
	return FAILURE;
}

GW::GReturn GQuaternionCpp::Scale(GQUATERNIONF _quaternion, float _scalar, GQUATERNIONF& _outQuaternion)
{
	return FAILURE;
}

GW::GReturn GQuaternionCpp::SetbyVectorAngle(GVECTORF _vector, float _angle, GQUATERNIONF& _outQuaternion)
{
	return FAILURE;
}

GW::GReturn GQuaternionCpp::SetbyMatrix(GMATRIXF _matrix, GQUATERNIONF& _outQuaternion)
{
	return FAILURE;
}

GW::GReturn GQuaternionCpp::Dot(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, float& _outValue)
{
	return FAILURE;
}

GReturn GQuaternionCpp::Cross(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GVECTORF & _outVector)
{
	return FAILURE;
}

GReturn GQuaternionCpp::Conjugate(GQUATERNIONF _quaternion, GQUATERNIONF & _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::Inverse(GQUATERNIONF _quaternion, GQUATERNIONF & _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::Magnitude(GQUATERNIONF _quaternion, float & _outMagnitude)
{
	return FAILURE;
}

GReturn GQuaternionCpp::Normalize(GQUATERNIONF _quaternion, GQUATERNIONF & _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::Identity(GQUATERNIONF _quaternion, GQUATERNIONF _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::Lerp(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, float _ratio, GQUATERNIONF & _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::ConvertMatrix(GMATRIXF _matrix, GQUATERNIONF & _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::Slerp(GMATRIXF _matrix, GQUATERNIONF & _outQuaternion)
{
	return FAILURE;
}

//double quaternion

GReturn GQuaternionCpp::AddQuaternion(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND & _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::SubtractQuaternion(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND & _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::MultiplyQuaternion(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND & _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::Scale(GQUATERNIOND _quaternion, GQUATERNIOND _quaternion2, GQUATERNIONF & _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::SetByVectorAngle(GQUATERNIOND _quaternion, GVECTORD _vector, double _angle, GQUATERNIOND & _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::SetByMatrix(GQUATERNIOND _quaternion, GMATRIXD _matrix, GQUATERNIOND & _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::Dot(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND & _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::Cross(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND & _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::Conjugate(GQUATERNIOND _quaternion, GQUATERNIOND & _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::Inverse(GQUATERNIOND _quaternion, GQUATERNIOND & _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::Magnitude(GQUATERNIOND _quaternion, double & _outMagnitude)
{
	return FAILURE;
}

GReturn GQuaternionCpp::Normalize(GQUATERNIOND _quaternion, GQUATERNIOND & _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::Identity(GQUATERNIOND _quaternion, GQUATERNIOND _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::Lerp(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, float _ratio, GQUATERNIOND & _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::ConvertMatrix(GMATRIXD _matrix, GQUATERNIOND & _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::Slerp(GMATRIXD _matrix, GQUATERNIOND & _outQuaternion)
{
	return FAILURE;
}



