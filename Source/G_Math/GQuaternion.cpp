// Override export symbols for DLL builds (must be included before interface code).
#include "../DLL_Export_Symbols.h"
#include "../../Interface/G_Math/GQuaternion.h"
#include "../Source/G_System/GUtility.h"

#include <atomic> //Thread safety

//The using statements for specifically what we are using.
using namespace GW;
using namespace MATH;

class GQuaternionCpp : public GW::MATH::GQuaternion
{
	std::atomic<unsigned int> refCount;

public:
	GQuaternionCpp();
	~GQuaternionCpp();

	//float quaternion

	GReturn AddQuaternionF(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GQUATERNIONF& _outQuaternion) override;

	GReturn SubtractQuaternionF(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GQUATERNIONF& _outQuaternion) override;

	GReturn MultiplyQuaternionF(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GQUATERNIONF& _outQuaternion) override;

	GReturn ScaleF(GQUATERNIONF _quaternion, float _scalar, GQUATERNIONF& _outQuaternion) override;

	GReturn SetByVectorAngleF(GVECTORF _vector, float _radian, GQUATERNIONF& _outQuaternion) override;

	GReturn SetByMatrixF(GMATRIXF _matrix, GQUATERNIONF& _outQuaternion) override;

	GReturn DotF(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, float& _outValue) override;

	GReturn CrossF(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GVECTORF& _outVector) override;

	GReturn ConjugateF(GQUATERNIONF _quaternion, GQUATERNIONF& _outQuaternion) override;

	GReturn InverseF(GQUATERNIONF _quaternion, GQUATERNIONF& _outQuaternion) override;

	GReturn MagnitudeF(GQUATERNIONF _quaternion, float& _outMagnitude) override;

	GReturn NormalizeF(GQUATERNIONF _quaternion, GQUATERNIONF& _outQuaternion) override;

	GReturn IdentityF(GQUATERNIONF& _outQuaternion) override;

	GReturn LerpF(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, float _ratio, GQUATERNIONF& _outQuaternion) override;

	GReturn ConvertMatrixF(GMATRIXF _matrix, GQUATERNIONF& _outQuaternion) override;

	GReturn SlerpF(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, float _ratio, GQUATERNIONF& _outQuaternion) override;

	//double quaternion

	GReturn AddQuaternionD(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND& _outQuaternion) override;

	GReturn SubtractQuaternionD(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND& _outQuaternion) override;

	GReturn MultiplyQuaternionD(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND& _outQuaternion) override;

	GReturn ScaleD(GQUATERNIOND _quaternion, double _scalar, GQUATERNIOND& _outQuaternion) override;

	GReturn SetByVectorAngleD(GVECTORD _vector, double _radian, GQUATERNIOND& _outQuaternion) override;

	GReturn SetByMatrixD(GMATRIXD _matrix, GQUATERNIOND& _outQuaternion) override;

	GReturn DotD(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, double& _outQuaternion) override;

	GReturn CrossD(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GVECTORD& _outVector) override;

	GReturn ConjugateD(GQUATERNIOND _quaternion, GQUATERNIOND& _outQuaternion) override;

	GReturn InverseD(GQUATERNIOND _quaternion, GQUATERNIOND& _outQuaternion) override;

	GReturn MagnitudeD(GQUATERNIOND _quaternion, double& _outMagnitude) override;

	GReturn NormalizeD(GQUATERNIOND _quaternion, GQUATERNIOND& _outQuaternion) override;

	GReturn IdentityD(GQUATERNIOND& _outQuaternion) override;

	GReturn LerpD(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, float _ratio, GQUATERNIOND& _outQuaternion) override;

	GReturn ConvertMatrixD(GMATRIXD _matrix, GQUATERNIOND& _outQuaternion) override;

	GReturn SlerpD(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, double _ratio, GQUATERNIOND& _outQuaternion) override;





	GReturn GetCount(unsigned int& _outCount) override;

	GReturn IncrementCount() override;

	GReturn DecrementCount() override;

	GReturn RequestInterface(const GW::GUUIID& _interfaceID, void** _outputInterface) override;
};

GQuaternionCpp::GQuaternionCpp() : refCount(1)
{
}

GQuaternionCpp::~GQuaternionCpp()
{
}

//float quaternion

GW::GReturn GQuaternionCpp::AddQuaternionF(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GQUATERNIONF& _outQuaternion)
{
	return FAILURE;
}

GW::GReturn GQuaternionCpp::SubtractQuaternionF(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GQUATERNIONF& _outQuaternion)
{
	return FAILURE;
}


GW::GReturn GQuaternionCpp::MultiplyQuaternionF(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GQUATERNIONF& _outQuaternion)
{
	return FAILURE;
}

GW::GReturn GQuaternionCpp::ScaleF(GQUATERNIONF _quaternion, float _scalar, GQUATERNIONF& _outQuaternion)
{
	return FAILURE;
}

GW::GReturn GQuaternionCpp::SetByVectorAngleF(GVECTORF _vector, float _radian, GQUATERNIONF& _outQuaternion)
{
	return FAILURE;
}

GW::GReturn GQuaternionCpp::SetByMatrixF(GMATRIXF _matrix, GQUATERNIONF& _outQuaternion)
{
	return FAILURE;
}

