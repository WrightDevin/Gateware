#include "../G_System/Common.h"


//THESE TEST CASES ARE SET UP IN A SPECIFIC ORDER. REORDERING TEST CASES COULD CAUSE
//CRASHES, FALSE FAILURES, or FALSE PASSES.

using namespace GW;
using namespace MATH;

//Globals used for all test cases.
GVector* VectorC;

GVECTORF vectorTest_VecF1;
GVECTORF vectorTest_VecF2;
GVECTORF vectorTest_OutVectorF;

GVECTORD vectorTest_VecD1;
GVECTORD vectorTest_VecD2;
GVECTORD vectorTest_OutVectorD;

GMATRIXF vectorTest_MatF;
GMATRIXF vectorTest_OutMatrixF;

GMATRIXD vectorTest_MatD;
GMATRIXD vectorTest_OutMatrixD;

float    vectorTest_NumF = 0.5f;
double   vectorTest_NumD = 0.4;

TEST_CASE("Create GVector.", "[CreateGVector]")
{
	//Fail cases
	CHECK(G_FAIL(CreateGVector(nullptr)));

	//Pass Cases
	REQUIRE(G_SUCCESS(CreateGVector(&VectorC)));
}

TEST_CASE("Add two vectors.", "[AddVectorF], [AddVectorD]")
{

	//Fail cases
	SECTION("Float vector addition.", "[AddVectorF]")
	{
		CHECK(G_FAIL(VectorC->AddVectorF(vectorTest_VecF1, vectorTest_VecF2, vectorTest_OutVectorF)));
	}
	SECTION("Double vector addition.", "[AddVectorD]")
	{
		CHECK(G_FAIL(VectorC->AddVectorD(vectorTest_VecD1, vectorTest_VecD2, vectorTest_OutVectorD)));
	}

}

TEST_CASE("Subtract two vectors.", "[SubtractVectorF], [SubtractVectorD]")
{

	//Fail cases
	SECTION("Float vector subtraction.", "[SubtractVectorF]")
	{
		CHECK(G_FAIL(VectorC->SubtractVectorF(vectorTest_VecF1, vectorTest_VecF2, vectorTest_OutVectorF)));
	}
	SECTION("Double vector subtraction.", "[SubtractVectorD]")
	{
		CHECK(G_FAIL(VectorC->SubtractVectorD(vectorTest_VecD1, vectorTest_VecD2, vectorTest_OutVectorD)));
	}

}

TEST_CASE("Scale the vector.", "[ScaleF], [ScaleD]")
{

	//Fail cases
	SECTION("Float vector.", "[ScaleF]")
	{
		CHECK(G_FAIL(VectorC->ScaleF(vectorTest_VecF1, vectorTest_NumF, vectorTest_OutVectorF)));
	}
	SECTION("Double vector.", "[ScaleD]")
	{
		CHECK(G_FAIL(VectorC->ScaleD(vectorTest_VecD1, vectorTest_NumD, vectorTest_OutVectorD)));
	}

}


TEST_CASE("Calculate the dot product of two vectors.", "[DotF], [DotD]")
{

	//Fail cases
	SECTION("Float vectors.", "[DotF]")
	{
		CHECK(G_FAIL(VectorC->DotF(vectorTest_VecF1, vectorTest_VecF2, vectorTest_NumF)));
	}
	SECTION("Double vectors.", "[DotD]")
	{
		CHECK(G_FAIL(VectorC->DotD(vectorTest_VecD1, vectorTest_VecD2, vectorTest_NumD)));
	}

}

TEST_CASE("Calculate the cross product of two 2d vectors.", "[CrossVector2F], [CrossVector2D]")
{

	//Fail cases
	SECTION("Float vectors.", "[CrossVector2F]")
	{
		CHECK(G_FAIL(VectorC->CrossVector2F(vectorTest_VecF1, vectorTest_VecF2, vectorTest_NumF)));
	}
	SECTION("Double vectors.", "[CrossVector2D]")
	{
		CHECK(G_FAIL(VectorC->CrossVector2D(vectorTest_VecD1, vectorTest_VecD2, vectorTest_NumD)));
	}

}

