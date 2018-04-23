#include "../Common.h"
#ifdef __APPLE__

#elif __linux__
#include <unistd.h>
#endif



///=============================================================================
//==============================TEST CASES======================================
///=============================================================================

//THESE TEST CASES ARE SET UP IN A SPECIFIC ORDER. REORDERING TEST CASES COULD CAUSE
//CRASHES, FALSE FAILURES, or FALSE PASSES.
using namespace GW;
using namespace AUDIO;

// Global variables needed for all Test Cases.

GAudio * testAudio = nullptr;
GSound * testSound = nullptr;
GSound * testSound2 = nullptr;
GMusic * testMusic = nullptr;
GMusic * testMusic2 = nullptr;
GReturn checkReturned = FAILURE;
#ifdef _WIN32

const char * testpath =  u8"../../../../gateware.git.0/Unit Tests/Resources/TestBeep.wav";
const char * testpath2 = u8"../../../../gateware.git.0/Unit Tests/Resources/TestMusic.wav";
const char * testpath3 = u8"../../../../gateware.git.0/Unit Tests/Resources/TestMusic2.wav";
#elif __APPLE__
const char * testpath =  u8"../../../../../gateware.git.0/Unit Tests/Resources/TestBeep.wav";
const char * testpath2 = u8"../../../../../gateware.git.0/Unit Tests/Resources/TestMusic.wav";
const char * testpath3 = u8"../../../../../gateware.git.0/Unit Tests/Resources/TestMusic2.wav";
#elif __linux__
const char * testpath =  u8"../../../../../gateware.git.0/Unit Tests/Resources/TestBeep.wav";
const char * testpath2 = u8"../../../../../gateware.git.0/Unit Tests/Resources/TestMusic.wav";
const char * testpath3 = u8"../../../../../gateware.git.0/Unit Tests/Resources/TestMusic2.wav";
#endif


//const char * testpath4 = "TestSound2.wav";
int numOfOutputs;
float atestVolume[6] = { 1.0f, 0.0f, 0.0f ,0.0f, 0.0f, 0.0f};

// ALL DEVELOPERS!!! USE THIS AS AN EXAMPLE OF HOW TO DO CORE GINTERFACE TESTING!!!

