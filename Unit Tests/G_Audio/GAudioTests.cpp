#include "../Common.h"
#ifdef __APPLE__

#elif __linux__
#include <unistd.h>
#endif


///=============================================================================
//==============================TEST CASES======================================
///=============================================================================

using namespace GW;
using namespace AUDIO;

#define FRONT_LEFT 0
#define FRONT_RIGHT 1
#define FRONT_CENTER 2
#define SURROUND_CENTER 3
#define SURROUND_LEFT 4
#define SURROUND_RIGHT 5

// Global variables needed for all Test Cases.

#ifdef _WIN32 // pathing needs one less indirection on windows

const char * testSong = u8"../../../../gateware.git.0/Unit Tests/Resources/testSong.wav"; //1m 11s
const char * testBeep = u8"../../../../gateware.git.0/Unit Tests/Resources/testBeep.wav"; //0.5s

const char * beep = u8"../../../../gateware.git.0/Unit Tests/Resources/beep.wav"; //1s
const char * stereo5_1Test = u8"../../../../gateware.git.0/Unit Tests/Resources/stereo5.1Test.wav"; // 35s

const char * frontLeft = u8"../../../../gateware.git.0/Unit Tests/Resources/frontLeft.wav"; //1s
const char * frontCenter = u8"../../../../gateware.git.0/Unit Tests/Resources/frontCenter.wav"; //1s
const char * frontRight = u8"../../../../gateware.git.0/Unit Tests/Resources/frontRight.wav"; //1s

const char * surroundLeft = u8"../../../../gateware.git.0/Unit Tests/Resources/surroundLeft.wav"; //2s
const char * bass = u8"../../../../gateware.git.0/Unit Tests/Resources/bass.wav"; //2s
const char * surroundRight = u8"../../../../gateware.git.0/Unit Tests/Resources/surroundRight.wav"; //2s

const char * masterVolume1 = u8"../../../../gateware.git.0/Unit Tests/Resources/masterVolumeAtOne.wav"; //2s
const char * masterVolume_5 = u8"../../../../gateware.git.0/Unit Tests/Resources/masterVolumeAtPointFive.wav"; //2s

const char * musicPause = u8"../../../../gateware.git.0/Unit Tests/Resources/musicPause.wav"; //1.8s -> 1.2s
const char * musicResume = u8"../../../../gateware.git.0/Unit Tests/Resources/musicResume.wav"; //1s
const char * musicStreamStart = u8"../../../../gateware.git.0/Unit Tests/Resources/musicStreamStart.wav"; //2s

const char * soundPause = u8"../../../../gateware.git.0/Unit Tests/Resources/soundPause.wav"; //1.8s -> 1.2s
const char * soundStop = u8"../../../../gateware.git.0/Unit Tests/Resources/soundStop.wav"; //1.8s -> 1.2s
const char * soundResume = u8"../../../../gateware.git.0/Unit Tests/Resources/soundResume.wav"; //1s
const char * soundPlay = u8"../../../../gateware.git.0/Unit Tests/Resources/soundPlay.wav"; //1s

const char * volume1 = u8"../../../../gateware.git.0/Unit Tests/Resources/volumeAtOne.wav"; //1s
const char * volume_5 = u8"../../../../gateware.git.0/Unit Tests/Resources/volumeAtPointFive.wav"; //2s

#else

const char * testSong = u8"../../../../../gateware.git.0/Unit Tests/Resources/testSong.wav"; //1m 11s
const char * testBeep = u8"../../../../../gateware.git.0/Unit Tests/Resources/testBeep.wav"; //0.5s

const char * beep = u8"../../../../../gateware.git.0/Unit Tests/Resources/beep.wav"; //1s
const char * stereo5_1Test = u8"../../../../../gateware.git.0/Unit Tests/Resources/stereo5.1Test.wav"; // 35s

const char * frontLeft = u8"../../../../../gateware.git.0/Unit Tests/Resources/frontLeft.wav"; //1s
const char * frontCenter = u8"../../../../../gateware.git.0/Unit Tests/Resources/frontCenter.wav"; //1s
const char * frontRight = u8"../../../../../gateware.git.0/Unit Tests/Resources/frontRight.wav"; //1s

