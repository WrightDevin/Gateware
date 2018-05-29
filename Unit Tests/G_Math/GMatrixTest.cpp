#include "../Common.h"


//THESE TEST CASES ARE SET UP IN A SPECIFIC ORDER. REORDERING TEST CASES COULD CAUSE
//CRASHES, FALSE FAILURES, or FALSE PASSES.

using namespace GW;
using namespace MATH;

//Globals used for all test cases.
GMatrix* MatrixC;


// ALL DEVELOPERS!!! USE THIS AS AN EXAMPLE OF HOW TO DO CORE GINTERFACE TESTING!!!
GW::MATH::GMatrix *GMatrix_specific = nullptr;
GW::CORE::GInterface *GMatrix_generic = nullptr;
// CORE GINTERFACE TEST BATTERY. ALL GATEWARE INTERFACES MUST BE ABLE TO PASS THESE TESTS.
TEST_CASE("GMatrix core test battery", "[CreateGMatrix], [RequestInterface], [IncrementCount], [DecrementCount], [GetCount]")
{
	// CATCH WARNING!!!
	// Any variables declared here will be REPLICATED to EACH SECTION.
	// If you need connectivity between sections your variables will need to be global or static.
	unsigned int countS = 0, countG = 0;
	const GW::GUUIID notAnValidInterface = { 0, };

	// THE CREATION FUNCTION IS UNIQUE MOST EVERYTHING BELOW THIS SHOULD BE THE SAME FOR ALL INTERFACES
	SECTION("Creation Tests", "[CreateGMatrix]")
	{
		CHECK(GW::MATH::CreateGMatrix(nullptr) == GW::INVALID_ARGUMENT);
		// TODO: Add additonal Creation parameter testing here as nessasary.
		REQUIRE(G_SUCCESS(GW::MATH::CreateGMatrix(&GMatrix_specific)));
		REQUIRE(GMatrix_specific != nullptr);
	}
	// The following tests can be copied verbatim as they are completly GMatrix_generic for all interfaces
	SECTION("Interface Request Tests", "[RequestInterface]")
	{
		CHECK(GMatrix_specific->RequestInterface(notAnValidInterface, nullptr) == GW::INVALID_ARGUMENT);
		CHECK(GMatrix_specific->RequestInterface(notAnValidInterface, (void**)&GMatrix_generic) == GW::INTERFACE_UNSUPPORTED);
		CHECK(GMatrix_generic == nullptr); // should not have changed yet
		REQUIRE(G_SUCCESS(GMatrix_specific->RequestInterface(GW::CORE::GInterfaceUUIID, (void**)&GMatrix_generic)));
		REQUIRE(GMatrix_generic != nullptr);
		// memory addresses should match
		REQUIRE(reinterpret_cast<std::uintptr_t>(GMatrix_generic) == reinterpret_cast<std::uintptr_t>(GMatrix_specific));
	}
	// Test reference counting behavior
	SECTION("Reference Counting Tests", "[GetCount], [IncrementCount], [DecrementCount]")
	{
		REQUIRE(G_SUCCESS(GMatrix_specific->GetCount(countS)));
		REQUIRE(G_SUCCESS(GMatrix_generic->GetCount(countG)));
		CHECK(countS == countG);
		CHECK(countS == 2); // should be exactly 2 references at this point
		REQUIRE(G_SUCCESS(GMatrix_specific->IncrementCount())); // 3
		REQUIRE(G_SUCCESS(GMatrix_generic->IncrementCount())); // 4
		GMatrix_specific->GetCount(countS);
		GMatrix_generic->GetCount(countG);
		CHECK(countS == countG);
		CHECK(countS == 4); // should be exactly 4 references at this point
		REQUIRE(G_SUCCESS(GMatrix_specific->DecrementCount())); // 3
		REQUIRE(G_SUCCESS(GMatrix_generic->DecrementCount())); // 2
		// Free GMatrix_specific pointer (user simulation of interface deletion)
		CHECK(G_SUCCESS(GMatrix_specific->DecrementCount())); // 1
		GMatrix_specific = nullptr; // this pointer should not longer be valid from users standpoint (though it is)
		GMatrix_generic->GetCount(countG);
		REQUIRE(countG == 1); // should be last remaining handle
	}
	// Finally test interface Forward Compatibilty
	SECTION("Forward Compatibility Tests", "[RequestInterface], [GetCount], [DecrementCount]")
	{
		CHECK(GMatrix_generic->RequestInterface(notAnValidInterface, nullptr) == GW::INVALID_ARGUMENT);
		CHECK(GMatrix_generic->RequestInterface(notAnValidInterface, (void**)&GMatrix_specific) == GW::INTERFACE_UNSUPPORTED);
		CHECK(GMatrix_specific == nullptr); // should not have changed yet
		// TODO: Check that GMatrix_generic interface supports upgrading to ALL relevant interfaces in the class heirarchy chain
		REQUIRE(G_SUCCESS(GMatrix_generic->RequestInterface(GW::MATH::GMatrixUUIID, (void**)&GMatrix_specific))); // 2
		CHECK(GMatrix_specific != nullptr); // GMatrix_specific pointer is valid again
		GW::CORE::GSingleThreaded *singleSupport = nullptr;
		GW::CORE::GMultiThreaded *multiSupport = nullptr;
		REQUIRE(G_SUCCESS(GMatrix_generic->RequestInterface(GW::CORE::GSingleThreadedUUIID, (void**)&singleSupport)));// 3
		CHECK(singleSupport != nullptr); // GMatrix IS singlethreaded
		REQUIRE(G_FAIL(GMatrix_generic->RequestInterface(GW::CORE::GMultiThreadedUUIID, (void**)&multiSupport)));
		CHECK(multiSupport == nullptr); // GMatrix is NOT multithreaded
		// Check final count VS expectations
		REQUIRE(G_SUCCESS(singleSupport->GetCount(countS)));
		CHECK(countS == 3); // three valid handles should exist now
		// Free all handles, all should succeed
		REQUIRE(G_SUCCESS(singleSupport->DecrementCount())); // 2
		REQUIRE(G_SUCCESS(GMatrix_specific->DecrementCount())); // 1
		GMatrix_generic->GetCount(countG);
		REQUIRE(countG == 1); // should be last remaining handle (again)
		REQUIRE(G_SUCCESS(GMatrix_generic->DecrementCount())); // 0
	}
	// done with standard tests, the memory for the object should be released at this point and all pointers should be invalid
}