//GAudio Test
GW::AUDIO::GAudio *GAudio_specific = nullptr;
GW::CORE::GInterface *GAudio_generic = nullptr;
// CORE GINTERFACE TEST BATTERY. ALL GATEWARE INTERFACES MUST BE ABLE TO PASS THESE TESTS.
TEST_CASE("GAudio core test battery", "[CreateGAudio], [RequestInterface], [IncrementCount], [DecrementCount], [GetCount]")
{
	// CATCH WARNING!!!
	// Any variables declared here will be REPLICATED to EACH SECTION.
	// If you need connectivity between sections your variables will need to be global or static.
	unsigned int countS = 0, countG = 0;
	const GW::GUUIID notAnValidInterface = { 0, };

	// THE CREATION FUNCTION IS UNIQUE MOST EVERYTHING BELOW THIS SHOULD BE THE SAME FOR ALL INTERFACES
	SECTION("Creation Tests", "[CreateGAudio]")
	{
		CHECK(GW::AUDIO::CreateGAudio(nullptr) == GW::INVALID_ARGUMENT);
		// TODO: Add additonal Creation parameter testing here as nessasary.
		REQUIRE(G_SUCCESS(GW::AUDIO::CreateGAudio(&GAudio_specific)));
		REQUIRE(G_SUCCESS(GAudio_specific->GetCount(countS)));
		REQUIRE(GAudio_specific != nullptr);
	}
	// The following tests can be copied verbatim as they are completly GAudio_generic for all interfaces
	SECTION("Interface Request Tests", "[RequestInterface]")
	{
		CHECK(GAudio_specific->RequestInterface(notAnValidInterface, nullptr) == GW::INVALID_ARGUMENT);
		CHECK(GAudio_specific->RequestInterface(notAnValidInterface, (void**)&GAudio_generic) == GW::INTERFACE_UNSUPPORTED);
		CHECK(GAudio_generic == nullptr); // should not have changed yet
		REQUIRE(G_SUCCESS(GAudio_specific->RequestInterface(GW::CORE::GInterfaceUUIID, (void**)&GAudio_generic)));
		REQUIRE(GAudio_generic != nullptr);
		// memory addresses should match
		REQUIRE(reinterpret_cast<std::uintptr_t>(GAudio_generic) == reinterpret_cast<std::uintptr_t>(GAudio_specific));
	}
	// Test reference counting behavior
	SECTION("Reference Counting Tests", "[GetCount], [IncrementCount], [DecrementCount]")
	{
		REQUIRE(G_SUCCESS(GAudio_specific->GetCount(countS)));
		REQUIRE(G_SUCCESS(GAudio_generic->GetCount(countG)));
		CHECK(countS == countG);
		CHECK(countS == 2); // should be exactly 2 references at this point
		REQUIRE(G_SUCCESS(GAudio_specific->IncrementCount())); // 3
		REQUIRE(G_SUCCESS(GAudio_generic->IncrementCount())); // 4
		GAudio_specific->GetCount(countS);
		GAudio_generic->GetCount(countG);
		CHECK(countS == countG);
		CHECK(countS == 4); // should be exactly 4 references at this point
		REQUIRE(G_SUCCESS(GAudio_specific->DecrementCount())); // 3
		REQUIRE(G_SUCCESS(GAudio_generic->DecrementCount())); // 2
		// Free GAudio_specific pointer (user simulation of interface deletion)
		CHECK(G_SUCCESS(GAudio_specific->DecrementCount())); // 1
		GAudio_specific = nullptr; // this pointer should not longer be valid from users standpoint (though it is)
		GAudio_generic->GetCount(countG);
		REQUIRE(countG == 1); // should be last remaining handle
	}
	// Finally test interface Forward Compatibilty
	SECTION("Forward Compatibility Tests", "[RequestInterface], [GetCount], [DecrementCount]")
	{
		CHECK(GAudio_generic->RequestInterface(notAnValidInterface, nullptr) == GW::INVALID_ARGUMENT);
		CHECK(GAudio_generic->RequestInterface(notAnValidInterface, (void**)&GAudio_specific) == GW::INTERFACE_UNSUPPORTED);
		CHECK(GAudio_specific == nullptr); // should not have changed yet
		// TODO: Check that GAudio_generic interface supports upgrading to ALL relevant interfaces in the class heirarchy chain
		REQUIRE(G_SUCCESS(GAudio_generic->RequestInterface(GW::AUDIO::GAudioUUIID, (void**)&GAudio_specific))); // 2
		CHECK(GAudio_specific != nullptr); // GAudio_specific pointer is valid again
		GW::CORE::GSingleThreaded *singleSupport = nullptr;
		GW::CORE::GMultiThreaded *multiSupport = nullptr;
		REQUIRE(G_FAIL(GAudio_generic->RequestInterface(GW::CORE::GSingleThreadedUUIID, (void**)&singleSupport)));
		CHECK(singleSupport == nullptr); // GAudio is NOT singlethreaded
		REQUIRE(G_SUCCESS(GAudio_generic->RequestInterface(GW::CORE::GMultiThreadedUUIID, (void**)&multiSupport))); // 3
		CHECK(multiSupport != nullptr); // GAudio IS multithreaded
		// Check final count VS expectations
		REQUIRE(G_SUCCESS(multiSupport->GetCount(countS)));
		CHECK(countS == 3); // three valid handles should exist now
		// Free all handles, all should succeed
		REQUIRE(G_SUCCESS(multiSupport->DecrementCount())); // 2
		REQUIRE(G_SUCCESS(GAudio_specific->DecrementCount())); // 1
		GAudio_generic->GetCount(countG);
		REQUIRE(countG == 1); // should be last remaining handle (again)
		REQUIRE(G_SUCCESS(GAudio_generic->DecrementCount())); // 0

		//delete GAudio_specific;
		GAudio_specific = nullptr;
	}
	// done with standard tests, the memory for the object should be released at this point and all pointers should be invalid
}