const char * surroundLeft = u8"../../../../../gateware.git.0/Unit Tests/Resources/surroundLeft.wav"; //2s
const char * bass = u8"../../../../../gateware.git.0/Unit Tests/Resources/bass.wav"; //2s
const char * surroundRight = u8"../../../../../gateware.git.0/Unit Tests/Resources/surroundRight.wav"; //2s

const char * masterVolume1 = u8"../../../../../gateware.git.0/Unit Tests/Resources/masterVolumeAtOne.wav"; //2s
const char * masterVolume_5 = u8"../../../../../gateware.git.0/Unit Tests/Resources/masterVolumeAtPointFive.wav"; //2s

const char * musicPause = u8"../../../../../gateware.git.0/Unit Tests/Resources/musicPause.wav"; //1.8s -> 1.2s
const char * musicResume = u8"../../../../../gateware.git.0/Unit Tests/Resources/musicResume.wav"; //1.1s
const char * musicStreamStart = u8"../../../../../gateware.git.0/Unit Tests/Resources/musicStreamStart.wav"; //2s

const char * soundPause = u8"../../../../../gateware.git.0/Unit Tests/Resources/soundPause.wav"; //1.8s -> 1.2s
const char * soundStop = u8"../../../../../gateware.git.0/Unit Tests/Resources/soundStop.wav"; //1.8s -> 1.2s
const char * soundResume = u8"../../../../../gateware.git.0/Unit Tests/Resources/soundResume.wav"; //1.1s
const char * soundPlay = u8"../../../../../gateware.git.0/Unit Tests/Resources/soundPlay.wav"; //1s

const char * volume1 = u8"../../../../../gateware.git.0/Unit Tests/Resources/volumeAtOne.wav"; //1s
const char * volume_5 = u8"../../../../../gateware.git.0/Unit Tests/Resources/volumeAtPointFive.wav"; //2s

#endif

void sleep_ms(int d)
{
#ifdef WIN32
    Sleep(d);
#else
    usleep(d*1000);
#endif
}

