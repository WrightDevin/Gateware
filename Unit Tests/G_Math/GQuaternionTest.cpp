#include "../G_System/Common.h"


//THESE TEST CASES ARE SET UP IN A SPECIFIC ORDER. REORDERING TEST CASES COULD CAUSE
//CRASHES, FALSE FAILURES, or FALSE PASSES.

using namespace GW;
using namespace MATH;

//Globals used for all test cases.
GQuaternion* QuaternionC;

GQUATERNIONF quaternionTest_QuaF1;
GQUATERNIONF quaternionTest_QuaF2;
GQUATERNIONF quaternionTest_OutQuaternionF;
GQUATERNIOND quaternionTest_QuaD1;
GQUATERNIOND quaternionTest_QuaD2;
GQUATERNIOND quaternionTest_OutQuaternionD;

GMATRIXF quaternionTest_MatF;
GMATRIXF quaternionTest_OutMatrixF1;

GMATRIXD quaternionTest_MatD;
GMATRIXD quaternionTest_OutMatrixD;

GVECTORF quaternionTest_VecF;
GVECTORF quaternionTest_OutVectorF;

GVECTORD quaternionTest_VecD;
GVECTORD quaternionTest_OutVectorD;

float quaternionTest_NumF = 0.5f;
double quaternionTest_NumD = 0.4;



TEST_CASE("Create GQuaternion.", "[CreateGQuaternion]")
{
	//Fail cases
	CHECK(G_FAIL(CreateGQuaternion(nullptr)));

	//Pass Cases
	REQUIRE(G_SUCCESS(CreateGQuaternion(&QuaternionC)));
}

TEST_CASE("Add two quaternions.", "[AddQuaternionF], [AddQuaternionD]")
{

	//Fail cases
	SECTION("Float quaternion addition.", "[AddQuaternionF]")
	{
		CHECK(G_FAIL(QuaternionC->AddQuaternionF(quaternionTest_QuaF1, quaternionTest_QuaF2, quaternionTest_OutQuaternionF)));
	}
	SECTION("Double quaternion addition.", "[AddQuaternionD]")
	{
		CHECK(G_FAIL(QuaternionC->AddQuaternionD(quaternionTest_QuaD1, quaternionTest_QuaD2, quaternionTest_OutQuaternionD)));
	}

}

TEST_CASE("Subtract two quaternions.", "[SubtractQuaternionF], [SubtractQuaternionD]")
{

	//Fail cases
	SECTION("Float quaternion subtraction.", "[SubtractQuaternionF]")
	{
		CHECK(G_FAIL(QuaternionC->SubtractQuaternionF(quaternionTest_QuaF1, quaternionTest_QuaF2, quaternionTest_OutQuaternionF)));
	}
	SECTION("Double quaternion subtraction.", "[SubtractQuaternionD]")
	{
		CHECK(G_FAIL(QuaternionC->SubtractQuaternionD(quaternionTest_QuaD1, quaternionTest_QuaD2, quaternionTest_OutQuaternionD)));
	}

}

TEST_CASE("Multiply two quaternions.", "[MultiplyQuaternionF], [MultiplyQuaternionD]")
{

	//Fail cases
	SECTION("Float quaternion Multiplication.", "[MultiplyQuaternionF]")
	{
		CHECK(G_FAIL(QuaternionC->MultiplyQuaternionF(quaternionTest_QuaF1, quaternionTest_QuaF2, quaternionTest_OutQuaternionF)));
	}
	SECTION("Double quaternion Multiplication.", "[MultiplyQuaternionD]")
	{
		CHECK(G_FAIL(QuaternionC->MultiplyQuaternionD(quaternionTest_QuaD1, quaternionTest_QuaD2, quaternionTest_OutQuaternionD)));
	}

}

