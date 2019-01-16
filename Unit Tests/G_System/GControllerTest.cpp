#include "../Unit Tests/Common.h"
#include "GControllerTestListener.h"

#include <thread>

#define MANUAl_INPUT
//#define MANUAL_CONNECTION_EVENTS
//#define MANUAL_VIBRATION_TEST
//#define SIMULATED_INPUT

///=============================================================================
//==============================TEST CASES======================================
///=============================================================================

//THESE TEST CASES ARE SET UP IN A SPECIFIC ORDER. REORDERING TEST CASES COULD CAUSE
//CRASHES, FALSE FAILURES, or FALSE PASSES

//Global variables needed for all GController Test Cases
GW::SYSTEM::GController* controller = nullptr; //Our buffered input object
GW::CORE::GListener* controllerListener = nullptr; //Our listener object

// ALL DEVELOPERS!!! USE THIS AS AN EXAMPLE OF HOW TO DO CORE GINTERFACE TESTING!!!
GW::SYSTEM::GController *GController_specific = nullptr;
GW::CORE::GInterface *GController_generic = nullptr;
// CORE GINTERFACE TEST BATTERY. ALL GATEWARE INTERFACES MUST BE ABLE TO PASS THESE TESTS.

TEST_CASE("GController core test battery", "[CreateGController], [RequestInterface], [IncrementCount], [DecrementCount], [GetCount]")
{
	// CATCH WARNING!!!
	// Any variables declared here will be REPLICATED to EACH SECTION.
	// If you need connectivity between sections your variables will need to be global or static.
	unsigned int countS = 0, countG = 0;
	const GW::GUUIID notAnValidInterface = { 0, };

	// THE CREATION FUNCTION IS UNIQUE MOST EVERYTHING BELOW THIS SHOULD BE THE SAME FOR ALL INTERFACES
	SECTION("Creation Tests", "[CreateGController]")
	{
		CHECK(GW::SYSTEM::CreateGController(G_GENERAL_CONTROLLER, nullptr) == GW::INVALID_ARGUMENT);
		CHECK(GW::SYSTEM::CreateGController(-1, &GController_specific) == GW::INVALID_ARGUMENT);
		// TODO: Add additonal Creation parameter testing here as nessasary.

#ifdef _WIN32 // Temp until General controller support is added to Windows
		REQUIRE(G_SUCCESS(GW::SYSTEM::CreateGController(G_XBOX_CONTROLLER, &GController_specific)));
#endif // _WIN32
#ifndef _WIN32
		REQUIRE(G_SUCCESS(GW::SYSTEM::CreateGController(G_GENERAL_CONTROLLER, &GController_specific)));
#endif // _WIN32

		REQUIRE(GController_specific != nullptr);
	}
	// The following tests can be copied verbatim as they are completly GController_generic for all interfaces
	SECTION("Interface Request Tests", "[RequestInterface]")
	{
		CHECK(GController_specific->RequestInterface(notAnValidInterface, nullptr) == GW::INVALID_ARGUMENT);
		CHECK(GController_specific->RequestInterface(notAnValidInterface, (void**)&GController_generic) == GW::INTERFACE_UNSUPPORTED);
		CHECK(GController_generic == nullptr); // should not have changed yet
		REQUIRE(G_SUCCESS(GController_specific->RequestInterface(GW::CORE::GInterfaceUUIID, (void**)&GController_generic)));
		REQUIRE(GController_generic != nullptr);
		// memory addresses should match
		REQUIRE(reinterpret_cast<std::uintptr_t>(GController_generic) == reinterpret_cast<std::uintptr_t>(GController_specific));
	}
	// Test reference counting behavior
	SECTION("Reference Counting Tests", "[GetCount], [IncrementCount], [DecrementCount]")
	{
		REQUIRE(G_SUCCESS(GController_specific->GetCount(countS)));
		REQUIRE(G_SUCCESS(GController_generic->GetCount(countG)));
		CHECK(countS == countG);
		CHECK(countS == 2); // should be exactly 2 references at this point
		REQUIRE(G_SUCCESS(GController_specific->IncrementCount())); // 3
		REQUIRE(G_SUCCESS(GController_generic->IncrementCount())); // 4
		GController_specific->GetCount(countS);
		GController_generic->GetCount(countG);
		CHECK(countS == countG);
		CHECK(countS == 4); // should be exactly 4 references at this point
		REQUIRE(G_SUCCESS(GController_specific->DecrementCount())); // 3
		REQUIRE(G_SUCCESS(GController_generic->DecrementCount())); // 2
																	  // Free GController_specific pointer (user simulation of interface deletion)
		CHECK(G_SUCCESS(GController_specific->DecrementCount())); // 1
		GController_specific = nullptr; // this pointer should not longer be valid from users standpoint (though it is)
		GController_generic->GetCount(countG);
		REQUIRE(countG == 1); // should be last remaining handle
	}
	// Finally test interface Forward Compatibilty
	SECTION("Forward Compatibility Tests", "[RequestInterface], [GetCount], [DecrementCount]")
	{
		CHECK(GController_generic->RequestInterface(notAnValidInterface, nullptr) == GW::INVALID_ARGUMENT);
		CHECK(GController_generic->RequestInterface(notAnValidInterface, (void**)&GController_specific) == GW::INTERFACE_UNSUPPORTED);
		CHECK(GController_specific == nullptr); // should not have changed yet
												   // TODO: Check that GController_generic interface supports upgrading to ALL relevant interfaces in the class heirarchy chain
		REQUIRE(G_SUCCESS(GController_generic->RequestInterface(GW::SYSTEM::GControllerUUIID, (void**)&GController_specific))); // 2
		CHECK(GController_specific != nullptr); // GController_specific pointer is valid again
		GW::CORE::GSingleThreaded *singleSupport = nullptr;
		GW::CORE::GMultiThreaded *multiSupport = nullptr;
		REQUIRE(G_FAIL(GController_generic->RequestInterface(GW::CORE::GSingleThreadedUUIID, (void**)&singleSupport)));
		CHECK(singleSupport == nullptr); // GController is NOT singlethreaded
		REQUIRE(G_SUCCESS(GController_generic->RequestInterface(GW::CORE::GMultiThreadedUUIID, (void**)&multiSupport))); // 3
		CHECK(multiSupport != nullptr); // GController IS multithreaded
										// Check final count VS expectations
		REQUIRE(G_SUCCESS(multiSupport->GetCount(countS)));
		CHECK(countS == 3); // three valid handles should exist now
							// Free all handles, all should succeed
		REQUIRE(G_SUCCESS(multiSupport->DecrementCount())); // 2
		REQUIRE(G_SUCCESS(GController_specific->DecrementCount())); // 1
		GController_generic->GetCount(countG);
		REQUIRE(countG == 1); // should be last remaining handle (again)
		REQUIRE(G_SUCCESS(GController_generic->DecrementCount())); // 0
	}
	// done with standard tests, the memory for the object should be released at this point and all pointers should be invalid
}

