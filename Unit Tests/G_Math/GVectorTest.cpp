#include "../G_System/Common.h"


//THESE TEST CASES ARE SET UP IN A SPECIFIC ORDER. REORDERING TEST CASES COULD CAUSE
//CRASHES, FALSE FAILURES, or FALSE PASSES.

using namespace GW;
using namespace MATH;

//Globals used for all test cases.
GVector* VectorC;


TEST_CASE("Create GVector.", "[CreateGVector]")
{
	//Fail cases
	CHECK(G_FAIL(CreateGVector(nullptr)));

	//Pass Cases
	REQUIRE(G_SUCCESS(CreateGVector(&VectorC)));
}

TEST_CASE("Add two vectors.", "[AddVectorF], [AddVectorD]")
{
	GVECTORF vF1 = { 1, 2, 3, 4 };
	GVECTORF vF2 = { 0.1f, 0.2f, 0.3f, 0.4f };
	GVECTORF resultF;

	GVECTORD vD1 = { 1, 2, 3, 4 };
	GVECTORD vD2 = { 0.1, 0.2, 0.3, 0.4 };
	GVECTORD resultD;

	SECTION("Float vector addition.", "[AddVectorF]")
	{
		CHECK(G_SUCCESS(VectorC->AddVectorF(vF1, vF2, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.x, 1.1f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.y, 2.2f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.z, 3.3f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.w, 4.4f));
	}
	SECTION("Double vector addition.", "[AddVectorD]")
	{
		CHECK(G_SUCCESS(VectorC->AddVectorD(vD1, vD2, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.x, 1.1));
		CHECK(G_COMPARISON_STANDARD_D(resultD.y, 2.2));
		CHECK(G_COMPARISON_STANDARD_D(resultD.z, 3.3));
		CHECK(G_COMPARISON_STANDARD_D(resultD.w, 4.4));
	}

}

TEST_CASE("Subtract two vectors.", "[SubtractVectorF], [SubtractVectorD]")
{
	GVECTORF vF1 = { 1, 2, 3, 4 };
	GVECTORF vF2 = { 0.1f, 0.2f, 0.3f, 0.4f };
	GVECTORF resultF;

	GVECTORD vD1 = { 1, 2, 3, 4 };
	GVECTORD vD2 = { 0.1, 0.2, 0.3, 0.4 };
	GVECTORD resultD;

	SECTION("Float vector subtraction.", "[SubtractVectorF]")
	{
		CHECK(G_SUCCESS(VectorC->SubtractVectorF(vF1, vF2, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.x, 0.9f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.y, 1.8f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.z, 2.7f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.w, 3.6f));
	}
	SECTION("Double vector subtraction.", "[SubtractVectorD]")
	{
		CHECK(G_SUCCESS(VectorC->SubtractVectorD(vD1, vD2, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.x, 0.9));
		CHECK(G_COMPARISON_STANDARD_D(resultD.y, 1.8));
		CHECK(G_COMPARISON_STANDARD_D(resultD.z, 2.7));
		CHECK(G_COMPARISON_STANDARD_D(resultD.w, 3.6));
	}

}

TEST_CASE("Scale the vector.", "[ScaleF], [ScaleD]")
{
	GVECTORF vF = { 0.1f, 0.2f, 0.3f, 0.4f };
	GVECTORF resultF;

	GVECTORD vD = { 0.1, 0.2, 0.3, 0.4 };
	GVECTORD resultD;

	SECTION("Float vector.", "[ScaleF]")
	{
		CHECK(G_SUCCESS(VectorC->ScaleF(vF, 0.3f, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.x, 0.03f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.y, 0.06f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.z, 0.09f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.w, 0.12f));
	}
	SECTION("Double vector.", "[ScaleD]")
	{
		CHECK(G_SUCCESS(VectorC->ScaleD(vD, 0.3, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.x, 0.03));
		CHECK(G_COMPARISON_STANDARD_D(resultD.y, 0.06));
		CHECK(G_COMPARISON_STANDARD_D(resultD.z, 0.09));
		CHECK(G_COMPARISON_STANDARD_D(resultD.w, 0.12));
	}

}


TEST_CASE("Calculate the dot product of two vectors.", "[DotF], [DotD]")
{
	GVECTORF vF1 = { 1, 2, 3, 4 };
	GVECTORF vF2 = { 0.1f, 0.2f, 0.3f, 0.4f };
	float resultF;

	GVECTORD vD1 = { 1, 2, 3, 4 };
	GVECTORD vD2 = { 0.1, 0.2, 0.3, 0.4 };
	double resultD;

	SECTION("Float vectors.", "[DotF]")
	{
		CHECK(G_SUCCESS(VectorC->DotF(vF1, vF2, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF, 3.0f));
	}
	SECTION("Double vectors.", "[DotD]")
	{
		CHECK(G_SUCCESS(VectorC->DotD(vD1, vD2, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD, 3));
	}

}

TEST_CASE("Calculate the cross product of two 2d vectors.", "[CrossVector2F], [CrossVector2D]")
{
	GVECTORF vF1 = { 1, 2, 3, 4 };
	GVECTORF vF2 = { 0.1f, 0.2f, 0.3f, 0.4f };
	float resultF;

	GVECTORD vD1 = { 1, 2, 3, 4 };
	GVECTORD vD2 = { 0.1, 0.2, 0.3, 0.4 };
	double resultD;

	SECTION("Float vectors.", "[CrossVector2F]")
	{
		CHECK(G_SUCCESS(VectorC->CrossVector2F(vF1, vF2, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF, 0.0f));
	}
	SECTION("Double vectors.", "[CrossVector2D]")
	{
		CHECK(G_SUCCESS(VectorC->CrossVector2D(vD1, vD2, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD, 0));
	}

}

TEST_CASE("Calculate the cross product of two 3d vectors.", "[CrossVector3F], [CrossVector3D]")
{
	GVECTORF vF1 = { 5.2f, 3.4f, 2.0f, 1.0f };
	GVECTORF vF2 = { 0.2f, 1.0f, 2.5f, 0.4f };
	GVECTORF resultF;

	GVECTORD vD1 = { 5.2, 3.4, 2.0, 1.0 };
	GVECTORD vD2 = { 0.2, 1.0, 2.5, 0.4 };
	GVECTORD resultD;

	SECTION("Float vector.", "[CrossVector3F]")
	{
		CHECK(G_SUCCESS(VectorC->CrossVector3F(vF1, vF2, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.x,   6.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.y, -12.6f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.z,  4.52f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.w,   0.0f));
	}
	SECTION("Double vector.", "[CrossVector3D]")
	{
		CHECK(G_SUCCESS(VectorC->CrossVector3D(vD1, vD2, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.x, 6.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.y, -12.6));
		CHECK(G_COMPARISON_STANDARD_D(resultD.z, 4.52));
		CHECK(G_COMPARISON_STANDARD_D(resultD.w, 0.0));
	}

}

TEST_CASE("Multiply a vector by matrix.", "[VectorXMatrixF], [VectorXMatrixD]")
{
	GVECTORF vF = { 5.2f, 3.4f, 2.0f, 1.0f };
	GMATRIXF mF = { 0.2f, 1.0f, 2.5f, 0.4f, 0.7f, 5.9f, 2.2f, 4.1f, 3.8f, 0.0f, 8.5f, 12.4f, 7.6f, 5.5f, 9.8f, 1.0f};
	GVECTORF resultF;

	GVECTORD vD = { 5.2, 3.4, 2.0, 1.0 };
	GMATRIXD mD = { 0.2, 1.0, 2.5, 0.4, 0.7, 5.9, 2.2, 4.1, 3.8, 0.0, 8.5, 12.4, 7.6, 5.5, 9.8, 1.0 };
	GVECTORD resultD;

	SECTION("Float vector.", "[VectorXMatrixF]")
	{
		CHECK(G_SUCCESS(VectorC->VectorXMatrixF(vF, mF, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.x, 18.62f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.y, 30.76f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.z, 47.28f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.w, 41.82f));
	}
	SECTION("Double vector.", "[VectorXMatrixD]")
	{
		CHECK(G_SUCCESS(VectorC->VectorXMatrixD(vD, mD, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.x, 18.62));
		CHECK(G_COMPARISON_STANDARD_D(resultD.y, 30.76));
		CHECK(G_COMPARISON_STANDARD_D(resultD.z, 47.28));
		CHECK(G_COMPARISON_STANDARD_D(resultD.w, 41.82));
	}

}

TEST_CASE("Transform a vector by matrix.", "[TransformF], [TransformD]")
{
	GVECTORF vF = { 5.2f, 3.4f, 2.0f, 1.0f };
	GMATRIXF mF = { 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	GVECTORF resultF;

	GVECTORD vD = { 5.2, 3.4, 2.0, 1.0 };
	GMATRIXD mD = { 0.0, -1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };
	GVECTORD resultD;

	SECTION("Float vector.", "[TransformF]")
	{
		CHECK(G_SUCCESS(VectorC->TransformF(vF, mF, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.x, 3.4f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.y, -5.2f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.z, 2.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.w, 1.0f));
	}
	SECTION("Double vector.", "[TransformD]")
	{
		CHECK(G_SUCCESS(VectorC->TransformD(vD, mD, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.x, 3.4));
		CHECK(G_COMPARISON_STANDARD_D(resultD.y, -5.2));
		CHECK(G_COMPARISON_STANDARD_D(resultD.z, 2.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.w, 1.0));
	}

}

TEST_CASE("Calculate the magnitude of the vector.", "[MagnitudeF], [MagnitudeD]")
{
	GVECTORF v0F = { 0.0f, 0.0f, 0.0f, 0.0f };
	GVECTORF vF = { 5.2f, 3.4f, 2.0f, 1.0f };
	float resultF;

	GVECTORD v0D = { 0.0, 0.0, 0.0, 0.0 };
	GVECTORD vD = { 5.2, 3.4, 2.0, 1.0 };
	double resultD;
	SECTION("Float vector.", "[MagnitudeF]")
	{
		//Fail cases
		CHECK(G_FAIL(VectorC->MagnitudeF(v0F, resultF)));

		//Pass cases
		CHECK(G_SUCCESS(VectorC->MagnitudeF(vF, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF, 6.60302960f));
	}
	SECTION("Double vector.", "[MagnitudeD]")
	{
		//Fail cases
		CHECK(G_FAIL(VectorC->MagnitudeD(v0D, resultD)));

		//Pass cases
		CHECK(G_SUCCESS(VectorC->MagnitudeD(vD, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD, 6.60302960768767112));
	}

}

TEST_CASE("Normalize the vector.", "[NormalizeF], [NormalizeD]")
{
	GVECTORF v0F = { 0.0f, 0.0f, 0.0f, 0.0f };
	GVECTORF vF = { 5.2f, 3.4f, 2.0f, 1.0f };
	GVECTORF resultF;

	GVECTORD v0D = { 0.0, 0.0, 0.0, 0.0 };
	GVECTORD vD = { 5.2, 3.4, 2.0, 1.0 };
	GVECTORD resultD;
	SECTION("Float vector.", "[NormalizeF]")
	{
		//Fail cases
		CHECK(G_FAIL(VectorC->NormalizeF(v0F, resultF)));

		//Pass cases
		CHECK(G_SUCCESS(VectorC->NormalizeF(vF, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.x, 0.7875172f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.y, 0.5149151f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.z, 0.3028912f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.w, 0.1514456f));
	}
	SECTION("Double vector.", "[NormalizeD]")
	{
		//Fail cases
		CHECK(G_FAIL(VectorC->NormalizeD(v0D, resultD)));

		//Pass cases
		CHECK(G_SUCCESS(VectorC->NormalizeD(vD, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.x, 0.7875172926599974));
		CHECK(G_COMPARISON_STANDARD_D(resultD.y, 0.5149151528930752));
		CHECK(G_COMPARISON_STANDARD_D(resultD.z, 0.3028912664076913));
		CHECK(G_COMPARISON_STANDARD_D(resultD.w, 0.1514456332038456));
	}

}

TEST_CASE("Lerp between two vectors.", "[LerpF], [LerpD]")
{
	GVECTORF vF1 = { 5.2f, 3.4f, 2.0f, 1.0f };
	GVECTORF vF2 = { 0.2f, 1.0f, 2.5f, 0.4f };
	GVECTORF resultF;

	GVECTORD vD1 = { 5.2, 3.4, 2.0, 1.0 };
	GVECTORD vD2 = { 0.2, 1.0, 2.5, 0.4 };
	GVECTORD resultD;

	SECTION("Float vector.", "[LerpF]")
	{
		CHECK(G_SUCCESS(VectorC->LerpF(vF1, vF2, 0.5f, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.x, 2.7f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.y, 2.2f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.z, 2.25f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.w, 0.7f));
	}
	SECTION("Double vector.", "[LerpD]")
	{
		CHECK(G_SUCCESS(VectorC->LerpD(vD1, vD2, 0.5, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.x, 2.7));
		CHECK(G_COMPARISON_STANDARD_D(resultD.y, 2.2));
		CHECK(G_COMPARISON_STANDARD_D(resultD.z, 2.25));
		CHECK(G_COMPARISON_STANDARD_D(resultD.w, 0.7));
	}

}

TEST_CASE("Spline between two vectors.", "[SlerpF], [SlerpD]")
{
	GVECTORF vF1 = { 0,0,0,0 };
	GVECTORF vF2 = { 1,1,0,0 };
	GVECTORF vF3 = { 3,1,0,0 };
	GVECTORF vF4 = { 4,0,0,0 };
	GVECTORF resultF;

	GVECTORD vD1 = { 0,0,0,0 };
	GVECTORD vD2 = { 1,1,0,0 };
	GVECTORD vD3 = { 3,1,0,0 };
	GVECTORD vD4 = { 4,0,0,0 };
	GVECTORD resultD;

	float ratioF = 0.5f;
	double ratioD = 0.5;
	
	SECTION("Float vector.", "[SlerpF]")
	{
		CHECK(G_SUCCESS(VectorC->SplineF(vF1, vF2, vF3, vF4, ratioF, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.x, 2.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.y, 1.1614983f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.z, 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.w, 0.0f));
	}
	SECTION("Double vector.", "[SlerpD]")
	{
		CHECK(G_SUCCESS(VectorC->SplineD(vD1, vD2, vD3, vD4, ratioD, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.x, 2));
		CHECK(G_COMPARISON_STANDARD_D(resultD.y, 1.1614983745349439));
		CHECK(G_COMPARISON_STANDARD_D(resultD.z, 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.w, 0.0));
	}

	VectorC->DecrementCount();
}