int numOfOutputs;
float ZEROS[6] = { 0.0f, 0.0f, 0.0f ,0.0f, 0.0f, 0.0f };
float HALVES[6] = { 0.5f, 0.5f, 0.5f ,0.5f, 0.5f, 0.5f };
float ONES[6] = { 1.0f, 1.0f, 1.0f ,1.0f, 1.0f, 1.0f };
float FRONT[6] = { 1.0f, 1.0f, 1.0f ,0.0f, 0.0f, 0.0f };
float SURROUND[6] = { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };
float LEFT_EAR[6] = { 1.0f, 0.0f, 0.0f ,0.0f, 1.0f, 0.0f };
float RIGHT_EAR[6] = { 0.0f, 1.0f, 0.0f ,0.0f, 0.0f, 1.0f };

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
    const GW::GUUIID notAnValidInterface = { {{0}}, };

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
    const GW::GUUIID notAnValidInterface = { {{0}}, };

	// THE CREATION FUNCTION IS UNIQUE MOST EVERYTHING BELOW THIS SHOULD BE THE SAME FOR ALL INTERFACES
	SECTION("Creation Tests", "[CreateGAudio], [CreateMusicStream]")
	{
		CHECK(GW::AUDIO::CreateGAudio(nullptr) == GW::INVALID_ARGUMENT);
		// TODO: Add additonal Creation parameter testing here as nessasary.
		REQUIRE(G_SUCCESS(GW::AUDIO::CreateGAudio(&GAudio_specific)));
		REQUIRE(GAudio_specific != nullptr);
		CHECK(GAudio_specific->CreateMusicStream(testSong, nullptr) == GW::INVALID_ARGUMENT);
		REQUIRE(G_SUCCESS(GAudio_specific->CreateMusicStream(testSong,&GMusic_specific)));
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
		CHECK(countS == 3); // should be exactly 3 references at this point, as GAudio also has a handle to this object
		REQUIRE(G_SUCCESS(GMusic_specific->IncrementCount())); // 4
		REQUIRE(G_SUCCESS(GMusic_generic->IncrementCount())); // 5
		GMusic_specific->GetCount(countS);
		GMusic_generic->GetCount(countG);
		CHECK(countS == countG);
		CHECK(countS == 5); // should be exactly 4 references at this point
		REQUIRE(G_SUCCESS(GMusic_specific->DecrementCount())); // 4
		REQUIRE(G_SUCCESS(GMusic_generic->DecrementCount())); // 3
		// Free GMusic_specific pointer (user simulation of interface deletion)
		CHECK(G_SUCCESS(GMusic_specific->DecrementCount())); // 2
		GMusic_specific = nullptr; // this pointer should not longer be valid from users standpoint (though it is)
		GMusic_generic->GetCount(countG);
		REQUIRE(countG == 2); // should be last remaining user handle
	}
	// Finally test interface Forward Compatibilty
	SECTION("Forward Compatibility Tests", "[RequestInterface], [GetCount], [DecrementCount]")
	{
		CHECK(GMusic_generic->RequestInterface(notAnValidInterface, nullptr) == GW::INVALID_ARGUMENT);
		CHECK(GMusic_generic->RequestInterface(notAnValidInterface, (void**)&GMusic_specific) == GW::INTERFACE_UNSUPPORTED);
		CHECK(GMusic_specific == nullptr); // should not have changed yet
		// TODO: Check that GMusic_generic interface supports upgrading to ALL relevant interfaces in the class heirarchy chain
		REQUIRE(G_SUCCESS(GMusic_generic->RequestInterface(GW::AUDIO::GMusicUUIID, (void**)&GMusic_specific))); // 3
		CHECK(GMusic_specific != nullptr); // GMusic_specific pointer is valid again
		GW::CORE::GSingleThreaded *singleSupport = nullptr;
		GW::CORE::GMultiThreaded *multiSupport = nullptr;
		REQUIRE(G_FAIL(GMusic_generic->RequestInterface(GW::CORE::GSingleThreadedUUIID, (void**)&singleSupport)));
		CHECK(singleSupport == nullptr); // GMusic is NOT singlethreaded
		REQUIRE(G_SUCCESS(GMusic_generic->RequestInterface(GW::CORE::GMultiThreadedUUIID, (void**)&multiSupport))); // 4
		CHECK(multiSupport != nullptr); // GMusic IS multithreaded
		// Check final count VS expectations
		REQUIRE(G_SUCCESS(multiSupport->GetCount(countS)));
		CHECK(countS == 4); // four valid handles should exist now
		// Free all handles except GAudio_specific, all should succeed
		REQUIRE(G_SUCCESS(multiSupport->DecrementCount())); // 3
		REQUIRE(G_SUCCESS(GMusic_specific->DecrementCount())); // 2
		GMusic_generic->GetCount(countG);
		REQUIRE(countG == 2); // should be last remaining user handle (again)
		REQUIRE(G_SUCCESS(GMusic_generic->DecrementCount())); // 1

		//Free GAudio_specific
		REQUIRE(G_SUCCESS(GAudio_specific->DecrementCount())); // 1
		//delete GAudio_specific;
		GAudio_specific = nullptr;
	}
	// done with standard tests, the memory for the object should be released at a safe point by GAudio and all pointers should be invalid
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
    const GW::GUUIID notAnValidInterface = { {{0}}, };

	// THE CREATION FUNCTION IS UNIQUE MOST EVERYTHING BELOW THIS SHOULD BE THE SAME FOR ALL INTERFACES
	SECTION("Creation Tests", "[CreateGAudio], [CreateMusicStream]")
	{
		CHECK(GW::AUDIO::CreateGAudio(nullptr) == GW::INVALID_ARGUMENT);
		// TODO: Add additonal Creation parameter testing here as nessasary.
		REQUIRE(G_SUCCESS(GW::AUDIO::CreateGAudio(&GAudio_specific)));
		REQUIRE(GAudio_specific != nullptr);
		CHECK(GAudio_specific->CreateSound(testBeep, nullptr) == GW::INVALID_ARGUMENT);
		REQUIRE(G_SUCCESS(GAudio_specific->CreateSound(testBeep, &GSound_specific)));
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
		CHECK(countS == 3); // should be exactly 3 references at this point, as GAudio also has a handle to this object
		REQUIRE(G_SUCCESS(GSound_specific->IncrementCount())); // 4
		REQUIRE(G_SUCCESS(GSound_generic->IncrementCount())); // 5
		GSound_specific->GetCount(countS);
		GSound_generic->GetCount(countG);
		CHECK(countS == countG);
		CHECK(countS == 5); // should be exactly 4 references at this point
		REQUIRE(G_SUCCESS(GSound_specific->DecrementCount())); // 4
		REQUIRE(G_SUCCESS(GSound_generic->DecrementCount())); // 3
		// Free GSound_specific pointer (user simulation of interface deletion)
		CHECK(G_SUCCESS(GSound_specific->DecrementCount())); // 2
		GSound_specific = nullptr; // this pointer should not longer be valid from users standpoint (though it is)
		GSound_generic->GetCount(countG);
		REQUIRE(countG == 2); // should be last remaining user handle
	}
	// Finally test interface Forward Compatibilty
	SECTION("Forward Compatibility Tests", "[RequestInterface], [GetCount], [DecrementCount]")
	{
		CHECK(GSound_generic->RequestInterface(notAnValidInterface, nullptr) == GW::INVALID_ARGUMENT);
		CHECK(GSound_generic->RequestInterface(notAnValidInterface, (void**)&GSound_specific) == GW::INTERFACE_UNSUPPORTED);
		CHECK(GSound_specific == nullptr); // should not have changed yet
		// TODO: Check that GSound_generic interface supports upgrading to ALL relevant interfaces in the class heirarchy chain
		REQUIRE(G_SUCCESS(GSound_generic->RequestInterface(GW::AUDIO::GSoundUUIID, (void**)&GSound_specific))); // 3
		CHECK(GSound_specific != nullptr); // GSound_specific pointer is valid again
		GW::CORE::GSingleThreaded *singleSupport = nullptr;
		GW::CORE::GMultiThreaded *multiSupport = nullptr;
		REQUIRE(G_FAIL(GSound_generic->RequestInterface(GW::CORE::GSingleThreadedUUIID, (void**)&singleSupport)));
		CHECK(singleSupport == nullptr); // GSound is NOT singlethreaded
		REQUIRE(G_SUCCESS(GSound_generic->RequestInterface(GW::CORE::GMultiThreadedUUIID, (void**)&multiSupport))); // 4
		CHECK(multiSupport != nullptr); // GSound IS multithreaded
		// Check final count VS expectations
		REQUIRE(G_SUCCESS(multiSupport->GetCount(countS)));
		CHECK(countS == 4); // four valid handles should exist now
		// Free all handles except GAudio_specific, all should succeed
		REQUIRE(G_SUCCESS(multiSupport->DecrementCount())); // 3
		REQUIRE(G_SUCCESS(GSound_specific->DecrementCount())); // 2
		GSound_generic->GetCount(countG);
		REQUIRE(countG == 2); // should be last remaining user handle (again)
		REQUIRE(G_SUCCESS(GSound_generic->DecrementCount())); // 1

		//Free GAudio_specific
		REQUIRE(G_SUCCESS(GAudio_specific->DecrementCount())); // 1
		//delete GAudio_specific;
		GAudio_specific = nullptr;
	}
	// done with standard tests, the memory for the object should be released at a safe point by GAudio and all pointers should be invalid
}