TEST_CASE("Scale two quaternions.", "[ScaleF], [ScaleD]")
{

	//Fail cases
	SECTION("Float quaternion scaling.", "[ScaleF]")
	{
		CHECK(G_FAIL(QuaternionC->ScaleF(quaternionTest_QuaF1, quaternionTest_NumF, quaternionTest_OutQuaternionF)));
	}
	SECTION("Double quaternion scaling.", "[ScaleD]")
	{
		CHECK(G_FAIL(QuaternionC->ScaleD(quaternionTest_QuaD1, quaternionTest_NumD, quaternionTest_OutQuaternionD)));
	}

}

TEST_CASE("Set a quaternion by a vector and a angle.", "[SetByVectorAngleF], [SetByVectorAngleD]")
{

	//Fail cases
	SECTION("Float quaternion.", "[SetByVectorAngleF]")
	{
		CHECK(G_FAIL(QuaternionC->SetByVectorAngleF(quaternionTest_VecF, quaternionTest_NumF, quaternionTest_OutQuaternionF)));
	}
	SECTION("Double quaternion.", "[SetByVectorAngleD]")
	{
		CHECK(G_FAIL(QuaternionC->SetByVectorAngleD(quaternionTest_VecD, quaternionTest_NumD, quaternionTest_OutQuaternionD)));
	}

}

TEST_CASE("Set a quaternion by a matrix.", "[SetByMatrixF], [SetByMatrixD]")
{

	//Fail cases
	SECTION("Float quaternion.", "[SetByMatrixF]")
	{
		CHECK(G_FAIL(QuaternionC->SetByMatrixF(quaternionTest_MatF, quaternionTest_OutQuaternionF)));
	}
	SECTION("Double quaternion.", "[SetByMatrixD]")
	{
		CHECK(G_FAIL(QuaternionC->SetByMatrixD(quaternionTest_MatD, quaternionTest_OutQuaternionD)));
	}

}

TEST_CASE("Calculate the dot product of a quaternion.", "[DotF], [DotD]")
{

	//Fail cases
	SECTION("Float quaternion dot product.", "[DotF]")
	{
		CHECK(G_FAIL(QuaternionC->DotF(quaternionTest_QuaF1, quaternionTest_QuaF2, quaternionTest_NumF)));
	}
	SECTION("Double quaternion dot product.", "[DotD]")
	{
		CHECK(G_FAIL(QuaternionC->DotD(quaternionTest_QuaD1, quaternionTest_QuaD2, quaternionTest_NumD)));
	}

}

TEST_CASE("Calculate the cross product of a quaternion.", "[CrossF], [CrossD]")
{

	//Fail cases
	SECTION("Float quaternion subtraction.", "[CrossF]")
	{
		CHECK(G_FAIL(QuaternionC->CrossF(quaternionTest_QuaF1, quaternionTest_QuaF2, quaternionTest_OutVectorF)));
	}
	SECTION("Double quaternion subtraction.", "[CrossD]")
	{
		CHECK(G_FAIL(QuaternionC->CrossD(quaternionTest_QuaD1, quaternionTest_QuaD2, quaternionTest_OutVectorD)));
	}

}


TEST_CASE("Set a quaternion to the conjugate of itself.", "[ConjugateF], [ConjugateD]")
{

	//Fail cases
	SECTION("Float quaternion.", "[ConjugateF]")
	{
		CHECK(G_FAIL(QuaternionC->ConjugateF(quaternionTest_QuaF1, quaternionTest_OutQuaternionF)));
	}
	SECTION("Double quaternion.", "[ConjugateD]")
	{
		CHECK(G_FAIL(QuaternionC->ConjugateD(quaternionTest_QuaD1, quaternionTest_OutQuaternionD)));
	}

}

TEST_CASE("Set a quaternion to the inverse of itself.", "[InverseF], [InverseD]")
{

	//Fail cases
	SECTION("Float quaternion.", "[InverseF]")
	{
		CHECK(G_FAIL(QuaternionC->InverseF(quaternionTest_QuaF1, quaternionTest_OutQuaternionF)));
	}
	SECTION("Double quaternion.", "[InverseD]")
	{
		CHECK(G_FAIL(QuaternionC->InverseD(quaternionTest_QuaD1, quaternionTest_OutQuaternionD)));
	}

}