//GMusic Test
GW::AUDIO::GMusic *GMusic_specific = nullptr;
GW::CORE::GInterface *GMusic_generic = nullptr;
// CORE GINTERFACE TEST BATTERY. ALL GATEWARE INTERFACES MUST BE ABLE TO PASS THESE TESTS.
TEST_CASE("GMusic core test battery", "[CreateGAudio], [CreateMusicStream], [RequestInterface], [IncrementCount], [DecrementCount], [GetCount]")
{
	// CATCH WARNING!!!
	// Any variables declared here will be REPLICATED to EACH SECTION.
	// If you need connectivity between sections your variables will need to be global or static.
	unsigned int countS = 0, countG = 0;
	const GW::GUUIID notAnValidInterface = { 0, };

	// THE CREATION FUNCTION IS UNIQUE MOST EVERYTHING BELOW THIS SHOULD BE THE SAME FOR ALL INTERFACES
	SECTION("Creation Tests", "[CreateGAudio], [CreateMusicStream]")
	{
		CHECK(GW::AUDIO::CreateGAudio(nullptr) == GW::INVALID_ARGUMENT);
		// TODO: Add additonal Creation parameter testing here as nessasary.
		REQUIRE(G_SUCCESS(GW::AUDIO::CreateGAudio(&GAudio_specific)));
		REQUIRE(GAudio_specific != nullptr);
		CHECK(GAudio_specific->CreateMusicStream(testpath, nullptr) == GW::INVALID_ARGUMENT);
		REQUIRE(G_SUCCESS(GAudio_specific->CreateMusicStream(testpath,&GMusic_specific)));
		REQUIRE(GMusic_specific != nullptr);
	}
	// The following tests can be copied verbatim as they are completly GMusic_generic for all interfaces
	SECTION("Interface Request Tests", "[RequestInterface]")
	{
		CHECK(GMusic_specific->RequestInterface(notAnValidInterface, nullptr) == GW::INVALID_ARGUMENT);
		CHECK(GMusic_specific->RequestInterface(notAnValidInterface, (void**)&GMusic_generic) == GW::INTERFACE_UNSUPPORTED);
		CHECK(GMusic_generic == nullptr); // should not have changed yet
		REQUIRE(G_SUCCESS(GMusic_specific->RequestInterface(GW::CORE::GInterfaceUUIID, (void**)&GMusic_generic)));
		REQUIRE(GMusic_generic != nullptr);
		// memory addresses should match
		REQUIRE(reinterpret_cast<std::uintptr_t>(GMusic_generic) == reinterpret_cast<std::uintptr_t>(GMusic_specific));
	}
	// Test reference counting behavior
	SECTION("Reference Counting Tests", "[GetCount], [IncrementCount], [DecrementCount]")
	{
		REQUIRE(G_SUCCESS(GMusic_specific->GetCount(countS)));
		REQUIRE(G_SUCCESS(GMusic_generic->GetCount(countG)));
		CHECK(countS == countG);
		CHECK(countS == 2); // should be exactly 2 references at this point
		REQUIRE(G_SUCCESS(GMusic_specific->IncrementCount())); // 3
		REQUIRE(G_SUCCESS(GMusic_generic->IncrementCount())); // 4
		GMusic_specific->GetCount(countS);
		GMusic_generic->GetCount(countG);
		CHECK(countS == countG);
		CHECK(countS == 4); // should be exactly 4 references at this point
		REQUIRE(G_SUCCESS(GMusic_specific->DecrementCount())); // 3
		REQUIRE(G_SUCCESS(GMusic_generic->DecrementCount())); // 2
		// Free GMusic_specific pointer (user simulation of interface deletion)
		CHECK(G_SUCCESS(GMusic_specific->DecrementCount())); // 1
		GMusic_specific = nullptr; // this pointer should not longer be valid from users standpoint (though it is)
		GMusic_generic->GetCount(countG);
		REQUIRE(countG == 1); // should be last remaining handle
	}
	// Finally test interface Forward Compatibilty
	SECTION("Forward Compatibility Tests", "[RequestInterface], [GetCount], [DecrementCount]")
	{
		CHECK(GMusic_generic->RequestInterface(notAnValidInterface, nullptr) == GW::INVALID_ARGUMENT);
		CHECK(GMusic_generic->RequestInterface(notAnValidInterface, (void**)&GMusic_specific) == GW::INTERFACE_UNSUPPORTED);
		CHECK(GMusic_specific == nullptr); // should not have changed yet
		// TODO: Check that GMusic_generic interface supports upgrading to ALL relevant interfaces in the class heirarchy chain
		REQUIRE(G_SUCCESS(GMusic_generic->RequestInterface(GW::AUDIO::GMusicUUIID, (void**)&GMusic_specific))); // 2
		CHECK(GMusic_specific != nullptr); // GMusic_specific pointer is valid again
		GW::CORE::GSingleThreaded *singleSupport = nullptr;
		GW::CORE::GMultiThreaded *multiSupport = nullptr;
		REQUIRE(G_FAIL(GMusic_generic->RequestInterface(GW::CORE::GSingleThreadedUUIID, (void**)&singleSupport)));
		CHECK(singleSupport == nullptr); // GMusic is NOT singlethreaded
		REQUIRE(G_SUCCESS(GMusic_generic->RequestInterface(GW::CORE::GMultiThreadedUUIID, (void**)&multiSupport))); // 3
		CHECK(multiSupport != nullptr); // GMusic IS multithreaded
		// Check final count VS expectations
		REQUIRE(G_SUCCESS(multiSupport->GetCount(countS)));
		CHECK(countS == 3); // three valid handles should exist now
		// Free all handles except GAudio_specific, all should succeed
		REQUIRE(G_SUCCESS(multiSupport->DecrementCount())); // 2
		REQUIRE(G_SUCCESS(GMusic_specific->DecrementCount())); // 1
		GMusic_generic->GetCount(countG);
		REQUIRE(countG == 1); // should be last remaining handle (again)
		REQUIRE(G_SUCCESS(GMusic_generic->DecrementCount())); // 0

		//Free GAudio_specific
		REQUIRE(G_SUCCESS(GAudio_specific->DecrementCount())); // 0
		//delete GAudio_specific;
		GAudio_specific = nullptr;
	}
	// done with standard tests, the memory for the object should be released at this point and all pointers should be invalid
}