// Custom Unit Tests specific to this interface follow..

TEST_CASE("CreateGController Tests", "[CreateGController]")
{

	//Check that these cases fail appropriately
	CHECK(GW::SYSTEM::CreateGController(G_GENERAL_CONTROLLER, nullptr) == GW::INVALID_ARGUMENT);
	CHECK(GW::SYSTEM::CreateGController(-1, &controller) == GW::INVALID_ARGUMENT);

#ifdef _WIN32 // Temp until General controller support is added to Windows
	REQUIRE(G_SUCCESS(GW::SYSTEM::CreateGController(G_XBOX_CONTROLLER, &controller)));
#else
	REQUIRE(G_SUCCESS(GW::SYSTEM::CreateGController(G_GENERAL_CONTROLLER, &controller)));
#endif // _WIN32



	REQUIRE(controller != nullptr);


}

TEST_CASE("GController Register Listeners.", "[RegisterListener]")
{

	//Create our new test listener
	controllerListener = new GControllerTestListener();

	//Check that this case fails appropriately
	CHECK(controller->RegisterListener(nullptr, 0) == GW::INVALID_ARGUMENT);

	//The following case should pass
	REQUIRE(G_SUCCESS(controller->RegisterListener(controllerListener, 0)));

}

#ifdef MANUAl_INPUT