// Custom Unit Tests specific to this interface follow..



TEST_CASE("Create GMatrix.", "[CreateGMatrix]")
{
	//Fail cases
	CHECK(G_FAIL(CreateGMatrix(nullptr)));

	//Pass Cases
	REQUIRE(G_SUCCESS(CreateGMatrix(&MatrixC)));
}

TEST_CASE("Add two matrices.", "[AddMatrixF], [AddMatrixD]")
{
	GMATRIXF mF1 = { 0.0f,-1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	GMATRIXF mF2 = { 0.2f, 1.0f, 2.5f, 0.4f, 0.7f, 5.9f, 2.2f, 4.1f, 3.8f, 0.0f, 8.5f, 12.4f, 7.6f, 5.5f, 9.8f, 1.0f };
	GMATRIXF resultF;


	GMATRIXD mD1 = { 0.0,-1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };
	GMATRIXD mD2 = { 0.2, 1.0, 2.5, 0.4, 0.7, 5.9, 2.2, 4.1, 3.8, 0.0, 8.5, 12.4, 7.6, 5.5, 9.8, 1.0 };
	GMATRIXD resultD;

	//Fail cases
	SECTION("Float matrix addition.", "[AddMatrixF]")
	{
		CHECK(G_SUCCESS(MatrixC->AddMatrixF(mF1, mF2, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[0], 0.2f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[1], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[2], 2.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[3], 0.4f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[4], 1.7f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[5], 5.9f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[6], 2.2f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[7], 4.1f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[8], 3.8f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[9], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[10], 9.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[11], 12.4f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[12], 7.6f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[13], 5.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[14], 9.8f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[15], 2.0f));
	}
	SECTION("Double matrix addition.", "[AddMatrixD]")
	{
		CHECK(G_SUCCESS(MatrixC->AddMatrixD(mD1, mD2, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[0], 0.2));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[1], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[2], 2.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[3], 0.4));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[4], 1.7));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[5], 5.9));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[6], 2.2));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[7], 4.1));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[8], 3.8));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[9], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[10], 9.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[11], 12.4));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[12], 7.6));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[13], 5.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[14], 9.8));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[15], 2.0));
	}

}