//GSound Test
GW::AUDIO::GSound *GSound_specific = nullptr;
GW::CORE::GInterface *GSound_generic = nullptr;
// CORE GINTERFACE TEST BATTERY. ALL GATEWARE INTERFACES MUST BE ABLE TO PASS THESE TESTS.
TEST_CASE("GSound core test battery", "[CreateGAudio], [CreateMusicStream], [RequestInterface], [IncrementCount], [DecrementCount], [GetCount]")
{
	// CATCH WARNING!!!
	// Any variables declared here will be REPLICATED to EACH SECTION.
	// If you need connectivity between sections your variables will need to be global or static.
	unsigned int countS = 0, countG = 0;
	const GW::GUUIID notAnValidInterface = { 0, };

	// THE CREATION FUNCTION IS UNIQUE MOST EVERYTHING BELOW THIS SHOULD BE THE SAME FOR ALL INTERFACES
	SECTION("Creation Tests", "[CreateGAudio], [CreateMusicStream]")
	{
		CHECK(GW::AUDIO::CreateGAudio(nullptr) == GW::INVALID_ARGUMENT);
		// TODO: Add additonal Creation parameter testing here as nessasary.
		REQUIRE(G_SUCCESS(GW::AUDIO::CreateGAudio(&GAudio_specific)));
		REQUIRE(GAudio_specific != nullptr);
		CHECK(GAudio_specific->CreateMusicStream(testpath2, nullptr) == GW::INVALID_ARGUMENT);
		REQUIRE(G_SUCCESS(GAudio_specific->CreateSound(testpath2, &GSound_specific)));
		REQUIRE(GSound_specific != nullptr);
	}
	// The following tests can be copied verbatim as they are completly GSound_generic for all interfaces
	SECTION("Interface Request Tests", "[RequestInterface]")
	{
		CHECK(GSound_specific->RequestInterface(notAnValidInterface, nullptr) == GW::INVALID_ARGUMENT);
		CHECK(GSound_specific->RequestInterface(notAnValidInterface, (void**)&GSound_generic) == GW::INTERFACE_UNSUPPORTED);
		CHECK(GSound_generic == nullptr); // should not have changed yet
		REQUIRE(G_SUCCESS(GSound_specific->RequestInterface(GW::CORE::GInterfaceUUIID, (void**)&GSound_generic)));
		REQUIRE(GSound_generic != nullptr);
		// memory addresses should match
		REQUIRE(reinterpret_cast<std::uintptr_t>(GSound_generic) == reinterpret_cast<std::uintptr_t>(GSound_specific));
	}
	// Test reference counting behavior
	SECTION("Reference Counting Tests", "[GetCount], [IncrementCount], [DecrementCount]")
	{
		REQUIRE(G_SUCCESS(GSound_specific->GetCount(countS)));
		REQUIRE(G_SUCCESS(GSound_generic->GetCount(countG)));
		CHECK(countS == countG);
		CHECK(countS == 2); // should be exactly 2 references at this point
		REQUIRE(G_SUCCESS(GSound_specific->IncrementCount())); // 3
		REQUIRE(G_SUCCESS(GSound_generic->IncrementCount())); // 4
		GSound_specific->GetCount(countS);
		GSound_generic->GetCount(countG);
		CHECK(countS == countG);
		CHECK(countS == 4); // should be exactly 4 references at this point
		REQUIRE(G_SUCCESS(GSound_specific->DecrementCount())); // 3
		REQUIRE(G_SUCCESS(GSound_generic->DecrementCount())); // 2
		// Free GSound_specific pointer (user simulation of interface deletion)
		CHECK(G_SUCCESS(GSound_specific->DecrementCount())); // 1
		GSound_specific = nullptr; // this pointer should not longer be valid from users standpoint (though it is)
		GSound_generic->GetCount(countG);
		REQUIRE(countG == 1); // should be last remaining handle
	}
	// Finally test interface Forward Compatibilty
	SECTION("Forward Compatibility Tests", "[RequestInterface], [GetCount], [DecrementCount]")
	{
		CHECK(GSound_generic->RequestInterface(notAnValidInterface, nullptr) == GW::INVALID_ARGUMENT);
		CHECK(GSound_generic->RequestInterface(notAnValidInterface, (void**)&GSound_specific) == GW::INTERFACE_UNSUPPORTED);
		CHECK(GSound_specific == nullptr); // should not have changed yet
		// TODO: Check that GSound_generic interface supports upgrading to ALL relevant interfaces in the class heirarchy chain
		REQUIRE(G_SUCCESS(GSound_generic->RequestInterface(GW::AUDIO::GSoundUUIID, (void**)&GSound_specific))); // 2
		CHECK(GSound_specific != nullptr); // GSound_specific pointer is valid again
		GW::CORE::GSingleThreaded *singleSupport = nullptr;
		GW::CORE::GMultiThreaded *multiSupport = nullptr;
		REQUIRE(G_FAIL(GSound_generic->RequestInterface(GW::CORE::GSingleThreadedUUIID, (void**)&singleSupport)));
		CHECK(singleSupport == nullptr); // GSound is NOT singlethreaded
		REQUIRE(G_SUCCESS(GSound_generic->RequestInterface(GW::CORE::GMultiThreadedUUIID, (void**)&multiSupport))); // 3
		CHECK(multiSupport != nullptr); // GSound IS multithreaded
		// Check final count VS expectations
		REQUIRE(G_SUCCESS(multiSupport->GetCount(countS)));
		CHECK(countS == 3); // three valid handles should exist now
		// Free all handles except GAudio_specific, all should succeed
		REQUIRE(G_SUCCESS(multiSupport->DecrementCount())); // 2
		REQUIRE(G_SUCCESS(GSound_specific->DecrementCount())); // 1
		GSound_generic->GetCount(countG);
		REQUIRE(countG == 1); // should be last remaining handle (again)
		REQUIRE(G_SUCCESS(GSound_generic->DecrementCount())); // 0

		//Free GAudio_specific
		REQUIRE(G_SUCCESS(GAudio_specific->DecrementCount())); // 0
		//delete GAudio_specific;
		GAudio_specific = nullptr;
	}
	// done with standard tests, the memory for the object should be released at this point and all pointers should be invalid
}