// Custom Unit Tests specific to this interface follow..

// Starting Audio Tests
TEST_CASE("Creating audio", "[CreateGAudio]")
{
    GAudio * testAudio = nullptr;
    
	// Fail cases
	CHECK(GW::AUDIO::CreateGAudio(nullptr));

	// Pass cases
	REQUIRE(G_SUCCESS(CreateGAudio(&testAudio)));
    
    testAudio->DecrementCount();
}

TEST_CASE("Deleting audio", "[DecrementCount]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    testAudio->DecrementCount();
    sleep_ms(2000);
    
    // [Pass case] Should throw an access violation when uncommented
    // There is no good way in c++ to check if something has been deleted.
    // testAudio->DecrementCount();
}

TEST_CASE("Initializing audio", "[Init]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);

    #ifdef WIN32
    numOfOutputs = 6;
    #else
    numOfOutputs = 6;
    #endif
    
	// Pass cases
	REQUIRE(G_SUCCESS(testAudio->Init(numOfOutputs)));
    
    testAudio->DecrementCount();
}

TEST_CASE("Creating sound.", "[CreateSound]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    GSound * testSound = nullptr;
    
	CHECK(testAudio->CreateSound(testBeep, nullptr) == INVALID_ARGUMENT);

	REQUIRE(G_SUCCESS(testAudio->CreateSound(testBeep, &testSound)));

    testAudio->DecrementCount();
}