TEST_CASE("GController Manual controller connection test")
{
	int maxIndex = -1;
	bool isConnected = false;
	int numReportedConnected = -1;
	int numConfirmedConnected = 0;
	// Test invaild arguments
	CHECK(controller->IsConnected(-1, isConnected) == GW::INVALID_ARGUMENT);
	// end test
	REQUIRE(G_SUCCESS(controller->GetMaxIndex(maxIndex)));
	REQUIRE(G_SUCCESS(controller->GetNumConnected(numReportedConnected)));

	for (unsigned int i = 0; i < maxIndex; ++i)
	{
		REQUIRE(G_SUCCESS(controller->IsConnected(i, isConnected)));
		if (isConnected)
			++numConfirmedConnected;
	}

	CHECK(numConfirmedConnected == numReportedConnected);
}

#ifdef MANUAL_CONNECTION_EVENTS

TEST_CASE("GController Manual controller connection event test")
{
	int maxIndex = -1;
	bool isConnected = false;
	int numReportedConnected = -1;
	int numConfirmedConnected = 0;
	printf("Unplug the controller\n");
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	CHECK(event_controllers[0].isConnected == 0);
	printf("Plug the controller back in\n");
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	CHECK(event_controllers[0].isConnected == 1);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

}
#endif // MANUAL_CONNECTION_EVENTS

#ifdef MANUAL_VIBRATION_TEST
TEST_CASE("GController Manual controller vibration test")
{
	bool isConnected = false;
	bool isVibrating = false;
	controller->IsConnected(0, isConnected);
	REQUIRE(isConnected);

	// Checking invailds
	CHECK(controller->IsVibrating(-1, isVibrating) == GW::INVALID_ARGUMENT);
	CHECK(controller->StopVirbration(-1) == GW::INVALID_ARGUMENT);
	CHECK(controller->StartVibration(-1.0f, -1.0f, -2.0f, -1) == GW::INVALID_ARGUMENT);

	printf("Vibration both sides duration .5 seconds\n");
	CHECK(G_SUCCESS(controller->StartVibration(0, 1, .5f, 0)));
	std::this_thread::sleep_for(std::chrono::seconds(2));
	controller->IsVibrating(0, isVibrating);
	CHECK(isVibrating == false);
	std::this_thread::sleep_for(std::chrono::seconds(1));


	printf("Vibration Left side duration .5 seconds\n");
	CHECK(G_SUCCESS(controller->StartVibration(-1, 1, .5f, 0)));
	std::this_thread::sleep_for(std::chrono::seconds(2));
	controller->IsVibrating(0, isVibrating);
	CHECK(isVibrating == false);
	std::this_thread::sleep_for(std::chrono::seconds(1));


	printf("Vibration Right side duration .5 seconds\n");
	CHECK(G_SUCCESS(controller->StartVibration(1, 1, .5f, 0)));
	std::this_thread::sleep_for(std::chrono::seconds(2));
	controller->IsVibrating(0, isVibrating);
	CHECK(isVibrating == false);
	std::this_thread::sleep_for(std::chrono::seconds(1));

	CHECK(G_SUCCESS(controller->StartVibration(0, 1, .5f, 0)));
	CHECK(G_SUCCESS(controller->StopVirbration(0)));
	controller->IsVibrating(0, isVibrating);
	CHECK(isVibrating == false);
	std::this_thread::sleep_for(std::chrono::seconds(1));

	CHECK(G_SUCCESS(controller->StartVibration(0, 1, .5f, 0)));
	CHECK(G_SUCCESS(controller->StopAllVirbrations()));
	controller->IsVibrating(0, isVibrating);
	CHECK(isVibrating == false);
	std::this_thread::sleep_for(std::chrono::seconds(1));

	CHECK(G_SUCCESS(controller->StartVibration(0, 1, .5f, 0)));
	CHECK(controller->StartVibration(0, 1, .5f, 0) == GW::FAILURE);
	CHECK(G_SUCCESS(controller->StopVirbration(0)));


}
#endif// MANUAL_VIBRATION_TEST