TEST_CASE("Calculate the cross product of two 3d vectors.", "[CrossVector3F], [CrossVector3D]")
{

	//Fail cases
	SECTION("Float vector.", "[CrossVector3F]")
	{
		CHECK(G_FAIL(VectorC->CrossVector3F(vectorTest_VecF1, vectorTest_VecF2, vectorTest_OutVectorF)));
	}
	SECTION("Double vector.", "[CrossVector3D]")
	{
		CHECK(G_FAIL(VectorC->CrossVector3D(vectorTest_VecD1, vectorTest_VecD2, vectorTest_OutVectorD)));
	}

}

TEST_CASE("Multiply a vector by matrix.", "[VectorXMatrixF], [VectorXMatrixD]")
{

	//Fail cases
	SECTION("Float vector.", "[VectorXMatrixF]")
	{
		CHECK(G_FAIL(VectorC->VectorXMatrixF(vectorTest_VecF1, vectorTest_MatF, vectorTest_OutVectorF)));
	}
	SECTION("Double vector.", "[VectorXMatrixD]")
	{
		CHECK(G_FAIL(VectorC->VectorXMatrixD(vectorTest_VecD1, vectorTest_MatD, vectorTest_OutVectorD)));
	}

}

TEST_CASE("Transform a vector by matrix.", "[TransformF], [TransformD]")
{

	//Fail cases
	SECTION("Float vector.", "[TransformF]")
	{
		CHECK(G_FAIL(VectorC->TransformF(vectorTest_VecF1, vectorTest_MatF, vectorTest_OutVectorF)));
	}
	SECTION("Double vector.", "[TransformD]")
	{
		CHECK(G_FAIL(VectorC->TransformD(vectorTest_VecD1, vectorTest_MatD, vectorTest_OutVectorD)));
	}

}

TEST_CASE("Calculate the magnitude of the vector.", "[MagnitudeF], [MagnitudeD]")
{

	//Fail cases
	SECTION("Float vector.", "[MagnitudeF]")
	{
		CHECK(G_FAIL(VectorC->MagnitudeF(vectorTest_VecF1, vectorTest_NumF)));
	}
	SECTION("Double vector.", "[MagnitudeD]")
	{
		CHECK(G_FAIL(VectorC->MagnitudeD(vectorTest_VecD1, vectorTest_NumD)));
	}

}

TEST_CASE("Normalize the vector.", "[NormalizeF], [NormalizeD]")
{

	//Fail cases
	SECTION("Float vector.", "[NormalizeF]")
	{
		CHECK(G_FAIL(VectorC->NormalizeF(vectorTest_VecF1, vectorTest_OutVectorF)));
	}
	SECTION("Double vector.", "[NormalizeD]")
	{
		CHECK(G_FAIL(VectorC->NormalizeD(vectorTest_VecD1, vectorTest_OutVectorD)));
	}

}

TEST_CASE("Lerp between two vectors.", "[LerpF], [LerpD]")
{

	//Fail cases
	SECTION("Float vector.", "[LerpF]")
	{
		CHECK(G_FAIL(VectorC->LerpF(vectorTest_VecF1, vectorTest_VecF2, vectorTest_NumF, vectorTest_OutVectorF)));
	}
	SECTION("Double vector.", "[LerpD]")
	{
		CHECK(G_FAIL(VectorC->LerpD(vectorTest_VecD1, vectorTest_VecD2, vectorTest_NumD, vectorTest_OutVectorD)));
	}

}

TEST_CASE("Slerp between two vectors.", "[SlerpF], [SlerpD]")
{

	//Fail cases
	SECTION("Float vector.", "[SlerpF]")
	{
		CHECK(G_FAIL(VectorC->SlerpF(vectorTest_VecF1, vectorTest_VecF2, vectorTest_NumF, vectorTest_OutVectorF)));
	}
	SECTION("Double vector.", "[SlerpD]")
	{
		CHECK(G_FAIL(VectorC->SlerpD(vectorTest_VecD1, vectorTest_VecD2, vectorTest_NumD, vectorTest_OutVectorD)));
	}

	VectorC->DecrementCount();
}