// Custom Unit Tests specific to this interface follow..


//Starting Audio Tests, some can't be tested until sound/music starts playing
TEST_CASE("Create GAudio.", "[CreateGAudio]")
{

	// Fail cases
	CHECK(GW::AUDIO::CreateGAudio(nullptr));

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = CreateGAudio(&testAudio)));
	checkReturned = FAILURE;
}
TEST_CASE("Initialize Audio", "[Init]")
{

#ifdef WIN32
 numOfOutputs = 6;
#else
 numOfOutputs = 2;
#endif
	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testAudio->Init(numOfOutputs)));
	checkReturned = FAILURE;
}

TEST_CASE("Creating Sound.", "[CreateSound]")
{
	// Fail cases
	CHECK(testAudio->CreateSound(testpath, nullptr) == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testAudio->CreateSound(testpath, &testSound)));

    REQUIRE(G_SUCCESS(checkReturned = testAudio->CreateSound(testpath3, &testSound2)));

	checkReturned = FAILURE;
}

TEST_CASE("Creating music.", "[CreateMusic]")
{

	// Fail cases
	CHECK(testAudio->CreateMusicStream(testpath, nullptr) == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testAudio->CreateMusicStream(testpath2, &testMusic)));
	REQUIRE(G_SUCCESS(checkReturned = testAudio->CreateMusicStream(testpath3, &testMusic2)));
	checkReturned = FAILURE;
}

