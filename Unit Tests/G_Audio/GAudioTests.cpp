#include "../G_System/Common.h"
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
GMusic * testMusic = nullptr;
GMusic * testMusic2 = nullptr;
GReturn checkReturned = FAILURE;

const char * testpath = "TestBeep.wav";
const char * testpath2 = "TestMusic.wav";
const char * testpath3 = "TestMusic2.wav";
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

	// Fail cases
	//CHECK(testAudio->Init() == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testAudio->Init()));
	checkReturned = FAILURE;
}
TEST_CASE("Creating Sound.", "[CreateSound]")
{
	// Fail cases
	CHECK(testAudio->CreateSound(testpath, nullptr) == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testAudio->CreateSound(testpath, &testSound)));
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
	checkReturned = FAILURE;
}
TEST_CASE("Pausing test sound", "[Pause]")
{

	// Fail cases
	//CHECK(testSound->Pause() == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testSound->Pause()));
	checkReturned = FAILURE;
}
TEST_CASE("Resuming test sound", "[Resume]")
{
	// Fail cases
	//CHECK(testSound->Resume() == INVALID_ARGUMENT);
	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testSound->Resume()));
	checkReturned = FAILURE;
}
TEST_CASE("Setting sound channel volumes", "[SetChannelVolumes]")
{
	float atestVolume = 0.5f;
	float * testvolumes = &atestVolume;
	// Fail cases
	CHECK(testSound->SetChannelVolumes(nullptr, 0) == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testSound->SetChannelVolumes(testvolumes, 1)));
	checkReturned = FAILURE;
}
TEST_CASE("Setting test sound volume", "[SetVolume]")
{
	// Fail cases
	CHECK(testSound->SetVolume(-1) == INVALID_ARGUMENT);
	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testSound->SetVolume(1)));
	checkReturned = FAILURE;
}
TEST_CASE("Stop test sound", "[StopSound]")
{
	// Fail cases
	//CHECK(testSound->Resume() == INVALID_ARGUMENT);
	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testSound->StopSound()));
	checkReturned = FAILURE;
}
//TEST_CASE("Editing test sound PCM", "[EditPCM]")
//{
//	const char* testdata = nullptr;
//	// Fail cases
//	//CHECK(testSound->Resume() == INVALID_ARGUMENT);
//	// Pass cases
//	REQUIRE(G_SUCCESS(testSound->SetPCMShader(testdata)));
//}
TEST_CASE("Setting music channel volumes", "[SetChannelVolumes]")
{
	float atestVolume[2] = { 0.3f ,1.0f };
	float * testvolumes = atestVolume;
	// Fail cases
	CHECK(testMusic->SetChannelVolumes(nullptr, 1) == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testMusic->SetChannelVolumes(testvolumes, 2)));
	float atestVolume2[2] = { 1.0f ,1.0f };
	float * testvolumes2 = atestVolume;
	REQUIRE(G_SUCCESS(checkReturned = testMusic->SetChannelVolumes(testvolumes2, 2)));
	checkReturned = FAILURE;
}
//Starting Music Tests
TEST_CASE("Playing test music", "[Playmusic]")
{
	// Fail cases
	// CHECK(testmusic->Playmusic() == INVALID_ARGUMENT);
	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testMusic->StreamStart()));
	REQUIRE(G_SUCCESS(checkReturned = testMusic2->StreamStart()));
	checkReturned = FAILURE;
}
TEST_CASE("Pausing test music", "[Pause]")
{

	// Fail cases
	//CHECK(testmusic->Pause() == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testMusic->PauseStream()));
	checkReturned = FAILURE;
}
TEST_CASE("Resuming test music", "[Resume]")
{
	// Fail cases
	//CHECK(testmusic->Resume() == INVALID_ARGUMENT);
	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testMusic->ResumeStream()));
	checkReturned = FAILURE;
}

TEST_CASE("Setting test music volume", "[SetVolume]")
{
	// Fail cases
	CHECK(testMusic->SetVolume(-1) == INVALID_ARGUMENT);
	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testMusic->SetVolume(1)));
	checkReturned = FAILURE;
}
TEST_CASE("Stop test music", "[Stopmusic]")
{
	// Fail cases
	//CHECK(testmusic->Resume() == INVALID_ARGUMENT);
	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testMusic->StopStream()));
	checkReturned = FAILURE;
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
	testMusic->StreamStart();
	testSound->Play();

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testAudio->PauseAll()));
	checkReturned = FAILURE;
}
TEST_CASE("Setting master channel volumes", "[SetMasterChannelVolumes]")
{
	float atestVolume[2] = { 1.0f, 1.0f };
	const float * testvolumes = atestVolume;
	// Fail cases
	CHECK(testAudio->SetMasterChannelVolumes(nullptr, 0) == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testAudio->SetMasterChannelVolumes(testvolumes, 1)));
	checkReturned = FAILURE;
}
TEST_CASE("Resuming all sounds and music.", "[ResumeAll]")
{

	// Pass cases
	REQUIRE(G_SUCCESS(checkReturned = testAudio->ResumeAll()));
	checkReturned = FAILURE;
}
//TEST_CASE("Stopping all sounds and music.", "[Stopll]")
//{
//
//	// Pass cases
//	REQUIRE(G_SUCCESS(checkReturned = testAudio->StopAll()));
//	checkReturned = FAILURE;
//}