TEST_CASE("Subtract two matrices.", "[SubtractMatrixF], [SubtractMatrixD]")
{
	GMATRIXF mF1 = { 0.0f,-1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	GMATRIXF mF2 = { 0.2f, 1.0f, 2.5f, 0.4f, 0.7f, 5.9f, 2.2f, 4.1f, 3.8f, 0.0f, 8.5f, 12.4f, 7.6f, 5.5f, 9.8f, 1.0f };
	GMATRIXF resultF;


	GMATRIXD mD1 = { 0.0,-1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };
	GMATRIXD mD2 = { 0.2, 1.0, 2.5, 0.4, 0.7, 5.9, 2.2, 4.1, 3.8, 0.0, 8.5, 12.4, 7.6, 5.5, 9.8, 1.0 };
	GMATRIXD resultD;

	//Fail cases
	SECTION("Float matrix subtraction.", "[SubtractMatrixF]")
	{
		CHECK(G_SUCCESS(MatrixC->SubtractMatrixF(mF1, mF2, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[0], -0.2f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[1], -2.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[2], -2.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[3], -0.4f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[4], 0.3f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[5], -5.9f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[6], -2.2f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[7], -4.1f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[8], -3.8f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[9], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[10], -7.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[11], -12.4f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[12], -7.6f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[13], -5.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[14], -9.8f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[15], 0.0f));
	}
	SECTION("Double matrix subtraction.", "[SubtractMatrixD]")
	{
		CHECK(G_SUCCESS(MatrixC->SubtractMatrixD(mD1, mD2, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[0], -0.2));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[1], -2.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[2], -2.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[3], -0.4));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[4], 0.3));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[5], -5.9));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[6], -2.2));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[7], -4.1));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[8], -3.8));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[9], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[10], -7.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[11], -12.4));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[12], -7.6));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[13], -5.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[14], -9.8));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[15], 0.0));
	}

}

TEST_CASE("Multiply a matrix by a matrix.", "[MultiplyMatrixF], [MultiplyMatrixD]")
{
	GMATRIXF mF1 = { 0.0f,-1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	GMATRIXF mF2 = { 0.2f, 1.0f, 2.5f, 0.4f, 0.7f, 5.9f, 2.2f, 4.1f, 3.8f, 0.0f, 8.5f, 12.4f, 7.6f, 5.5f, 9.8f, 1.0f };
	GMATRIXF resultF;


	GMATRIXD mD1 = { 0.0,-1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };
	GMATRIXD mD2 = { 0.2, 1.0, 2.5, 0.4, 0.7, 5.9, 2.2, 4.1, 3.8, 0.0, 8.5, 12.4, 7.6, 5.5, 9.8, 1.0 };
	GMATRIXD resultD;

	SECTION("Float matrix multiplication.", "[MultiplyMatrixF]")
	{
		CHECK(G_SUCCESS(MatrixC->MultiplyMatrixF(mF1, mF2, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[0], -0.7f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[1], -5.9f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[2], -2.2f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[3], -4.1f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[4], 0.2f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[5], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[6], 2.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[7], 0.4f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[8], 3.8f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[9], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[10], 8.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[11], 12.4f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[12], 7.6f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[13], 5.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[14], 9.8f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[15], 1.0f));
	}
	SECTION("Double matrix multiplication.", "[MultiplyMatrixD]")
	{
		CHECK(G_SUCCESS(MatrixC->MultiplyMatrixD(mD1, mD2, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[0], -0.7));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[1], -5.9));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[2], -2.2));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[3], -4.1));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[4], 0.2));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[5], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[6], 2.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[7], 0.4));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[8], 3.8));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[9], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[10], 8.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[11], 12.4));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[12], 7.6));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[13], 5.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[14], 9.8));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[15], 1.0));
	}

}

TEST_CASE("Multiply a vector by a matrix.", "[VectorXMatrixF], [VectorXMatrixD]")
{
	GVECTORF vF = { 1.0f,-0.2f, 0.3f, 0.4f };
	GMATRIXF mF = { 0.2f, 1.0f, 2.5f, 0.4f, 0.7f, 5.9f, 2.2f, 4.1f, 3.8f, 0.0f, 8.5f, 12.4f, 7.6f, 5.5f, 9.8f, 1.0f };
	GVECTORF resultF;


	GVECTORD vD = { 1.0,-1.0, 0.3, 0.4 };
	GMATRIXD mD = { 0.2, 1.0, 2.5, 0.4, 0.7, 5.9, 2.2, 4.1, 3.8, 0.0, 8.5, 12.4, 7.6, 5.5, 9.8, 1.0 };
	GVECTORD resultD;

	SECTION("Float matrix multiplication.", "[VectorXMatrixF]")
	{
		CHECK(G_SUCCESS(MatrixC->VectorXMatrixF(mF, vF, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[0], 4.24f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[1], 2.02f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[2], 8.53f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[3], 3.7f));
	}
	SECTION("Double matrix multiplication.", "[VectorXMatrixD]")
	{
		CHECK(G_SUCCESS(MatrixC->VectorXMatrixD(mD, vD, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[0], 3.68));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[1], -2.7));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[2], 6.77));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[3], 0.42));
	}

}