TEST_CASE("Creating music.", "[CreateMusicStream]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    GMusic * testMusic = nullptr;

	CHECK(testAudio->CreateMusicStream(testSong, nullptr) == INVALID_ARGUMENT);

	REQUIRE(G_SUCCESS(testAudio->CreateMusicStream(testSong, &testMusic)));
    
    testAudio->DecrementCount();
}


//Starting Sound Tests
TEST_CASE("Playing sound", "[Play]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    GSound * testSound = nullptr;
    testAudio->CreateSound(soundPlay, &testSound);
    
	REQUIRE(G_SUCCESS(testSound->Play()));
    sleep_ms(1000);
    
    testAudio->DecrementCount();
}

// Starting Sound Tests
TEST_CASE("Deleting sound", "[DecrementCount]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    GSound * testSound = nullptr;
    testAudio->CreateSound(testBeep, &testSound); // testSound soundCount = 2 (this handle, and audio has a handle)
    testSound->Play(); // plays for 0.5s then should trigger the audio callback CleanUpSound() in GAudio.mm. soundCount = 1
    testSound->DecrementCount(); // soundCount = 0
    sleep_ms(2000); // testSound deletes at a safe time
    
    // [Pass case] Should throw an access violation when uncommented
    // There is no good way in c++ to check if something has been deleted.
    // testSound->DecrementCount();
}

TEST_CASE("Pausing sound", "[Pause]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    GSound * testSound = nullptr;
    testAudio->CreateSound(soundPause, &testSound);
    testSound->Play();
    sleep_ms(1800);
    
	REQUIRE(G_SUCCESS(testSound->Pause()));
    
    testAudio->DecrementCount();
}

TEST_CASE("Resuming sound", "[Resume]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    GSound * testSound = nullptr;
    testAudio->CreateSound(soundResume, &testSound);
    testSound->Play();
    testSound->Pause();
    
	REQUIRE(G_SUCCESS(testSound->Resume()));
    sleep_ms(1100);
    
    testAudio->DecrementCount();
}

TEST_CASE("Setting sound channel volumes", "[SetChannelVolumes]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    float testvolumes[6] = { 0.0f, 0.0f, 0.0f ,0.0f, 0.0f, 0.0f };
    
    GSound * soundFrontRight = nullptr;
    GSound * soundFrontCenter = nullptr;
    GSound * soundFrontLeft = nullptr;
    {
        testAudio->CreateSound(frontLeft, &soundFrontLeft);
        testvolumes[FRONT_LEFT] = 1.0f;
        
        REQUIRE(G_SUCCESS(soundFrontLeft->SetChannelVolumes(testvolumes, 6)));
        
        soundFrontLeft->Play();
        sleep_ms(1000);
        testvolumes[FRONT_LEFT] = 0.0f;
        soundFrontLeft->DecrementCount();
        
        testAudio->CreateSound(frontCenter, &soundFrontCenter);
        testvolumes[FRONT_CENTER] = 1.0f;
        
        REQUIRE(G_SUCCESS(soundFrontCenter->SetChannelVolumes(testvolumes, 6)));
        
        soundFrontCenter->Play();
        sleep_ms(1000);
        testvolumes[FRONT_CENTER] = 0.0f;
        soundFrontCenter->DecrementCount();
        
        testAudio->CreateSound(frontRight, &soundFrontRight);
        testvolumes[FRONT_RIGHT] = 1.0f;
        
        REQUIRE(G_SUCCESS(soundFrontRight->SetChannelVolumes(testvolumes, 6)));
        
        soundFrontRight->Play();
        sleep_ms(1000);
        testvolumes[FRONT_RIGHT] = 0.0f;
        soundFrontRight->DecrementCount();
    }
    
    GSound * soundSurroundRight = nullptr;
    GSound * soundBass = nullptr;
    GSound * soundSurroundLeft = nullptr;
    {
        testAudio->CreateSound(surroundLeft, &soundSurroundLeft);
        testvolumes[SURROUND_LEFT] = 1.0f;
        
        REQUIRE(G_SUCCESS(soundSurroundLeft->SetChannelVolumes(testvolumes, 6)));
        
        soundSurroundLeft->Play();
        sleep_ms(1000);
        testvolumes[SURROUND_LEFT] = 0.0f;
        soundSurroundLeft->DecrementCount();
        
        testAudio->CreateSound(bass, &soundBass);
        testvolumes[SURROUND_CENTER] = 1.0f;
        
        REQUIRE(G_SUCCESS(soundBass->SetChannelVolumes(testvolumes, 6)));
        
        soundBass->Play();
        sleep_ms(1000);
        testvolumes[SURROUND_CENTER] = 0.0f;
        soundBass->DecrementCount();
        
        testAudio->CreateSound(surroundRight, &soundSurroundRight);
        testvolumes[SURROUND_RIGHT] = 1.0f;
        
        REQUIRE(G_SUCCESS(soundSurroundRight->SetChannelVolumes(testvolumes, 6)));
        
        soundSurroundRight->Play();
        sleep_ms(1000);
        testvolumes[SURROUND_RIGHT] = 0.0f;
        soundSurroundRight->DecrementCount();
    }
    
	// Fail cases
    GSound * testSound = nullptr;
    testAudio->CreateSound(testBeep, &testSound);
    
	CHECK(testSound->SetChannelVolumes(nullptr, 0) == INVALID_ARGUMENT);
    
    testAudio->DecrementCount();
}

