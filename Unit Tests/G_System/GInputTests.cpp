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
