/*
#include "../Unit Tests/Common.h"
#include "GBufferedInputTestListener.h"

#include <thread>

///=============================================================================
//==============================TEST CASES======================================
///=============================================================================

//THESE TEST CASES ARE SET UP IN A SPECIFIC ORDER. REORDERING TEST CASES COULD CAUSE
//CRASHES, FALSE FAILURES, or FALSE PASSES

//Global variables needed for all GBufferedInput Test Cases
GW::SYSTEM::GBufferedInput* bufferedInput = nullptr; //Our buffered input object
GW::CORE::GListener* listener = nullptr; //Our listener object

#ifndef __linux__ 
TEST_CASE("CreateGBufferedInput Tests", "[CreateGBufferedInput]")
{
	//Check that these cases fail appropriately
	CHECK(GW::SYSTEM::CreateGBufferedInput(nullptr, 0, nullptr) == GW::INVALID_ARGUMENT);
	CHECK(GW::SYSTEM::CreateGBufferedInput(nullptr, 0, &bufferedInput) == GW::INVALID_ARGUMENT);

	//If linux then we need to fill out a structure
	//I named the structure window for less branching
#ifdef __linux__
	window->window = (void*)&mainWindow;
	window->display = (void*)display;
#endif

	//The following cases should pass
	REQUIRE(G_SUCCESS(GW::SYSTEM::CreateGBufferedInput((void*)window, sizeof(window), &bufferedInput)));
    //usleep(10000000); // Why was this here?
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
#endif
*/
