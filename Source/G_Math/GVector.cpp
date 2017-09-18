// Override export symbols for DLL builds (must be included before interface code).
#include "../DLL_Export_Symbols.h"
#include "../../Interface/G_Math/GVector.h"
#include "../Source/G_System/GUtility.h"

#include <atomic> //Thread safety

//The using statements for specifically what we are using.
using namespace GW;
using namespace MATH;

class GVectorCpp :public::GW::MATH::GVector
{
	//Reference counter.
	atomic<unsigned int> refCount;

public:
	GVectorCpp();
	~GVectorCpp();

	//float vector

	GReturn AddVectorF(GVECTORF _vector1, GVECTORF _vector2, GVECTORF& _outVector) override;

	GReturn SubtractVectorF(GVECTORF _vector1, GVECTORF _vector2, GVECTORF& _outVector) override;

	GReturn ScaleF(GVECTORF _vector, float _scalar, GVECTORF& _outVector) override;

	GReturn DotF(GVECTORF _vector1, GVECTORF _vector2, float& _outValue) override;

	GReturn CrossVector2F(GVECTORF _vector1, GVECTORF _vector2, float& _outValue) override;
																					 
	GReturn CrossVector3F(GVECTORF _vector1, GVECTORF _vector2, GVECTORF& _outVector) override;

	GReturn VectorXMatrixF(GVECTORF _vector, GMATRIXF _matrix, GVECTORF& _outVector) override;

	GReturn TransformF(GVECTORF _vector, GMATRIXF _matrix, GVECTORF& _outVector) override;

	GReturn MagnitudeF(GVECTORF _vector, float& _outMagnitude) override;
															  
	GReturn NormalizeF(GVECTORF _vector, GVECTORF& _outVector) override;

	GReturn LerpF(GVECTORF _vector1, GVECTORF _vector2, float _ratio, GVECTORF& _outVector) override;

	GReturn SlerpF(GVECTORF _vector1, GVECTORF _vector2, float _ratio, GVECTORF& _outVector) override;

	//double vector

	GReturn AddVectorD(GVECTORD _vector1, GVECTORD _vector2, GVECTORD& _outVector) override;

	GReturn SubtractVectorD(GVECTORD _vector1, GVECTORD _vector2, GVECTORD& _outVector) override;

	GReturn ScaleD(GVECTORD _vector, double _scalar, GVECTORD& _outVector) override;

	GReturn DotD(GVECTORD _vector1, GVECTORD _vector2, double& _outValue) override;

	GReturn CrossVector2D(GVECTORD _vector1, GVECTORD _vector2, double& _outValue) override;

	GReturn CrossVector3D(GVECTORD _vector1, GVECTORD _vector2, GVECTORD& _outVector) override;

	GReturn VectorXMatrixD(GVECTORD _vector, GMATRIXD _matrix, GVECTORD& _outVector) override;

	GReturn TransformD(GVECTORD _vector, GMATRIXD _matrix, GVECTORD& _outVector) override;

	GReturn MagnitudeD(GVECTORD _vector, double& _outMagnitude) override;

	GReturn NormalizeD(GVECTORD _vector, GVECTORD& _outVector) override;

	GReturn LerpD(GVECTORD _vector1, GVECTORD _vector2, double _ratio, GVECTORD& _outVector) override;

	GReturn SlerpD(GVECTORD _vector1, GVECTORD _vector2, double _ratio, GVECTORD& _outVector) override;

	GReturn GetCount(unsigned int& _outCount) override;

	GReturn IncrementCount() override;

	GReturn DecrementCount() override;

	GReturn RequestInterface(const GW::GUUIID& _interfaceID, void** _outputInterface) override;

};

GVectorCpp::GVectorCpp()
{
}

GVectorCpp::~GVectorCpp()
{
}

//float vector

GReturn GVectorCpp::AddVectorF(GVECTORF _vector1, GVECTORF _vector2, GVECTORF& _outVector)
{
	//GVECTORD f;
	//
	//_outVector.x = f.x + _vector2.x;
	//_outVector.y = f.y + _vector2.y;
	//_outVector.z = f.z + _vector2.z;
	//_outVector.w = f.w + _vector2.w;
	//return SUCCESS;


	return FAILURE;
}

GReturn GVectorCpp::SubtractVectorF(GVECTORF _vector1, GVECTORF _vector2, GVECTORF& _outVector)
{
	return FAILURE;
}

GReturn GVectorCpp::ScaleF(GVECTORF _vector, float _scalar, GVECTORF& _outVector)
{
	return FAILURE;
}

GReturn GVectorCpp::DotF(GVECTORF _vector1, GVECTORF _vector2, float& _outValue)
{
	return FAILURE;
}

GReturn GVectorCpp::CrossVector2F(GVECTORF _vector1, GVECTORF _vector2, float& _outValue)
{
	return FAILURE;
}

GReturn GVectorCpp::CrossVector3F(GVECTORF _vector1, GVECTORF _vector2, GVECTORF& _outVector)
{
	return FAILURE;
}