TEST_CASE("Setting master volume", "[SetMasterVolume]")
{

	// Fail cases
	CHECK(testAudio->SetMasterVolume(-1) == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testAudio->SetMasterVolume(1)));
	checkReturned = FAILURE;
}

//Starting Sound Tests
TEST_CASE("Playing test sound", "[PlaySound]")
{
	// Fail cases
	// CHECK(testSound->PlaySound() == INVALID_ARGUMENT);
	// Pass cases

	REQUIRE(G_SUCCESS(checkReturned = testSound->Play()));
#ifdef WIN32
  	Sleep(1);
#else
 sleep(1);
#endif

    REQUIRE(G_SUCCESS(checkReturned = testSound2->Play()));


    checkReturned = FAILURE;
}

TEST_CASE("Pausing test sound", "[Pause]")
{

	// Fail cases
	//CHECK(testSound->Pause() == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testSound->Pause()));
	checkReturned = FAILURE;
	#ifdef WIN32
  	Sleep(1);
#else
 sleep(1);
#endif
}

TEST_CASE("Resuming test sound", "[Resume]")
{
	// Fail cases
	//CHECK(testSound->Resume() == INVALID_ARGUMENT);
	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testSound->Resume()));
	checkReturned = FAILURE;
#ifdef WIN32
Sleep(1);
#else
 sleep(1);
#endif
}

TEST_CASE("Setting sound channel volumes", "[SetChannelVolumes]")
{
	atestVolume[0] = 1.0f;
	atestVolume[3] = 1.0f;
	atestVolume[5] = 1.0f;


	float * testvolumes = atestVolume;

	REQUIRE(G_SUCCESS(checkReturned = testSound2->SetChannelVolumes(testvolumes, 6)));

	atestVolume[0] = 0.5f;
	// Fail cases
	CHECK(testSound->SetChannelVolumes(nullptr, 0) == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testSound->SetChannelVolumes(testvolumes, 6)));
	REQUIRE(G_SUCCESS(checkReturned = testSound->Play()));
#ifdef WIN32

	for (int k = 1; k < numOfOutputs; k++)
	{
		Sleep(1);
		for (int i = 0; i < 6; i++)
		{
			atestVolume[i] = 0.0f;
		}
		atestVolume[k] = 1.0f;
		REQUIRE(G_SUCCESS(checkReturned = testSound->SetChannelVolumes(testvolumes, 6)));
		REQUIRE(G_SUCCESS(checkReturned = testSound->Play()));
	}
	Sleep(1);
#endif
	checkReturned = FAILURE;
}

TEST_CASE("Setting test sound volume", "[SetVolume]")
{
	// Fail cases
	CHECK(testSound->SetVolume(-1) == INVALID_ARGUMENT);
	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testSound->SetVolume(0.5)));
	checkReturned = FAILURE;
}