TEST_CASE("Convert a quaternion to a rotation matrix.", "[ConvertQuaternionF], [ConvertQuaternionD]")
{
	GQUATERNIONF qF = { 0.0f, 0.0f, 0.70710678f, 0.70710678f };
	GMATRIXF resultF;


	GQUATERNIOND qD = { 0.0, 0.0, 0.7071067811865475, 0.7071067811865475 };
	GMATRIXD resultD;
	//Fail cases
	SECTION("Float matrix convert.", "[ConvertQuaternionF]")
	{
		CHECK(G_SUCCESS(MatrixC->ConvertQuaternionF(qF, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[0], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[1], -1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[2], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[3], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[4], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[5], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[6], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[7], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[8], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[9], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[10], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[11], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[12], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[13], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[14], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[15], 1.0f));
	}
	SECTION("Double matrix Multiplication.", "[ConvertQuaternionD]")
	{
		CHECK(G_SUCCESS(MatrixC->ConvertQuaternionD(qD, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[0], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[1], -1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[2], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[3], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[4], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[5], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[6], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[7], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[8], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[9], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[10], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[11], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[12], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[13], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[14], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[15], 1.0));
	}

}

TEST_CASE("Multiply a matrix by a number.", "[MultiplyNumF], [MultiplyNumD]")
{
	GMATRIXF mF = { 0.2f, 1.0f, 2.5f, 0.4f, 0.7f, 5.9f, 2.2f, 4.1f, 3.8f, 0.0f, 8.5f, 12.4f, 7.6f, 5.5f, 9.8f, 1.0f };
	GMATRIXF resultF;


	GMATRIXD mD = { 0.2, 1.0, 2.5, 0.4, 0.7, 5.9, 2.2, 4.1, 3.8, 0.0, 8.5, 12.4, 7.6, 5.5, 9.8, 1.0 };
	GMATRIXD resultD;

	SECTION("Float matrix multiplication.", "[MultiplyNumF]")
	{
		CHECK(G_SUCCESS(MatrixC->MultiplyNumF(mF, -0.3f, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[0], -0.06f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[1], -0.3f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[2], -0.75f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[3], -0.12f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[4], -0.21f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[5], -1.77f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[6], -0.66f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[7], -1.23f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[8], -1.14f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[9], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[10], -2.55f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[11], -3.72f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[12], -2.28f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[13], -1.65f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[14], -2.94f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[15], -0.3f));
	}
	SECTION("Double matrix multiplication.", "[MultiplyNumD]")
	{
		CHECK(G_SUCCESS(MatrixC->MultiplyNumD(mD, -0.3, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[0], -0.06));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[1], -0.3));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[2], -0.75));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[3], -0.12));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[4], -0.21));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[5], -1.77));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[6], -0.66));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[7], -1.23));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[8], -1.14));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[9], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[10], -2.55));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[11], -3.72));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[12], -2.28));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[13], -1.65));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[14], -2.94));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[15], -0.3));
	}

}

TEST_CASE("Calculate a determinant of a matrix.", "[DeterminantF], [DeterminantD]")
{
	GMATRIXF mF = { 0.2f, 1.0f, 2.5f, 0.4f, 0.7f, 5.9f, 2.2f, 4.1f, 3.8f, 0.0f, 8.5f, 12.4f, 7.6f, 5.5f, 9.8f, 1.0f };
	float resultF;

	GMATRIXD mD = { 0.2, 1.0, 2.5, 0.4, 0.7, 5.9, 2.2, 4.1, 3.8, 0.0, 8.5, 12.4, 7.6, 5.5, 9.8, 1.0 };
	double resultD;

	SECTION("Float matrix determinant.", "[DeterminantF]")
	{
		MatrixC->DeterminantF(mF, resultF);
		CHECK(G_COMPARISON_STANDARD_F(resultF, 1209.6248f));
	}
	SECTION("Double matrix determinant.", "[DeterminantD]")
	{
		MatrixC->DeterminantD(mD, resultD);
		CHECK(G_COMPARISON_STANDARD_D(resultD, 1209.6248));
	}

}