TEST_CASE("Calcuate the magnitude of the quaternion.", "[MagnitudeF], [MagnitudeD]")
{

	//Fail cases
	SECTION("Float quaternion.", "[MagnitudeF]")
	{
		CHECK(G_FAIL(QuaternionC->MagnitudeF(quaternionTest_QuaF1, quaternionTest_NumF)));
	}
	SECTION("Double quaternion.", "[MagnitudeD]")
	{
		CHECK(G_FAIL(QuaternionC->MagnitudeD(quaternionTest_QuaD1, quaternionTest_NumD)));
	}

}

TEST_CASE("Normalize the quaternion.", "[NormalizeF], [NormalizeD]")
{

	//Fail cases
	SECTION("Float quaternion.", "[NormalizeF]")
	{
		CHECK(G_FAIL(QuaternionC->NormalizeF(quaternionTest_QuaF1, quaternionTest_OutQuaternionF)));
	}
	SECTION("Double quaternion.", "[NormalizeD]")
	{
		CHECK(G_FAIL(QuaternionC->NormalizeD(quaternionTest_QuaD1, quaternionTest_OutQuaternionD)));
	}

}

TEST_CASE("Set a identity quaternion.", "[IdentityF], [IdentityD]")
{

	//Fail cases
	SECTION("Float quaternion.", "[IdentityF]")
	{
		CHECK(G_FAIL(QuaternionC->IdentityF(quaternionTest_OutQuaternionF)));
	}
	SECTION("Double quaternion.", "[IdentityD]")
	{
		CHECK(G_FAIL(QuaternionC->IdentityD(quaternionTest_OutQuaternionD)));
	}

}

TEST_CASE("Calcuate the lerp of the quaternion.", "[LerpF], [LerpD]")
{

	//Fail cases
	SECTION("Float quaternion.", "[LerpF]")
	{
		CHECK(G_FAIL(QuaternionC->LerpF(quaternionTest_QuaF1, quaternionTest_QuaF2, quaternionTest_NumF, quaternionTest_OutQuaternionF)));
	}
	SECTION("Double quaternion.", "[LerpD]")
	{
		CHECK(G_FAIL(QuaternionC->LerpD(quaternionTest_QuaD1, quaternionTest_QuaD2, quaternionTest_NumD, quaternionTest_OutQuaternionD)));
	}

}

TEST_CASE("Convert a matrix to a quaternion.", "[ConvertMatrixF], [ConvertMatrixD]")
{

	//Fail cases
	SECTION("Float quaternion.", "[ConvertMatrixF]")
	{
		CHECK(G_FAIL(QuaternionC->ConvertMatrixF(quaternionTest_MatF, quaternionTest_OutQuaternionF)));
	}
	SECTION("Double quaternion.", "[ConvertMatrixD]")
	{
		CHECK(G_FAIL(QuaternionC->ConvertMatrixD(quaternionTest_MatD, quaternionTest_OutQuaternionD)));
	}

}

TEST_CASE("Calcuate the slerp of the quaternion.", "[SlerpF], [SlerpD]")
{

	//Fail cases
	SECTION("Float quaternion.", "[SlerpF]")
	{
		CHECK(G_FAIL(QuaternionC->SlerpF(quaternionTest_QuaF1, quaternionTest_QuaF2, quaternionTest_NumF, quaternionTest_OutQuaternionF)));
	}
	SECTION("Double quaternion.", "[SlerpD]")
	{
		CHECK(G_FAIL(QuaternionC->SlerpD(quaternionTest_QuaD1, quaternionTest_QuaD2, quaternionTest_NumD, quaternionTest_OutQuaternionD)));
	}

	QuaternionC->DecrementCount();
}