TEST_CASE("Stop test sound", "[StopSound]")
{
	// Fail cases

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testSound->StopSound()));
    REQUIRE(G_SUCCESS(checkReturned = testSound2->StopSound()));
	checkReturned = FAILURE;
}
/*
//////////////////////////
//Following test case is if future developer gets PCM shader working
/////////////////////////

//TEST_CASE("Editing test sound PCM", "[EditPCM]")
//{
//	const char* testdata = nullptr;
//	// Fail cases
//	//CHECK(testSound->Resume() == INVALID_ARGUMENT);
//	// Pass cases
//	REQUIRE(G_SUCCESS(testSound->SetPCMShader(testdata)));
//}
//Starting Music Tests

TEST_CASE("Setting music channel volumes", "[SetChannelVolumes]")
{

    REQUIRE(testMusic != nullptr);
     REQUIRE(testMusic2 != nullptr);
	 for (int i = 0; i < 6; i++)
	 {
		 atestVolume[i] = 0.0f;
	 }
	 atestVolume[0] = { 1.0f };
	float * testvolumes = atestVolume;
	// Fail cases
	CHECK(testMusic->SetChannelVolumes(nullptr, 1) == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testMusic->SetChannelVolumes(testvolumes, 6)));
	for (int i = 0; i < 6; i++)
	{
		atestVolume[i] = 0.0f;
	}
	atestVolume[5] = { 1.0f };

	REQUIRE(G_SUCCESS(checkReturned = testMusic2->SetChannelVolumes(testvolumes, 6)));
	checkReturned = FAILURE;
}

TEST_CASE("Playing test music", "[Playmusic]")
{
    REQUIRE(testMusic != nullptr);
    REQUIRE(testMusic2 != nullptr);
	// Fail cases
	// CHECK(testmusic->Playmusic() == INVALID_ARGUMENT);
	// Pass cases


  	REQUIRE(G_SUCCESS(checkReturned = testMusic->StreamStart()));
	REQUIRE(G_SUCCESS(checkReturned = testMusic2->StreamStart()));
#ifdef WIN32
	float * testvolumes = atestVolume;

		Sleep(1);
		REQUIRE(G_SUCCESS(checkReturned = testMusic->PauseStream()));
		REQUIRE(G_SUCCESS(checkReturned = testMusic2->PauseStream()));
		for (int i = 0; i < 6; i++)
		{
			atestVolume[i] = 0.0f;
		}
		atestVolume[3] = 1.0f;
		REQUIRE(G_SUCCESS(checkReturned = testMusic->SetChannelVolumes(testvolumes, 6)));
		atestVolume[3] = 0.0f;
		atestVolume[2] = 1.0f;
		REQUIRE(G_SUCCESS(checkReturned = testMusic2->SetChannelVolumes(testvolumes, 6)));

		REQUIRE(G_SUCCESS(checkReturned = testMusic->ResumeStream()));
		REQUIRE(G_SUCCESS(checkReturned = testMusic2->ResumeStream()));

		Sleep(1);
		REQUIRE(G_SUCCESS(checkReturned = testMusic->PauseStream()));
		REQUIRE(G_SUCCESS(checkReturned = testMusic2->PauseStream()));
		for (int i = 0; i < 6; i++)
		{
			atestVolume[i] = 0.0f;
		}
		atestVolume[4] = 1.0f;
		REQUIRE(G_SUCCESS(checkReturned = testMusic->SetChannelVolumes(testvolumes, 6)));
		atestVolume[4] = 0.0f;
		atestVolume[1] = 1.0f;

		REQUIRE(G_SUCCESS(checkReturned = testMusic2->SetChannelVolumes(testvolumes, 6)));
		REQUIRE(G_SUCCESS(checkReturned = testMusic->ResumeStream()));
		REQUIRE(G_SUCCESS(checkReturned = testMusic2->ResumeStream()));
		Sleep(1);

#else
 sleep(1);
#endif

	checkReturned = FAILURE;

}
TEST_CASE("Setting test music volume", "[SetVolume]")
{   REQUIRE(testMusic != nullptr);
  // REQUIRE(testMusic2 != nullptr);
    // Fail cases
    CHECK(testMusic->SetVolume(-1) == INVALID_ARGUMENT);
    // Pass cases
    REQUIRE(G_SUCCESS(checkReturned = testMusic->SetVolume(1)));
    checkReturned = FAILURE;
}

TEST_CASE("Pausing test music", "[Pause]")
{
    REQUIRE(testMusic != nullptr);
    REQUIRE(testMusic2 != nullptr);
	// Fail cases
	//CHECK(testmusic->Pause() == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testMusic->PauseStream()));
    REQUIRE(G_SUCCESS(checkReturned = testMusic2->PauseStream()));
	for (int i = 0; i < 6; i++)
	{
		atestVolume[i] = 0.0f;
	}
     atestVolume[3] = atestVolume[4] = atestVolume[5] = {0.3f};
	float * testvolumes = atestVolume;
	// Fail cases
	CHECK(testMusic->SetChannelVolumes(nullptr, 1) == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testMusic->SetChannelVolumes(testvolumes, 6)));
	for (int i = 0; i < 6; i++)
	{
		atestVolume[i] = 0.0f;
	}
	atestVolume[0] = atestVolume[1] = atestVolume[2] = { 0.5f };
	REQUIRE(G_SUCCESS(checkReturned = testMusic2->SetChannelVolumes(testvolumes, 6)));
	checkReturned = FAILURE;
#ifdef WIN32
  	Sleep(1);
#else
 sleep(1);
#endif

}
TEST_CASE("Resuming test music", "[Resume]")
{
    REQUIRE(testMusic != nullptr);
    REQUIRE(testMusic2 != nullptr);
	REQUIRE(G_SUCCESS(checkReturned = testMusic2->SetVolume(0.2)));
	REQUIRE(G_SUCCESS(checkReturned = testMusic2->SetVolume(1)));
	// Fail cases
	//CHECK(testmusic->Resume() == INVALID_ARGUMENT);
	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testMusic->ResumeStream()));
    REQUIRE(G_SUCCESS(checkReturned = testMusic2->ResumeStream()));
	checkReturned = FAILURE;
#ifdef WIN32
  	Sleep(1);
#else
 sleep(1);
#endif

}

TEST_CASE("Stop test music", "[Stopmusic]")
{
    REQUIRE(testMusic != nullptr);
    REQUIRE(testMusic2 != nullptr);
	// Fail cases
	//CHECK(testmusic->Resume() == INVALID_ARGUMENT);
	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testMusic->StopStream()));
    REQUIRE(G_SUCCESS(checkReturned = testMusic2->StopStream()));
	checkReturned = FAILURE;
#ifdef WIN32
  	Sleep(1);
#else
 sleep(1);
#endif

}
//TEST_CASE("Editing test music PCM", "[EditPCM]")
//{
//	const char* testdata = nullptr;
//	// Pass cases
//	REQUIRE(G_SUCCESS(testMusic->SetPCMShader(testdata)));
//}

//Last of Audio Tests
TEST_CASE("Pausing all sounds and music.", "[PauseAll]")
{
    REQUIRE(testSound != nullptr);
    REQUIRE(testMusic != nullptr);
    REQUIRE(testMusic2 != nullptr);
    REQUIRE(G_SUCCESS(checkReturned = testMusic->SetVolume(1)));
    REQUIRE(G_SUCCESS(checkReturned = testMusic2->SetVolume(1)));
	for (int i = 0; i < 6; i++)
	{
		atestVolume[i] = 0.0f;
	}
	atestVolume[0] = atestVolume[2] = atestVolume[4] = { 0.5f };
	float * testvolumes = atestVolume;
	// Fail cases
	CHECK(testMusic->SetChannelVolumes(nullptr, 1) == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testMusic->SetChannelVolumes(testvolumes, 6)));

	for (int i = 0; i < 6; i++)
	{
		atestVolume[i] = 0.0f;
	}
	atestVolume[1] = atestVolume[3] = atestVolume[5] = { 0.8f };
	REQUIRE(G_SUCCESS(checkReturned = testMusic2->SetChannelVolumes(testvolumes, 6)));
	testMusic->StreamStart(true);
    testMusic2->StreamStart();
	testSound->Play();
#ifdef WIN32
  	Sleep(1);
#else
 sleep(1);
#endif

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testAudio->PauseAll()));
	checkReturned = FAILURE;

}

TEST_CASE("Setting master channel volumes", "[SetMasterChannelVolumes]")
{
	for (int i = 0; i < 6; i++)
	{
		atestVolume[i] = 1.0f;
	}
	float * testvolumes = atestVolume;
	// Fail cases
	CHECK(testAudio->SetMasterChannelVolumes(nullptr, 0) == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testAudio->SetMasterChannelVolumes(testvolumes, 6)));
	checkReturned = FAILURE;
}
TEST_CASE("Resuming all sounds and music.", "[ResumeAll]")
{

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testAudio->ResumeAll()));
	checkReturned = FAILURE;
#ifdef WIN32
  	Sleep(1);
#else
 sleep(1);
#endif

}
TEST_CASE("Stopping all sounds and music.", "[Stopll]")
{

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testAudio->StopAll()));
	checkReturned = FAILURE;
	testMusic->DecrementCount();
	testMusic2->DecrementCount();
	testSound->DecrementCount();
	testSound2->DecrementCount();
	testAudio->DecrementCount();

	testAudio = nullptr;
	testMusic = nullptr;
	testMusic2 = nullptr;
	testSound = nullptr;
	testSound2 = nullptr;

}
*/