TEST_CASE("Transpose a matrix.", "[TransposeF], [TransposeD]")
{
	GMATRIXF mF = { 0.2f, 1.0f, 2.5f, 0.4f, 0.7f, 5.9f, 2.2f, 4.1f, 3.8f, 0.0f, 8.5f, 12.4f, 7.6f, 5.5f, 9.8f, 1.0f };
	GMATRIXF resultF;

	GMATRIXD mD = { 0.2, 1.0, 2.5, 0.4, 0.7, 5.9, 2.2, 4.1, 3.8, 0.0, 8.5, 12.4, 7.6, 5.5, 9.8, 1.0 };
	GMATRIXD resultD;

	SECTION("Float matrix transpose.", "[TransposeF]")
	{
		CHECK(G_SUCCESS(MatrixC->TransposeF(mF, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[0], 0.2f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[1], 0.7f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[2], 3.8f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[3], 7.6f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[4], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[5], 5.9f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[6], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[7], 5.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[8], 2.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[9], 2.2f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[10], 8.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[11], 9.8f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[12], 0.4f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[13], 4.1f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[14], 12.4f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[15], 1.0f));
	}
	SECTION("Double matrix transpose.", "[TransposeD]")
	{
		CHECK(G_SUCCESS(MatrixC->TransposeD(mD, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[0], 0.2));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[1], 0.7));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[2], 3.8));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[3], 7.6));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[4], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[5], 5.9));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[6], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[7], 5.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[8], 2.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[9], 2.2));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[10], 8.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[11], 9.8));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[12], 0.4));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[13], 4.1));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[14], 12.4));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[15], 1.0));
	}

}

TEST_CASE("Inverse a matrix.", "[InverseF], [InverseD]")
{
	GMATRIXF mF = { 0.2f, 1.0f, 2.5f, 0.4f, 0.7f, 5.9f, 2.2f, 4.1f, 3.8f, 0.0f, 8.5f, 12.4f, 7.6f, 5.5f, 9.8f, 1.0f };
	GMATRIXF resultF;

	GMATRIXD mD = { 0.2, 1.0, 2.5, 0.4, 0.7, 5.9, 2.2, 4.1, 3.8, 0.0, 8.5, 12.4, 7.6, 5.5, 9.8, 1.0 };
	GMATRIXD resultD;

	SECTION("Float matrix inverse.", "[InverseF]")
	{
		CHECK(G_SUCCESS(MatrixC->InverseF(mF, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[0], -0.58567995f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[1], -0.03205952f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[2], 0.01813206f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[3], 0.14087839f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[4], -0.00634742f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[5], 0.15918324f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[6], -0.05341326f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[7], 0.01221205f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[8], 0.47249858f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[9], -0.07040200f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[10], 0.00887383f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[11], -0.01038669f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[12], -0.14440759f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[13], 0.05808413f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[14], 0.06900569f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[15], -0.03605250f));
	}
	SECTION("Double matrix inverse.", "[InverseD]")
	{
		CHECK(G_SUCCESS(MatrixC->InverseD(mD, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[0], -0.5856799562971923));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[1], -0.0320595278800501));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[2], 0.0181320687208133));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[3], 0.1408783946889978));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[4], -0.0063474227710940));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[5], 0.1591832442588809));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[6], -0.0534132567387838));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[7], 0.0122120512079448));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[8], 0.4724985797248866));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[9], -0.0704019957262781));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[10], 0.0088738259995992));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[11], -0.0103866918072447));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[12], -0.1444075882042101));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[13], 0.0580841265820608));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[14], 0.0690056949890578));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[15], -0.0360525015690816));
	}

}