GW::GReturn GQuaternionCpp::DotF(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, float& _outValue)
{
	return FAILURE;
}

GReturn GQuaternionCpp::CrossF(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GVECTORF& _outVector)
{
	return FAILURE;
}

GReturn GQuaternionCpp::ConjugateF(GQUATERNIONF _quaternion, GQUATERNIONF& _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::InverseF(GQUATERNIONF _quaternion, GQUATERNIONF& _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::MagnitudeF(GQUATERNIONF _quaternion, float& _outMagnitude)
{
	return FAILURE;
}

GReturn GQuaternionCpp::NormalizeF(GQUATERNIONF _quaternion, GQUATERNIONF& _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::IdentityF(GQUATERNIONF& _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::LerpF(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, float _ratio, GQUATERNIONF& _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::ConvertMatrixF(GMATRIXF _matrix, GQUATERNIONF& _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::SlerpF(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, float _ratio, GQUATERNIONF& _outQuaternion)
{
	return FAILURE;
}


//double quaternion

GReturn GQuaternionCpp::AddQuaternionD(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND& _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::SubtractQuaternionD(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND& _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::MultiplyQuaternionD(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND& _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::ScaleD(GQUATERNIOND _quaternion, double _scalar, GQUATERNIOND& _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::SetByVectorAngleD(GVECTORD _vector, double _radian, GQUATERNIOND& _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::SetByMatrixD(GMATRIXD _matrix, GQUATERNIOND& _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::DotD(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, double& _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::CrossD(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GVECTORD& _outVector)
{
	return FAILURE;
}

GReturn GQuaternionCpp::ConjugateD(GQUATERNIOND _quaternion, GQUATERNIOND& _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::InverseD(GQUATERNIOND _quaternion, GQUATERNIOND& _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::MagnitudeD(GQUATERNIOND _quaternion, double& _outMagnitude)
{
	return FAILURE;
}

GReturn GQuaternionCpp::NormalizeD(GQUATERNIOND _quaternion, GQUATERNIOND& _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::IdentityD(GQUATERNIOND& _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::LerpD(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, float _ratio, GQUATERNIOND& _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::ConvertMatrixD(GMATRIXD _matrix, GQUATERNIOND& _outQuaternion)
{
	return FAILURE;
}

GReturn GQuaternionCpp::SlerpD(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, double _ratio, GQUATERNIOND& _outQuaternion)
{
	return FAILURE;
}


GReturn GQuaternionCpp::GetCount(unsigned int& _outCount)
{
	//Store reference count.
	_outCount = refCount;

	return GW::SUCCESS;
}

GReturn GQuaternionCpp::IncrementCount()
{
	//Check for possible overflow.
	if (refCount == G_UINT_MAX)
		return FAILURE;

	++refCount;

	return SUCCESS;
}

GReturn GQuaternionCpp::DecrementCount()
{
	//Check to make sure underflow will not occur.
	if (refCount == 0)
		return GW::FAILURE;

	//Decrement reference count.
	--refCount;

	return GW::SUCCESS;
}

GReturn GQuaternionCpp::RequestInterface(const GW::GUUIID& _interfaceID, void ** _outputInterface)
{
	if (_outputInterface == nullptr)
		return GW::INVALID_ARGUMENT;

	//If passed in interface is equivalent to current interface (this).
	if (_interfaceID == GW::MATH::GQuaternionUUIID)
	{
		//Temporary GQuaternion* to ensure proper functions are called.
		GQuaternion* convert = reinterpret_cast<GQuaternion*>(this);

		//Increment the count of the GFile.
		convert->IncrementCount();

		//Store the value.
		(*_outputInterface) = convert;
	}
	//If requested interface is multithreaded.
	else if (_interfaceID == GW::CORE::GSingleThreadedUUIID)
	{
		//Temporary GMultiThreaded* to ensure proper functions are called.
		GSingleThreaded* convert = reinterpret_cast<GSingleThreaded*>(this);

		//Increment the count of the GMultithreaded.
		convert->IncrementCount();

		//Store the value.
		(*_outputInterface) = convert;
	}
	//If requested interface is the primary interface.
	else if (_interfaceID == GW::CORE::GInterfaceUUIID)
	{
		//Temporary GInterface* to ensure proper functions are called.
		GInterface* convert = reinterpret_cast<GInterface*>(this);

		//Increment the count of the GInterface.
		convert->IncrementCount();

		//Store the value.
		(*_outputInterface) = convert;
	}
	//Interface is not supported.
	else
		return GW::INTERFACE_UNSUPPORTED;

	return GW::SUCCESS;
}


GATEWARE_EXPORT_EXPLICIT GReturn CreateGQuaternion(GQuaternion** _outQuaternion)
{
	return GW::MATH::CreateGQuaternion(_outQuaternion);
}

GReturn GW::MATH::CreateGQuaternion(GQuaternion** _outQuaternion)
{
	if (_outQuaternion == nullptr)
	{
		return INVALID_ARGUMENT;
	}
	GQuaternionCpp* mat = new GQuaternionCpp();

	if (mat == nullptr)
	{
		return FAILURE;
	}

	(*_outQuaternion) = mat;

	return SUCCESS;
}