#ifdef _WIN32 // Temp until General controller support is added to Windows
TEST_CASE("GController Manual Xbox input test")
{
	float outState = 0.0f;
	int numConnected = 0;
	bool isConnected = false;
	// test invaild arguments
	CHECK(controller->GetState(-1, G_XBOX_A_BTN, outState) == GW::INVALID_ARGUMENT);
	CHECK(controller->GetState(0, -1, outState) == GW::INVALID_ARGUMENT);
	//end test

	controller->IsConnected(0, isConnected);
	REQUIRE(isConnected);

	// test polling
	while (true)
	{
		// Buttons: SOUTH, DPAD_DOWN, LEFT_SHOULDER, RIGHT_THUMB
		printf("Press the South Button\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		REQUIRE(G_SUCCESS(controller->GetState(0, G_XBOX_A_BTN, outState)));
		CHECK(outState == 1.0f);
		CHECK(outState == event_controllers[0].southBTN);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		printf("Press the Down on the DPAD\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		REQUIRE(G_SUCCESS(controller->GetState(0, G_XBOX_DPAD_DOWN_BTN, outState)));
		CHECK(outState == 1.0f);
		CHECK(outState == event_controllers[0].dpadDown);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		printf("Press the Left Shoulder\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		REQUIRE(G_SUCCESS(controller->GetState(0, G_XBOX_LEFT_SHOULDER_BTN, outState)));
		CHECK(outState == 1.0f);
		CHECK(outState == event_controllers[0].leftShoulder);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		printf("Press Down on the Right Thumb stick\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		REQUIRE(G_SUCCESS(controller->GetState(0, G_XBOX_RIGHT_THUMB_BTN, outState)));
		CHECK(outState == 1.0f);
		CHECK(outState == event_controllers[0].rightThumb);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		// AXES: LX, LY, LEFT_TRIGGER, RIGHT_TRIGGER
		printf("Move the left stick left\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		REQUIRE(G_SUCCESS(controller->GetState(0, G_XBOX_LX_AXIS, outState)));
		CHECK(outState < 0.0f);
		CHECK(outState == event_controllers[0].LX);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		printf("Move the left stick right\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		REQUIRE(G_SUCCESS(controller->GetState(0, G_XBOX_LX_AXIS, outState)));
		CHECK(outState > 0.0f);
		CHECK(outState == event_controllers[0].LX);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		printf("Move the left stick up\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		REQUIRE(G_SUCCESS(controller->GetState(0, G_XBOX_LY_AXIS, outState)));
		CHECK(outState > 0.0f);
		CHECK(outState == event_controllers[0].LY);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		printf("Move the left stick down\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		REQUIRE(G_SUCCESS(controller->GetState(0, G_XBOX_LY_AXIS, outState)));
		CHECK(outState < 0.0f);
		CHECK(outState == event_controllers[0].LY);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		printf("Press down the left trigger\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		REQUIRE(G_SUCCESS(controller->GetState(0, G_XBOX_LEFT_TRIGGER_AXIS, outState)));
		CHECK(outState > 0.0f);
		CHECK(outState == event_controllers[0].leftTrigger);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		printf("Press down the right trigger\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		REQUIRE(G_SUCCESS(controller->GetState(0, G_XBOX_RIGHT_TRIGGER_AXIS, outState)));
		CHECK(outState > 0.0f);
		CHECK(outState == event_controllers[0].rightTrigger);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		// EXIT CODE: START
		printf("Press start to end\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		REQUIRE(G_SUCCESS(controller->GetState(0, G_XBOX_START_BTN, outState)));
		CHECK(outState == 1.0f);
		CHECK(outState == event_controllers[0].start);
		if (outState == 1.0f)
			break;
	}

}
#else
TEST_CASE("GController Manual input test")
{
	float outState = 0.0f;
	int numConnected = 0;
	bool isConnected = false;
	// test invaild arguments
	CHECK(controller->GetState(-1, G_GENERAL_SOUTH_BTN, outState) == GW::INVALID_ARGUMENT);
	CHECK(controller->GetState(0, -1, outState) == GW::INVALID_ARGUMENT);
	//end test
        printf("Connect Controller now\n") ;
	//while(!isConnected)
	//{
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        //controller->IsConnected(0, isConnected);
      //  CHECK(isConnected);
    //}

	REQUIRE(isConnected);

	// test polling
	while (true)
	{
		// Buttons: SOUTH, DPAD_DOWN, LEFT_SHOULDER, RIGHT_THUMB
		printf("Press the South Button\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		REQUIRE(G_SUCCESS(controller->GetState(0, G_GENERAL_SOUTH_BTN, outState)));
		CHECK(outState == 1.0f);
		CHECK(outState == event_controllers[0].southBTN);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		printf("Press the Down on the DPAD\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		REQUIRE(G_SUCCESS(controller->GetState(0, G_GENERAL_DPAD_DOWN_BTN, outState)));
		CHECK(outState == 1.0f);
		CHECK(outState == event_controllers[0].dpadDown);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		printf("Press the Left Shoulder\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		REQUIRE(G_SUCCESS(controller->GetState(0, G_GENERAL_LEFT_SHOULDER_BTN, outState)));
		CHECK(outState == 1.0f);
		CHECK(outState == event_controllers[0].leftShoulder);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		printf("Press Down on the Right Thumb stick\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		REQUIRE(G_SUCCESS(controller->GetState(0, G_GENERAL_RIGHT_THUMB_BTN, outState)));
		CHECK(outState == 1.0f);
		CHECK(outState == event_controllers[0].rightThumb);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		// AXES: LX, LY, LEFT_TRIGGER, RIGHT_TRIGGER
		printf("Move the left stick left\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		REQUIRE(G_SUCCESS(controller->GetState(0, G_GENERAL_LX_AXIS, outState)));
		CHECK(outState < 0.0f);
		CHECK(outState == event_controllers[0].LX);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		printf("Move the left stick right\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		REQUIRE(G_SUCCESS(controller->GetState(0, G_GENERAL_LX_AXIS, outState)));
		CHECK(outState > 0.0f);
		CHECK(outState == event_controllers[0].LX);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		printf("Move the left stick up\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		REQUIRE(G_SUCCESS(controller->GetState(0, G_GENERAL_LY_AXIS, outState)));
		CHECK(outState > 0.0f);
		CHECK(outState == event_controllers[0].LY);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		printf("Move the left stick down\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		REQUIRE(G_SUCCESS(controller->GetState(0, G_GENERAL_LY_AXIS, outState)));
		CHECK(outState < 0.0f);
		CHECK(outState == event_controllers[0].LY);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		printf("Press down the left trigger\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		REQUIRE(G_SUCCESS(controller->GetState(0, G_GENERAL_LEFT_TRIGGER_AXIS, outState)));
		CHECK(outState > 0.0f);
		CHECK(outState == event_controllers[0].leftTrigger);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		printf("Press down the right trigger\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		REQUIRE(G_SUCCESS(controller->GetState(0, G_GENERAL_RIGHT_TRIGGER_AXIS, outState)));
		CHECK(outState > 0.0f);
		CHECK(outState == event_controllers[0].rightTrigger);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		// EXIT CODE: START
		printf("Press start to end\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		REQUIRE(G_SUCCESS(controller->GetState(0, G_GENERAL_START_BTN, outState)));
		CHECK(outState == 1.0f);
		CHECK(outState == event_controllers[0].start);
		if (outState == 1.0f)
			break;
	}

}
#endif // _WIN32

TEST_CASE("GController Setting Deadzone")
{
	CHECK(controller->SetDeadZone(GW::SYSTEM::DEADZONESQUARE, -1.0f) == GW::INVALID_ARGUMENT);
	CHECK(controller->SetDeadZone(GW::SYSTEM::DEADZONESQUARE, 2.0f) == GW::INVALID_ARGUMENT);


	REQUIRE(G_SUCCESS(controller->SetDeadZone(GW::SYSTEM::DEADZONESQUARE, .5f)));
	REQUIRE(G_SUCCESS(controller->SetDeadZone(GW::SYSTEM::DEADZONECIRCLE, .35f)));

}




#elif SIMULATED_INPUT
// test polling

// test events

#endif

TEST_CASE("GController Unregistering listener", "[DeregisterListener]")
{

	unsigned int refCount = 0;

	//Check that this case fails appropriately
	CHECK(controller->DeregisterListener(nullptr) == GW::INVALID_ARGUMENT);

	//The following case should pass
	REQUIRE(G_SUCCESS(controller->DeregisterListener(controllerListener)));
	controllerListener->GetCount(refCount);

	CHECK(refCount == 1);

	controllerListener->DecrementCount();
	controller->DecrementCount();

}


