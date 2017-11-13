#include "../Unit Tests/Common.h"

#include <thread>
///=============================================================================
//==============================TEST CASES======================================
///=============================================================================

//THESE TEST CASES ARE SET UP IN A SPECIFIC ORDER. REORDERING TEST CASES COULD CAUSE
//CRASHES, FALSE FAILURES, or FALSE PASSES

//Globals needed for all test cases
GW::SYSTEM::GInput* input = nullptr;

/*
// ALL DEVELOPERS!!! USE THIS AS AN EXAMPLE OF HOW TO DO CORE GINTERFACE TESTING!!!
GW::SYSTEM::GInput *GInput_specific = nullptr;
GW::CORE::GInterface *GInput_generic = nullptr;
// CORE GINTERFACE TEST BATTERY. ALL GATEWARE INTERFACES MUST BE ABLE TO PASS THESE TESTS.
TEST_CASE("GInput core test battery", "[CreateGInput], [RequestInterface], [IncrementCount], [DecrementCount], [GetCount]")
{
	// CATCH WARNING!!!
	// Any variables declared here will be REPLICATED to EACH SECTION.
	// If you need connectivity between sections your variables will need to be global or static.
	unsigned int countS = 0, countG = 0;
	const GW::GUUIID notAnValidInterface = { 0, };

	// THE CREATION FUNCTION IS UNIQUE MOST EVERYTHING BELOW THIS SHOULD BE THE SAME FOR ALL INTERFACES
	SECTION("Creation Tests", "[CreateGInput]")
	{
		CHECK(GW::SYSTEM::CreateGInput(nullptr, 0, nullptr) == GW::INVALID_ARGUMENT);
		// TODO: Add additonal Creation parameter testing here as nessasary.
		REQUIRE(G_SUCCESS(GW::SYSTEM::CreateGInput((void*)window, sizeof(window), &GInput_specific)));
		REQUIRE(GInput_specific != nullptr);
	}
	// The following tests can be copied verbatim as they are completly GInput_generic for all interfaces
	SECTION("Interface Request Tests", "[RequestInterface]")
	{
		CHECK(GInput_specific->RequestInterface(notAnValidInterface, nullptr) == GW::INVALID_ARGUMENT);
		CHECK(GInput_specific->RequestInterface(notAnValidInterface, (void**)&GInput_generic) == GW::INTERFACE_UNSUPPORTED);
		CHECK(GInput_generic == nullptr); // should not have changed yet
		REQUIRE(G_SUCCESS(GInput_specific->RequestInterface(GW::CORE::GInterfaceUUIID, (void**)&GInput_generic)));
		REQUIRE(GInput_generic != nullptr);
		// memory addresses should match
		REQUIRE(reinterpret_cast<std::uintptr_t>(GInput_generic) == reinterpret_cast<std::uintptr_t>(GInput_specific));
	}
	// Test reference counting behavior
	SECTION("Reference Counting Tests", "[GetCount], [IncrementCount], [DecrementCount]")
	{
		REQUIRE(G_SUCCESS(GInput_specific->GetCount(countS)));
		REQUIRE(G_SUCCESS(GInput_generic->GetCount(countG)));
		CHECK(countS == countG);
		CHECK(countS == 2); // should be exactly 2 references at this point
		REQUIRE(G_SUCCESS(GInput_specific->IncrementCount())); // 3
		REQUIRE(G_SUCCESS(GInput_generic->IncrementCount())); // 4
		GInput_specific->GetCount(countS);
		GInput_generic->GetCount(countG);
		CHECK(countS == countG);
		CHECK(countS == 4); // should be exactly 4 references at this point
		REQUIRE(G_SUCCESS(GInput_specific->DecrementCount())); // 3
		REQUIRE(G_SUCCESS(GInput_generic->DecrementCount())); // 2
		// Free GInput_specific pointer (user simulation of interface deletion)
		CHECK(G_SUCCESS(GInput_specific->DecrementCount())); // 1
		GInput_specific = nullptr; // this pointer should not longer be valid from users standpoint (though it is)
		GInput_generic->GetCount(countG);
		REQUIRE(countG == 1); // should be last remaining handle
	}
	// Finally test interface Forward Compatibilty
	SECTION("Forward Compatibility Tests", "[RequestInterface], [GetCount], [DecrementCount]")
	{
		CHECK(GInput_generic->RequestInterface(notAnValidInterface, nullptr) == GW::INVALID_ARGUMENT);
		CHECK(GInput_generic->RequestInterface(notAnValidInterface, (void**)&GInput_specific) == GW::INTERFACE_UNSUPPORTED);
		CHECK(GInput_specific == nullptr); // should not have changed yet
		// TODO: Check that GInput_generic interface supports upgrading to ALL relevant interfaces in the class heirarchy chain
		REQUIRE(G_SUCCESS(GInput_generic->RequestInterface(GW::SYSTEM::GInputUUIID, (void**)&GInput_specific))); // 2
		CHECK(GInput_specific != nullptr); // GInput_specific pointer is valid again
		GW::CORE::GSingleThreaded *singleSupport = nullptr;
		GW::CORE::GMultiThreaded *multiSupport = nullptr;
		REQUIRE(G_SUCCESS(GInput_generic->RequestInterface(GW::CORE::GSingleThreadedUUIID, (void**)&singleSupport)));// 3
		CHECK(singleSupport != nullptr); // GInput IS singlethreaded
		REQUIRE(G_FAIL(GInput_generic->RequestInterface(GW::CORE::GMultiThreadedUUIID, (void**)&multiSupport)));
		CHECK(multiSupport == nullptr); // GInput is NOT multithreaded
		// Check final count VS expectations
		REQUIRE(G_SUCCESS(singleSupport->GetCount(countS)));
		CHECK(countS == 3); // three valid handles should exist now
		// Free all handles, all should succeed
		REQUIRE(G_SUCCESS(singleSupport->DecrementCount())); // 2
		REQUIRE(G_SUCCESS(GInput_specific->DecrementCount())); // 1
		GInput_generic->GetCount(countG);
		REQUIRE(countG == 1); // should be last remaining handle (again)
		REQUIRE(G_SUCCESS(GInput_generic->DecrementCount())); // 0
	}
	// done with standard tests, the memory for the object should be released at this point and all pointers should be invalid
}

// Custom Unit Tests specific to this interface follow..
*/