TEST_CASE("Setting sound volume", "[SetVolume]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    GSound * testSound = nullptr;
    testAudio->CreateSound(volume_5, &testSound);
    
	// Fail cases
	CHECK(testSound->SetVolume(-1) == INVALID_ARGUMENT);
	// Pass cases
	REQUIRE(G_SUCCESS(testSound->SetVolume(0.5)));
    
    testSound->Play();
    sleep_ms(1000);
    
    testAudio->DecrementCount();
}

TEST_CASE("Stopping sound", "[StopSound]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    GSound * testSound = nullptr;
    testAudio->CreateSound(soundStop, &testSound);
    testSound->Play();
    sleep_ms(1800);

	// Pass cases
	REQUIRE(G_SUCCESS(testSound->StopSound()));
    
    testAudio->DecrementCount();
}

TEST_CASE("Stopping sound after pausing", "[StopSound]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    GSound * testSound = nullptr;
    testAudio->CreateSound(testBeep, &testSound);
    testSound->Play();
    testSound->Pause();
    
    REQUIRE(G_SUCCESS(testSound->StopSound()));
    
    testAudio->DecrementCount();
}


#if 0
TEST_CASE("Editing sound PCM", "[EditPCM]")
{
	// const char* testdata = nullptr;
	// Pass cases
	// REQUIRE(G_SUCCESS(testSound->SetPCMShader(testdata)));
}
#endif


// Starting Music Tests
TEST_CASE("Starting music stream", "[StreamStart]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    GMusic * testMusic = nullptr;
    testAudio->CreateMusicStream(musicStreamStart, &testMusic);
    
    REQUIRE(G_SUCCESS(testMusic->StreamStart()));
    sleep_ms(2000);
    
    testAudio->DecrementCount();
}

TEST_CASE("Deleting music stream", "[DecrementCount]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    GMusic * testMusic = nullptr;
    testAudio->CreateMusicStream(testBeep, &testMusic); // testMusic musicCount = 2 (this handle, and audio has a handle)
    testMusic->StreamStart(); // plays for 0.5s then should trigger the audio callback CleanUpMusic() in GAudio.mm. musicCount = 1
    testMusic->DecrementCount(); // musicCount = 0
    sleep_ms(2000); // testMusic deletes at a safe time
    
    // [Pass case] Should throw an access violation when uncommented
    // There is no good way in c++ to check if something has been deleted.
    // testMusic->DecrementCount();
}

TEST_CASE("Pausing music stream", "[PauseStream]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    GMusic * testMusic = nullptr;
    testAudio->CreateMusicStream(musicPause, &testMusic);
    testMusic->StreamStart();
    sleep_ms(1800);
    
    // Pass cases
    REQUIRE(G_SUCCESS(testMusic->PauseStream()));
    
    testAudio->DecrementCount();
}

TEST_CASE("Resuming music stream", "[ResumeStream]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    GMusic * testMusic = nullptr;
    testAudio->CreateMusicStream(musicResume, &testMusic);
    testMusic->StreamStart();
    testMusic->PauseStream();
    
    // Pass cases
    REQUIRE(G_SUCCESS(testMusic->ResumeStream()));
    sleep_ms(1100);
    
    testAudio->DecrementCount();
}