TEST_CASE("Set a matrix to an identity matrix.", "[IdentityF], [IdentityD]")
{
	GMATRIXF resultF;

	GMATRIXD resultD;
	SECTION("Float identity matrix.", "[IdentityF]")
	{
		CHECK(G_SUCCESS(MatrixC->IdentityF(resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[0], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[1], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[2], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[3], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[4], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[5], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[6], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[7], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[8], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[9], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[10], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[11], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[12], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[13], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[14], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[15], 1.0f));
	}
	SECTION("Double identity matrix.", "[IdentityD]")
	{
		CHECK(G_SUCCESS(MatrixC->IdentityD(resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[0], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[1], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[2], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[3], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[4], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[5], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[6], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[7], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[8], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[9], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[10], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[11], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[12], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[13], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[14], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[15], 1.0));
	}

}

TEST_CASE("Get a roatation matrix form a transform matrix.", "[GetRotationF], [GetRotationD]")
{
	GMATRIXF mF = { -2.0f, -1.0f, 0.0f, 2.0f, -2.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	GQUATERNIONF resultF;

	GMATRIXD mD = { -2.0, -1.0, 0.0, 2.0, -2.0, 1.0, 0.0, -1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
	GQUATERNIOND resultD;
	SECTION("Float matrix.", "[GetRotationF]")
	{
		CHECK(G_SUCCESS(MatrixC->GetRotationF(mF, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[0], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[1], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[2], 0.38268343f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[3], 0.92387953f));
	}
	SECTION("Double matrix.", "[GetRotationD]")
	{
		CHECK(G_SUCCESS(MatrixC->GetRotationD(mD, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[0], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[1], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[2], 0.3826834323650898));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[3], 0.9238795325112867));
	}

}

TEST_CASE("Get a translation matrix form a transform matrix.", "[GetTranslationF], [GetTranslationD]")
{
	GMATRIXF mF = { -2.0f, -1.0f, 0.0f, 2.0f, -2.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	GVECTORF resultF;

	GMATRIXD mD = { -2.0, -1.0, 0.0, 2.0, -2.0, 1.0, 0.0, -1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
	GVECTORD resultD;

	SECTION("Float matrix.", "[GetTranslationF]")
	{
		CHECK(G_SUCCESS(MatrixC->GetTranslationF(mF, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[0], 2.0F));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[1], -1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[2], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[3], 0.0f));
	}
	SECTION("Double matrix.", "[GetTranslationD]")
	{
		CHECK(G_SUCCESS(MatrixC->GetTranslationD(mD, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[0], 2));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[1], -1));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[2], 1));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[3], 0.0));
	}

}

TEST_CASE("Get a scale matrix form a transform matrix.", "[GetScaleF], [GetScaleD]")
{
	GMATRIXF mF = { -2.0f, -1.0f, 0.0f, 2.0f, -2.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	GVECTORF resultF;

	GMATRIXD mD = { -2.0, -1.0, 0.0, 2.0, -2.0, 1.0, 0.0, -1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
	GVECTORD resultD;
	SECTION("Float matrix.", "[GetScaleF]")
	{
		CHECK(G_SUCCESS(MatrixC->GetScaleF(mF, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[0], -2.82842712f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[1], 1.41421356f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[2], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[3], 0.0f));
	}
	SECTION("Double matrix.", "[GetScaleD]")
	{
		CHECK(G_SUCCESS(MatrixC->GetScaleD(mD, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[0], -2.8284271247461903));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[1], 1.4142135623730951));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[2], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[3], 0.0));
	}

}

