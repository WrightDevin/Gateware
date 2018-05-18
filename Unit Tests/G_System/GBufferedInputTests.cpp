
#include "../Unit Tests/Common.h"
#include "GBufferedInputTestListener.h"

#include <thread>
/*
///=============================================================================
//==============================TEST CASES======================================
///=============================================================================

//THESE TEST CASES ARE SET UP IN A SPECIFIC ORDER. REORDERING TEST CASES COULD CAUSE
//CRASHES, FALSE FAILURES, or FALSE PASSES

//Global variables needed for all GBufferedInput Test Cases
GW::SYSTEM::GBufferedInput* bufferedInput = nullptr; //Our buffered input object
GW::CORE::GListener* listener = nullptr; //Our listener object

// ALL DEVELOPERS!!! USE THIS AS AN EXAMPLE OF HOW TO DO CORE GINTERFACE TESTING!!!
GW::SYSTEM::GBufferedInput *GBufferedInput_specific = nullptr;
GW::CORE::GInterface *GBufferedInput_generic = nullptr;
// CORE GINTERFACE TEST BATTERY. ALL GATEWARE INTERFACES MUST BE ABLE TO PASS THESE TESTS.

TEST_CASE("GBufferedInput core test battery", "[CreateGBufferedInput], [RequestInterface], [IncrementCount], [DecrementCount], [GetCount]")
{
	// CATCH WARNING!!!
	// Any variables declared here will be REPLICATED to EACH SECTION.
	// If you need connectivity between sections your variables will need to be global or static.
	unsigned int countS = 0, countG = 0;
	const GW::GUUIID notAnValidInterface = { 0, };

	// THE CREATION FUNCTION IS UNIQUE MOST EVERYTHING BELOW THIS SHOULD BE THE SAME FOR ALL INTERFACES
	SECTION("Creation Tests", "[CreateGBufferedInput]")
	{
		CHECK(GW::SYSTEM::CreateGBufferedInput(nullptr, 0, nullptr) == GW::INVALID_ARGUMENT);
		// TODO: Add additonal Creation parameter testing here as nessasary.
#ifdef __linux__
      //  window.window = (void*)&mainWindow;
      //  window.display = (void*)display;
        REQUIRE(G_SUCCESS(GW::SYSTEM::CreateGBufferedInput((void*)&window, sizeof(window), &GBufferedInput_specific)));
#endif

#if defined(_WIN32) || defined(__APPLE__)
        REQUIRE(G_SUCCESS(GW::SYSTEM::CreateGBufferedInput((void*)window, sizeof(window), &GBufferedInput_specific)));
#endif
		REQUIRE(GBufferedInput_specific != nullptr);
	}
	// The following tests can be copied verbatim as they are completly GBufferedInput_generic for all interfaces
	SECTION("Interface Request Tests", "[RequestInterface]")
	{
		CHECK(GBufferedInput_specific->RequestInterface(notAnValidInterface, nullptr) == GW::INVALID_ARGUMENT);
		CHECK(GBufferedInput_specific->RequestInterface(notAnValidInterface, (void**)&GBufferedInput_generic) == GW::INTERFACE_UNSUPPORTED);
		CHECK(GBufferedInput_generic == nullptr); // should not have changed yet
		REQUIRE(G_SUCCESS(GBufferedInput_specific->RequestInterface(GW::CORE::GInterfaceUUIID, (void**)&GBufferedInput_generic)));
		REQUIRE(GBufferedInput_generic != nullptr);
		// memory addresses should match
		REQUIRE(reinterpret_cast<std::uintptr_t>(GBufferedInput_generic) == reinterpret_cast<std::uintptr_t>(GBufferedInput_specific));
	}
	// Test reference counting behavior
	SECTION("Reference Counting Tests", "[GetCount], [IncrementCount], [DecrementCount]")
	{
		REQUIRE(G_SUCCESS(GBufferedInput_specific->GetCount(countS)));
		REQUIRE(G_SUCCESS(GBufferedInput_generic->GetCount(countG)));
		CHECK(countS == countG);
		CHECK(countS == 2); // should be exactly 2 references at this point
		REQUIRE(G_SUCCESS(GBufferedInput_specific->IncrementCount())); // 3
		REQUIRE(G_SUCCESS(GBufferedInput_generic->IncrementCount())); // 4
		GBufferedInput_specific->GetCount(countS);
		GBufferedInput_generic->GetCount(countG);
		CHECK(countS == countG);
		CHECK(countS == 4); // should be exactly 4 references at this point
		REQUIRE(G_SUCCESS(GBufferedInput_specific->DecrementCount())); // 3
		REQUIRE(G_SUCCESS(GBufferedInput_generic->DecrementCount())); // 2
		// Free GBufferedInput_specific pointer (user simulation of interface deletion)
		CHECK(G_SUCCESS(GBufferedInput_specific->DecrementCount())); // 1
		GBufferedInput_specific = nullptr; // this pointer should not longer be valid from users standpoint (though it is)
		GBufferedInput_generic->GetCount(countG);
		REQUIRE(countG == 1); // should be last remaining handle
	}
	// Finally test interface Forward Compatibilty
	SECTION("Forward Compatibility Tests", "[RequestInterface], [GetCount], [DecrementCount]")
	{
		CHECK(GBufferedInput_generic->RequestInterface(notAnValidInterface, nullptr) == GW::INVALID_ARGUMENT);
		CHECK(GBufferedInput_generic->RequestInterface(notAnValidInterface, (void**)&GBufferedInput_specific) == GW::INTERFACE_UNSUPPORTED);
		CHECK(GBufferedInput_specific == nullptr); // should not have changed yet
		// TODO: Check that GBufferedInput_generic interface supports upgrading to ALL relevant interfaces in the class heirarchy chain
		REQUIRE(G_SUCCESS(GBufferedInput_generic->RequestInterface(GW::SYSTEM::GBufferedInputUUIID, (void**)&GBufferedInput_specific))); // 2
		CHECK(GBufferedInput_specific != nullptr); // GBufferedInput_specific pointer is valid again
		GW::CORE::GSingleThreaded *singleSupport = nullptr;
		GW::CORE::GMultiThreaded *multiSupport = nullptr;
		REQUIRE(G_FAIL(GBufferedInput_generic->RequestInterface(GW::CORE::GSingleThreadedUUIID, (void**)&singleSupport)));
		CHECK(singleSupport == nullptr); // GBufferedInput is NOT singlethreaded
		REQUIRE(G_SUCCESS(GBufferedInput_generic->RequestInterface(GW::CORE::GMultiThreadedUUIID, (void**)&multiSupport))); // 3
		CHECK(multiSupport != nullptr); // GBufferedInput IS multithreaded
		// Check final count VS expectations
		REQUIRE(G_SUCCESS(multiSupport->GetCount(countS)));
		CHECK(countS == 3); // three valid handles should exist now
		// Free all handles, all should succeed
		REQUIRE(G_SUCCESS(multiSupport->DecrementCount())); // 2
		REQUIRE(G_SUCCESS(GBufferedInput_specific->DecrementCount())); // 1
		GBufferedInput_generic->GetCount(countG);
		REQUIRE(countG == 1); // should be last remaining handle (again)
		REQUIRE(G_SUCCESS(GBufferedInput_generic->DecrementCount())); // 0
	}
	// done with standard tests, the memory for the object should be released at this point and all pointers should be invalid
}

// Custom Unit Tests specific to this interface follow..



TEST_CASE("CreateGBufferedInput Tests", "[CreateGBufferedInput]")
{

	//Check that these cases fail appropriately
	CHECK(GW::SYSTEM::CreateGBufferedInput(nullptr, 0, nullptr) == GW::INVALID_ARGUMENT);
	CHECK(GW::SYSTEM::CreateGBufferedInput(nullptr, 0, &bufferedInput) == GW::INVALID_ARGUMENT);

	//If linux then we need to fill out a structure
	//I named the structure window for less branching
#ifdef __linux__
	//window.window = (void*)&mainWindow;
	//window.display = (void*)display;
    REQUIRE(G_SUCCESS(GW::SYSTEM::CreateGBufferedInput((void*)&window, sizeof(window), &bufferedInput)));
#endif
#if defined(_WIN32) || defined(__APPLE__)
	//The following cases should pass
	REQUIRE(G_SUCCESS(GW::SYSTEM::CreateGBufferedInput((void*)window, sizeof(window), &bufferedInput)));
#endif

	REQUIRE(bufferedInput != nullptr);


}

TEST_CASE("GBufferedInput Register Listeners.", "[RegisterListener]")
{

	//Create our new test listener
	listener = new GBufferedInputTestListener();

	//Check that this case fails appropriately
	CHECK(bufferedInput->RegisterListener(nullptr, 0) == GW::INVALID_ARGUMENT);

	//The following case should pass
	REQUIRE(G_SUCCESS(bufferedInput->RegisterListener(listener, 0)));

}

//Input cases are commented out becasue of known linux bug

#if defined(_WIN32) || defined(__APPLE__)

TEST_CASE("GBufferedInput Testing Key/Button Down Events")
{

	//Send the simulated input
#ifdef _WIN32
	SimulateInput(KEYEVENTF_SCANCODE);

#else
    SimulateInput(true);

#endif

	//Sleep this thread for 5 milliseconds to give the library
	//time to process the input.
	std::this_thread::sleep_for(std::chrono::milliseconds(15));

	//Check the value of our stored keys

	//Check the number keys 1, 2, 3, 4
	CHECK(keys['1'] == true);
	CHECK(keys['2'] == true);
	CHECK(keys['3'] == true);
	CHECK(keys['4'] == true);

	//Check the letters A, S, D, W
	CHECK(keys['A'] == true);
	CHECK(keys['S'] == true);
	CHECK(keys['D'] == true);
	CHECK(keys['W'] == true);

	//Check the arrow keys Left, Right, Up, Down
	CHECK(keys[0] == true); // Left Key
	CHECK(keys[1] == true); // Right Key
	CHECK(keys[2] == true); // Up Key
	CHECK(keys[3] == true); // Down Key

}

TEST_CASE("GBufferedInput Testing Key/Button Up Events")
{

	//Send the simulated input
#ifdef _WIN32
	SimulateInput(KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP);
#else
    SimulateInput(false);
#endif

	//Sleep this thread for 5 milliseconds to give the library
	//time to process the input.
	std::this_thread::sleep_for(std::chrono::milliseconds(15));

	//Check the number keys 1, 2, 3, 4
	CHECK(keys['1'] == false);
	CHECK(keys['2'] == false);
	CHECK(keys['3'] == false);
	CHECK(keys['4'] == false);

	//Check the letters A, S, D, W
	CHECK(keys['A'] == false);
	CHECK(keys['S'] == false);
	CHECK(keys['D'] == false);
	CHECK(keys['W'] == false);

	//Check the arrow keys Left, Right, Up, Down
	CHECK(keys[0] == false); // Left Key
	CHECK(keys[1] == false); // Right Key
	CHECK(keys[2] == false); // Up Key
	CHECK(keys[3] == false); // Down Key

}
#endif //_WIN32 || __APPLE__


TEST_CASE("GBufferedInput Unregistering listener", "[DeregisterListener]")
{

	unsigned int refCount = 0;

	//Check that this case fails appropriately
	CHECK(bufferedInput->DeregisterListener(nullptr) == GW::INVALID_ARGUMENT);

	//The following case should pass
	REQUIRE(G_SUCCESS(bufferedInput->DeregisterListener(listener)));
	listener->GetCount(refCount);

	CHECK(refCount == 1);

	listener->DecrementCount();
	bufferedInput->DecrementCount();

}

*/