TEST_CASE("Setting music channel volumes", "[SetChannelVolumes]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    float testvolumes[6] = { 0.0f, 0.0f, 0.0f ,0.0f, 0.0f, 0.0f };
    
    GMusic * musicFrontRight = nullptr;
    GMusic * musicFrontCenter = nullptr;
    GMusic * musicFrontLeft = nullptr;
    {
        testAudio->CreateMusicStream(frontLeft, &musicFrontLeft);
        testvolumes[FRONT_LEFT] = 1.0f;
        
        REQUIRE(G_SUCCESS(musicFrontLeft->SetChannelVolumes(testvolumes, 6)));
        
        musicFrontLeft->StreamStart();
        sleep_ms(1000);
        testvolumes[FRONT_LEFT] = 0.0f;
        musicFrontLeft->DecrementCount();
        
        testAudio->CreateMusicStream(frontCenter, &musicFrontCenter);
        testvolumes[FRONT_CENTER] = 1.0f;
        
        REQUIRE(G_SUCCESS(musicFrontCenter->SetChannelVolumes(testvolumes, 6)));
        
        musicFrontCenter->StreamStart();
        sleep_ms(1000);
        testvolumes[FRONT_CENTER] = 0.0f;
        musicFrontCenter->DecrementCount();
        
        testAudio->CreateMusicStream(frontRight, &musicFrontRight);
        testvolumes[FRONT_RIGHT] = 1.0f;
        
        REQUIRE(G_SUCCESS(musicFrontRight->SetChannelVolumes(testvolumes, 6)));
        
        musicFrontRight->StreamStart();
        sleep_ms(1000);
        testvolumes[FRONT_RIGHT] = 0.0f;
        musicFrontRight->DecrementCount();
    }
    
    GMusic * musicSurroundRight = nullptr;
    GMusic * musicBass = nullptr;
    GMusic * musicSurroundLeft = nullptr;
    {
        testAudio->CreateMusicStream(surroundLeft, &musicSurroundLeft);
        testvolumes[SURROUND_LEFT] = 1.0f;
        
        REQUIRE(G_SUCCESS(musicSurroundLeft->SetChannelVolumes(testvolumes, 6)));
        
        musicSurroundLeft->StreamStart();
        sleep_ms(1000);
        testvolumes[SURROUND_LEFT] = 0.0f;
        musicSurroundLeft->DecrementCount();
        
        testAudio->CreateMusicStream(bass, &musicBass);
        testvolumes[SURROUND_CENTER] = 1.0f;
        
        REQUIRE(G_SUCCESS(musicBass->SetChannelVolumes(testvolumes, 6)));
        
        musicBass->StreamStart();
        sleep_ms(1000);
        testvolumes[SURROUND_CENTER] = 0.0f;
        musicBass->DecrementCount();
        
        testAudio->CreateMusicStream(surroundRight, &musicSurroundRight);
        testvolumes[SURROUND_RIGHT] = 1.0f;
        
        REQUIRE(G_SUCCESS(musicSurroundRight->SetChannelVolumes(testvolumes, 6)));
        
        musicSurroundRight->StreamStart();
        sleep_ms(1000);
        testvolumes[SURROUND_RIGHT] = 0.0f;
        musicSurroundRight->DecrementCount();
    }
    
    // Fail cases
    GMusic * testMusic = nullptr;
    testAudio->CreateMusicStream(testSong, &testMusic);
    
    CHECK(testMusic->SetChannelVolumes(nullptr, 0) == INVALID_ARGUMENT);
    
    testAudio->DecrementCount();
}

TEST_CASE("Setting music volume", "[SetVolume]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    GMusic * testMusic = nullptr;
    testAudio->CreateMusicStream(volume1, &testMusic);
    
    // Fail cases
    CHECK(testMusic->SetVolume(-1) == INVALID_ARGUMENT);
    // Pass cases
    REQUIRE(G_SUCCESS(testMusic->SetVolume(1)));
    
    testMusic->StreamStart();
    sleep_ms(1000);
    
    testAudio->DecrementCount();
}

TEST_CASE("Stopping music stream", "[StopStream]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    GMusic * testMusic = nullptr;
    testAudio->CreateMusicStream(testSong, &testMusic);
    testMusic->StreamStart();
    
	// Pass cases
	REQUIRE(G_SUCCESS(testMusic->StopStream()));
    
    testAudio->DecrementCount();
}