TEST_CASE("Rotate a specified matrix around the x-axis.", "[RotationXF], [RotationXD]")
{
	GMATRIXF mF = { -2.0f, -1.0f, 0.0f, 2.0f, -2.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	GMATRIXF resultF;

	GMATRIXD mD = { -2.0, -1.0, 0.0, 2.0, -2.0, 1.0, 0.0, -1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
	GMATRIXD resultD;

	SECTION("Float matrix rotation.", "[RotationXF]")
	{
		CHECK(G_SUCCESS(MatrixC->RotationXF(mF, (float)G_PI / 2.0f, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[0], -2.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[1], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[2], -1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[3], 2.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[4], -2.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[5], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[6], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[7], -1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[8], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[9], -1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[10], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[11], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[12], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[13], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[14], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[15], 1.0f));
	}
	SECTION("Double matrix rotation.", "[RotationXD]")
	{
		CHECK(G_SUCCESS(MatrixC->RotationXD(mD, G_PI / 2.0, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[0], -2.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[1], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[2], -1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[3], 2.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[4], -2.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[5], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[6], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[7], -1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[8], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[9], -1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[10], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[11], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[12], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[13], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[14], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[15], 1.0));
	}

}

TEST_CASE("Rotate a specified matrix around the y-axis.", "[RotationYF], [RotationYD]")
{
	GMATRIXF mF = { -2.0f, -1.0f, 0.0f, 2.0f, -2.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	GMATRIXF resultF;

	GMATRIXD mD = { -2.0, -1.0, 0.0, 2.0, -2.0, 1.0, 0.0, -1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
	GMATRIXD resultD;

	SECTION("Float matrix rotation.", "[RotationYF]")
	{
		CHECK(G_SUCCESS(MatrixC->RotationYF(mF, (float)G_PI / 2.0f, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[0], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[1], -1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[2], 2.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[3], 2.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[4], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[5], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[6], 2.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[7], -1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[8], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[9], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[10], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[11], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[12], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[13], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[14], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[15], 1.0f));
	}
	SECTION("Double matrix rotation.", "[RotationYD]")
	{
		CHECK(G_SUCCESS(MatrixC->RotationYD(mD, G_PI / 2.0, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[0], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[1], -1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[2], 2.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[3], 2.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[4], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[5], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[6], 2.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[7], -1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[8], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[9], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[10], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[11], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[12], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[13], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[14], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[15], 1.0));
	}

}

TEST_CASE("Rotate a specified matrix around the z-axis.", "[RotationZF], [RotationZD]")
{
	GMATRIXF mF = { -2.0f, -1.0f, 0.0f, 2.0f, -2.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	GMATRIXF resultF;

	GMATRIXD mD = { -2.0, -1.0, 0.0, 2.0, -2.0, 1.0, 0.0, -1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
	GMATRIXD resultD;

	SECTION("Float matrix rotation.", "[RotationZF]")
	{
		CHECK(G_SUCCESS(MatrixC->RotationZF(mF, (float)G_PI / 2.0f, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[0], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[1], -2.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[2], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[3], 2.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[4], -1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[5], -2.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[6], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[7], -1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[8], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[9], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[10], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[11], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[12], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[13], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[14], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[15], 1.0f));
	}
	SECTION("Double matrix rotation.", "[RotationZD]")
	{
		CHECK(G_SUCCESS(MatrixC->RotationZD(mD, G_PI / 2.0, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[0], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[1], -2.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[2], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[3], 2.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[4], -1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[5], -2.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[6], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[7], -1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[8], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[9], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[10], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[11], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[12], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[13], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[14], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[15], 1.0));
	}

}


TEST_CASE("Rotate a specified vector by rotating Yaw, Pitch and Roll axis.", "[RotationYawPitchRollF], [RotationYawPitchRollD]")
{
	GVECTORF vF = { 1.0f, 0.0f, 0.0f, 1.0f };
	GMATRIXF rotMatF;
	GVECTORF resultF;

	GVECTORD vD = { 1.0, 0.0, 0.0, 1.0 };
	GMATRIXD rotMatD;
	GVECTORD resultD;

	SECTION("Float matrix rotation.", "[RotationYawPitchRollF]")
	{
		CHECK(G_SUCCESS(MatrixC->RotationYawPitchRollF(G_DEGREE_TO_RADIAN(90), G_DEGREE_TO_RADIAN(0), G_DEGREE_TO_RADIAN(90), rotMatF)));
		MatrixC->VectorXMatrixF(rotMatF, vF, resultF);
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[0], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[1], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[2], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[3], 1.0f));

	}
	SECTION("Double matrix rotation.", "[RotationYawPitchRollD")
	{
		CHECK(G_SUCCESS(MatrixC->RotationYawPitchRollD(G_DEGREE_TO_RADIAN(90), G_DEGREE_TO_RADIAN(90), G_DEGREE_TO_RADIAN(90), rotMatD)));
		MatrixC->VectorXMatrixD(rotMatD, vD, resultD);
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[0], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[1], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[2], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[3], 1.0));
	}
}

TEST_CASE("Rotate the vector by a specified vector and angle.", "[RotationByVectorF], [RotationByVectorD]")
{
	GVECTORF vF = { 1.0f, 0.0f, 0.0f, 1.0f };
	GVECTORF axisF = { 0.0f, 0.0f, 1.0f, 1.0f };
	GMATRIXF rotMatF;
	GVECTORF resultF;

	GVECTORD vD = { 1.0, 0.0, 0.0, 1.0 };
	GVECTORD axisD = { 0.0, 0.0, 1.0, 1.0 };
	GMATRIXD rotMatD;
	GVECTORD resultD;

	SECTION("Float vector rotation.", "[RotationByVectorF]")
	{
		CHECK(G_SUCCESS(MatrixC->RotationByVectorF(axisF, G_DEGREE_TO_RADIAN(90), rotMatF)));
		MatrixC->VectorXMatrixF(rotMatF, vF, resultF);
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[0], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[1], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[2], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[3], 1.0f));
	}
	SECTION("Double vector rotation.", "[RotationByVectorD]")
	{
		CHECK(G_SUCCESS(MatrixC->RotationByVectorD(axisD, G_DEGREE_TO_RADIAN(90), rotMatD)));
		MatrixC->VectorXMatrixD(rotMatD, vD, resultD);
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[0], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[1], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[2], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[3], 1.0));
	}
}

TEST_CASE("Translate a specified matrix by the vector.", "[TranslatelocalF], [TranslatelocalD]")
{
	GMATRIXF mF = { -2.0f, -1.0f, 0.0f, 2.0f, -2.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	GVECTORF vF = { 0.3f, 2, -7, 0 };
	GMATRIXF resultF;

	GMATRIXD mD = { -2.0, -1.0, 0.0, 2.0, -2.0, 1.0, 0.0, -1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
	GVECTORD vD = { 0.3, 2, -7, 0 };
	GMATRIXD resultD;

	SECTION("Float matrix trasnlation.", "[TranslatelocalF]")
	{
		CHECK(G_SUCCESS(MatrixC->TranslatelocalF(mF, vF, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[0], -2.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[1], -1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[2], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[3], -0.6f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[4], -2.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[5], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[6], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[7], 0.4f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[8], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[9], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[10], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[11], -6.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[12], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[13], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[14], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[15], 1.0f));
	}
	SECTION("Double matrix trasnlation.", "[TranslatelocalD]")
	{
		CHECK(G_SUCCESS(MatrixC->TranslatelocalD(mD, vD, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[0], -2.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[1], -1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[2], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[3], -0.6));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[4], -2.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[5], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[6], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[7], 0.4));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[8], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[9], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[10], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[11], -6.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[12], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[13], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[14], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[15], 1.0));

	}

}

TEST_CASE("Scale a specified matrix by the vector.", "[ScalingF], [ScalingD]")
{
	GMATRIXF mF = { -2.0f, -1.0f, 0.0f, 2.0f, -2.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	GVECTORF vF = { 0.3f, 2, -7, 0 };
	GMATRIXF resultF;

	GMATRIXD mD = { -2.0, -1.0, 0.0, 2.0, -2.0, 1.0, 0.0, -1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
	GVECTORD vD = { 0.3, 2, -7, 0 };
	GMATRIXD resultD;

	SECTION("Float matrix Scaling.", "[ScalingF]")
	{
		CHECK(G_SUCCESS(MatrixC->ScalingF(mF, vF, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[0], -0.6f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[1], -2.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[2], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[3], 2.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[4], -0.6f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[5], 2.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[6], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[7], -1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[8], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[9], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[10], -7.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[11], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[12], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[13], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[14], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[15], 1.0f));
	}
	SECTION("Double matrix Scaling.", "[ScalingD]")
	{
		CHECK(G_SUCCESS(MatrixC->ScalingD(mD, vD, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[0], -0.6));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[1], -2.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[2], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[3], 2.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[4], -0.6));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[5], 2.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[6], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[7], -1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[8], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[9], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[10], -7.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[11], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[12], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[13], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[14], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[15], 1.0));
	}

}

TEST_CASE("Lerp between two matrices.", "[LerpF], [LerpD]")
{
	GMATRIXF mF1 = { -2.0f, -1.0f, 0.0f, 2.0f, -2.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	GMATRIXF mF2 = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
	GMATRIXF resultF;

	GMATRIXD mD1 = { -2.0, -1.0, 0.0, 2.0, -2.0, 1.0, 0.0, -1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
	GMATRIXD mD2 = { 1.0, 1.f, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
	GMATRIXD resultD;

	SECTION("Float matrix Scaling.", "[LerpF]")
	{
		CHECK(G_SUCCESS(MatrixC->LerpF(mF1, mF2, 0.5f, resultF)));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[0], -0.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[1], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[2], 0.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[3], 1.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[4], -0.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[5], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[6], 0.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[7], 0.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[8], 0.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[9], 0.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[10], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[11], 1.0f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[12], 0.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[13], 0.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[14], 0.5f));
		CHECK(G_COMPARISON_STANDARD_F(resultF.data[15], 1.0f));
	}
	SECTION("Double matrix Scaling.", "[LerpD]")
	{
		CHECK(G_SUCCESS(MatrixC->LerpD(mD1, mD2, 0.5, resultD)));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[0], -0.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[1], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[2], 0.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[3], 1.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[4], -0.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[5], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[6], 0.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[7], 0.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[8], 0.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[9], 0.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[10], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[11], 1.0));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[12], 0.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[13], 0.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[14], 0.5));
		CHECK(G_COMPARISON_STANDARD_D(resultD.data[15], 1.0));
	}

}

TEST_CASE("Free MatrixC", "[DecrementCount]")
{

	REQUIRE(G_SUCCESS(MatrixC->DecrementCount()));
}