/*
TEST_CASE("CreateGInput Tests", "[CreateGInput]")
{
	//Check that these cases fail appropriately
	CHECK(GW::SYSTEM::CreateGInput(nullptr, 0, nullptr) == GW::INVALID_ARGUMENT);
	CHECK(GW::SYSTEM::CreateGInput(nullptr, 0, &input) == GW::INVALID_ARGUMENT);

#ifdef __linux__
	window->window = (void*)&mainWindow;
	window->display = (void*)display;
#endif

	//The following cases should pass
	REQUIRE(G_SUCCESS(GW::SYSTEM::CreateGInput((void*)window, sizeof(window), &input)));

	REQUIRE(input != nullptr);
}

//Commented out becasue of known linux bug

TEST_CASE("GInput Key/Button Down Tests")
{
	//Send the simulated input
#ifdef _WIN32
	SimulateInput(KEYEVENTF_SCANCODE);
#else
    SimulateInput(true);
#endif
	//Check the value of our stored keys
	GW::GReturn errorCode;
	//Check the number keys 1, 2, 3, 4
	CHECK(input->GetState(G_KEY_1, &errorCode) == 1);
	CHECK(input->GetState(G_KEY_2, &errorCode) == 1);
	CHECK(input->GetState(G_KEY_3, &errorCode) == 1);
	CHECK(input->GetState(G_KEY_4, &errorCode) == 1);

	//Check the letters A, S, D, W
	CHECK(input->GetState(G_KEY_A, &errorCode) == 1);
	CHECK(input->GetState(G_KEY_S, &errorCode) == 1);
	CHECK(input->GetState(G_KEY_D, &errorCode) == 1);
	CHECK(input->GetState(G_KEY_W, &errorCode) == 1);

	//Check the arrow keys Left, Right, Up, Down
	CHECK(input->GetState(G_KEY_LEFT, &errorCode) == 1); // Left Key
	CHECK(input->GetState(G_KEY_RIGHT, &errorCode) == 1); // Right Key
	CHECK(input->GetState(G_KEY_UP, &errorCode) == 1); // Up Key
	CHECK(input->GetState(G_KEY_DOWN, &errorCode) == 1); // Down Key
}

TEST_CASE("GInput Key/Button Up Tests")
{
	//Send the simulated input
#ifdef _WIN32
	SimulateInput(KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP);
#else
    SimulateInput(false);
#endif
	//Check the value of our stored keys
	GW::GReturn errorCode;
	//Check the number keys 1, 2, 3, 4
	CHECK(input->GetState(G_KEY_1, &errorCode) == 0);
	CHECK(input->GetState(G_KEY_2, &errorCode) == 0);
	CHECK(input->GetState(G_KEY_3, &errorCode) == 0);
	CHECK(input->GetState(G_KEY_4, &errorCode) == 0);

	//Check the letters A, S, D, W
	CHECK(input->GetState(G_KEY_A, &errorCode) == 0);
	CHECK(input->GetState(G_KEY_S, &errorCode) == 0);
	CHECK(input->GetState(G_KEY_D, &errorCode) == 0);
	CHECK(input->GetState(G_KEY_W, &errorCode) == 0);

	//Check the arrow keys Left, Right, Up, Down
	CHECK(input->GetState(G_KEY_LEFT, &errorCode) == 0); // Left Key
	CHECK(input->GetState(G_KEY_RIGHT, &errorCode) == 0); // Right Key
	CHECK(input->GetState(G_KEY_UP, &errorCode) == 0); // Up Key
	CHECK(input->GetState(G_KEY_DOWN, &errorCode) == 0); // Down Key

}
*/