GReturn GVectorCpp::VectorXMatrixF(GVECTORF _vector, GMATRIXF _matrix, GVECTORF& _outVector)
{
	return FAILURE;
}

GReturn GVectorCpp::TransformF(GVECTORF _vector, GMATRIXF _matrix, GVECTORF& _outVector)
{
	return FAILURE;
}

GReturn GVectorCpp::MagnitudeF(GVECTORF _vector, float& _outMagnitude)
{
	return FAILURE;
}

GReturn GVectorCpp::NormalizeF(GVECTORF _vector, GVECTORF& _outVector)
{
	return FAILURE;
}

GReturn GVectorCpp::LerpF(GVECTORF _vector1, GVECTORF _vector2, float _ratio, GVECTORF & _outVector)
{
	return FAILURE;
}

GReturn GVectorCpp::SlerpF(GVECTORF _vector1, GVECTORF _vector2, float _ratio, GVECTORF & _outVector)
{
	return FAILURE;
}

//double vector

GReturn GVectorCpp::AddVectorD(GVECTORD _vector1, GVECTORD _vector2, GVECTORD& _outVector)
{
	return FAILURE;
}

GReturn GVectorCpp::SubtractVectorD(GVECTORD _vector1, GVECTORD _vector2, GVECTORD& _outVector)
{
	return FAILURE;
}

GReturn GVectorCpp::ScaleD(GVECTORD _vector, double _scalar, GVECTORD& _outVector)
{
	return FAILURE;
}

GReturn GVectorCpp::DotD(GVECTORD _vector1, GVECTORD _vector2, double& _outValue)
{
	return FAILURE;
}

GReturn GVectorCpp::CrossVector2D(GVECTORD _vector1, GVECTORD _vector2, double& _outValue)
{
	return FAILURE;
}

GReturn GVectorCpp::CrossVector3D(GVECTORD _vector1, GVECTORD _vector2, GVECTORD& _outVector)
{
	return FAILURE;
}

GReturn GVectorCpp::VectorXMatrixD(GVECTORD _vector, GMATRIXD _matrix, GVECTORD& _outVector)
{
	return FAILURE;
}

GReturn GVectorCpp::TransformD(GVECTORD _vector, GMATRIXD _matrix, GVECTORD& _outVector)
{
	return FAILURE;
}

GReturn GVectorCpp::MagnitudeD(GVECTORD _vector, double& _outMagnitude)
{
	return FAILURE;
}

GReturn GVectorCpp::NormalizeD(GVECTORD _vector, GVECTORD& _outVector)
{
	return FAILURE;
}

GReturn GVectorCpp::LerpD(GVECTORD _vector1, GVECTORD _vector2, double _ratio, GVECTORD & _outVector)
{
	return FAILURE;
}

GReturn GVectorCpp::SlerpD(GVECTORD _vector1, GVECTORD _vector2, double _ratio, GVECTORD & _outVector)
{
	return FAILURE;
}

GReturn GVectorCpp::GetCount(unsigned int& _outCount)
{
	//Store reference count.
	_outCount = refCount;

	return GW::SUCCESS;
}

GReturn GVectorCpp::IncrementCount()
{
	//Check to make sure overflow will not occur.
	if (refCount == G_UINT_MAX)
		return GW::FAILURE;

	//Increment reference count.
	++refCount;

	return GW::SUCCESS;
}

GReturn GVectorCpp::DecrementCount()
{
	//Check to make sure underflow will not occur.
	if (refCount == 0)
		return GW::FAILURE;

	//Decrement reference count.
	--refCount;

	return GW::SUCCESS;
}

GReturn GVectorCpp::RequestInterface(const GW::GUUIID& _interfaceID, void ** _outputInterface)
{

	if (_outputInterface == nullptr)
		return GW::INVALID_ARGUMENT;

	//If passed in interface is equivalent to current interface (this).
	if (_interfaceID == GW::MATH::GVectorUUIID)
	{
		//Temporary GFile* to ensure proper functions are called.
		GVector* convert = reinterpret_cast<GVector*>(this);

		//Increment the count of the GFile.
		convert->IncrementCount();

		//Store the value.
		(*_outputInterface) = convert;
	}
	//If requested interface is multithreaded.
	else if (_interfaceID == GW::CORE::GSingleThreadedUUIID)
	{
		//Temporary GSingleThreaded* to ensure proper functions are called.
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


GATEWARE_EXPORT_EXPLICIT GReturn CreateGVector(GVector** _outVector)
{
	return GW::MATH::CreateGVector(_outVector);
}

GReturn GW::MATH::CreateGVector(GVector** _outVector)
{
	if (_outVector == nullptr)
	{
		return INVALID_ARGUMENT;
	}
	GVectorCpp* vec = new GVectorCpp();

	if (vec == nullptr)
	{
		return FAILURE;
	}

	(*_outVector) = vec;

	return SUCCESS;
}