TEST_CASE("Stopping music after pausing", "[StopStream]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    GMusic * testMusic = nullptr;
    testAudio->CreateMusicStream(testSong, &testMusic);
    testMusic->StreamStart();
    testMusic->PauseStream();
    
    // Pass cases
    REQUIRE(G_SUCCESS(testMusic->StopStream()));
    
    testAudio->DecrementCount();
}


#if 0
TEST_CASE("Editing test music PCM", "[EditPCM]")
{
   // const char* testdata = nullptr;
   // Pass cases
   // REQUIRE(G_SUCCESS(testMusic->SetPCMShader(testdata)));
}
#endif


// Last of Audio Tests
TEST_CASE("Setting master volume", "[SetMasterVolume]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    GSound * testSound = nullptr;
    GMusic * testMusic = nullptr;
    
    CHECK(testAudio->SetMasterVolume(-1) == INVALID_ARGUMENT);
    
    REQUIRE(G_SUCCESS(testAudio->SetMasterVolume(1)));
    
    testAudio->CreateSound(masterVolume1, &testSound);
    testSound->Play();
    sleep_ms(2000);
    testSound->StopSound();
    
    REQUIRE(G_SUCCESS(testAudio->SetMasterVolume(0.5f)));
    
    testAudio->CreateMusicStream(masterVolume_5, &testMusic);
    testMusic->StreamStart();
    sleep_ms(2000);
    testMusic->StopStream();
    
    testAudio->DecrementCount();
}

TEST_CASE("Pausing all sounds and music.", "[PauseAll]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    
    GMusic * testMusic = nullptr;
    testAudio->CreateMusicStream(musicPause, &testMusic);
    testMusic->SetChannelVolumes(LEFT_EAR, 6);
    
    GSound * testSound = nullptr;
    testAudio->CreateSound(soundPause, &testSound);
    testSound->SetChannelVolumes(RIGHT_EAR, 6);
    
    testMusic->StreamStart();
    testSound->Play();
    sleep_ms(1800);

	REQUIRE(G_SUCCESS(testAudio->PauseAll()));

    testAudio->DecrementCount();
}

TEST_CASE("Setting master channel volumes", "[SetMasterChannelVolumes]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    
    GMusic * testMusic = nullptr;
    testAudio->CreateMusicStream(volume_5, &testMusic);
    testMusic->SetChannelVolumes(LEFT_EAR, 6);
    
    GSound * testSound = nullptr;
    testAudio->CreateSound(volume_5, &testSound);
    testSound->SetChannelVolumes(RIGHT_EAR, 6);
    
	// Fail cases
	CHECK(testAudio->SetMasterChannelVolumes(nullptr, 0) == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(testAudio->SetMasterChannelVolumes(HALVES, 6)));
    
    testMusic->StreamStart();
    testSound->Play();
    sleep_ms(2000);
    
    testAudio->DecrementCount();
}

TEST_CASE("Resuming all sounds and music.", "[ResumeAll]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    
    GMusic * testMusic = nullptr;
    testAudio->CreateMusicStream(musicResume, &testMusic);
    testMusic->SetChannelVolumes(LEFT_EAR, 6);
    
    GSound * testSound = nullptr;
    testAudio->CreateSound(soundResume, &testSound);
    testSound->SetChannelVolumes(RIGHT_EAR, 6);
    
    testMusic->StreamStart();
    testSound->Play();
    testAudio->PauseAll();
    
    REQUIRE(G_SUCCESS(testAudio->ResumeAll()));
    sleep_ms(1100);
    
    testAudio->DecrementCount();
}

TEST_CASE("DecrementCount cleans up all music and sound", "[DecrementCount]")
{
    GAudio * testAudio = nullptr;
    CreateGAudio(&testAudio);
    
    GMusic * testMusic = nullptr;
    testAudio->CreateMusicStream(testBeep, &testMusic);
    
    GSound * testSound = nullptr;
    testAudio->CreateSound(testBeep, &testSound);
    
    testMusic->StreamStart();
    testSound->Play();
    
    testAudio->DecrementCount();
    
    sleep_ms(1000);
    
    testMusic->StreamStart();
    testSound->Play();
}

