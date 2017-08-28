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
const char * testpath = "TestBeep.wav";
//Starting Audio Tests, some can't be tested until sound/music starts playing
TEST_CASE("Create GAudio.", "[CreateGAudio]")
{
	// Fail cases
	CHECK(GW::AUDIO::CreateGAudio(nullptr));

	// Pass cases
	REQUIRE(G_SUCCESS(CreateGAudio(&testAudio)));
}
TEST_CASE("Initialize Audio", "[Init]")
{	

	// Fail cases
	//CHECK(testAudio->Init() == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(testAudio->Init()));
}
TEST_CASE("Creating Sound.", "[CreateSound]")
{
	// Fail cases
	CHECK(testAudio->CreateSound(testpath,nullptr) == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(testAudio->CreateSound(testpath, &testSound)));
}
TEST_CASE("Creating music.", "[CreateMusic]")
{
	// Fail cases
	CHECK(testAudio->CreateMusicStream(testpath, nullptr) == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(testAudio->CreateMusicStream(testpath, &testMusic)));
}
TEST_CASE("Setting master channel volumes", "[SetMasterChannelVolumes]")
{
	float atestVolume = 0.5f;
	const float * testvolumes = &atestVolume;
	// Fail cases
	CHECK(testAudio->SetMasterChannelVolumes(nullptr,1) == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(testAudio->SetMasterChannelVolumes(testvolumes, 1)));
}
TEST_CASE("Setting master volume", "[SetMasterVolume]")
{

	// Fail cases
	CHECK(testAudio->SetMasterVolume(-1) == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(testAudio->SetMasterVolume(1)));
}

//Starting Sound Tests
TEST_CASE("Playing test sound", "[PlaySound]")
{
	// Fail cases
	// CHECK(testSound->PlaySound() == INVALID_ARGUMENT);
	// Pass cases
	REQUIRE(G_SUCCESS(testSound->PlaySound()));
}
TEST_CASE("Pausing test sound", "[Pause]")
{

	// Fail cases
	//CHECK(testSound->Pause() == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(testSound->Pause()));
}
TEST_CASE("Resuming test sound", "[Resume]")
{
	// Fail cases
	//CHECK(testSound->Resume() == INVALID_ARGUMENT);
	// Pass cases
	REQUIRE(G_SUCCESS(testSound->Resume()));
}
TEST_CASE("Setting sound channel volumes", "[SetChannelVolumes]")
{
	float atestVolume = 0.5f;
	float * testvolumes = &atestVolume;
	// Fail cases
	CHECK(testSound->SetChannelVolumes(nullptr, 1) == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(testSound->SetChannelVolumes(testvolumes, 1)));
}
TEST_CASE("Setting test sound volume", "[SetVolume]")
{
	// Fail cases
	//CHECK(testSound->Resume() == INVALID_ARGUMENT);
	// Pass cases
	REQUIRE(G_SUCCESS(testSound->SetVolume(1)));
}
TEST_CASE("Stop test sound", "[StopSound]")
{
	// Fail cases
	//CHECK(testSound->Resume() == INVALID_ARGUMENT);
	// Pass cases
	REQUIRE(G_SUCCESS(testSound->StopSound()));
}
//TEST_CASE("Editing test sound PCM", "[EditPCM]")
//{
//	const char* testdata = nullptr;
//	// Fail cases
//	//CHECK(testSound->Resume() == INVALID_ARGUMENT);
//	// Pass cases
//	REQUIRE(G_SUCCESS(testSound->SetPCMShader(testdata)));
//}

//Starting Music Tests
TEST_CASE("Playing test music", "[Playmusic]")
{
	// Fail cases
	// CHECK(testmusic->Playmusic() == INVALID_ARGUMENT);
	// Pass cases
	REQUIRE(G_SUCCESS(testMusic->StreamStart()));
}
TEST_CASE("Pausing test music", "[Pause]")
{

	// Fail cases
	//CHECK(testmusic->Pause() == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(testMusic->PauseStream()));
}
TEST_CASE("Resuming test music", "[Resume]")
{
	// Fail cases
	//CHECK(testmusic->Resume() == INVALID_ARGUMENT);
	// Pass cases
	REQUIRE(G_SUCCESS(testMusic->ResumeStream()));
}
TEST_CASE("Setting music channel volumes", "[SetChannelVolumes]")
{
	float atestVolume = 0.5f;
	float * testvolumes = &atestVolume;
	// Fail cases
	CHECK(testMusic->SetChannelVolumes(nullptr, 1) == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(testMusic->SetChannelVolumes(testvolumes, 1)));
}
TEST_CASE("Setting test music volume", "[SetVolume]")
{
	// Fail cases
	//CHECK(testmusic->Resume() == INVALID_ARGUMENT);
	// Pass cases
	REQUIRE(G_SUCCESS(testMusic->SetVolume(1)));
}
TEST_CASE("Stop test music", "[Stopmusic]")
{
	// Fail cases
	//CHECK(testmusic->Resume() == INVALID_ARGUMENT);
	// Pass cases
	REQUIRE(G_SUCCESS(testMusic->StopStream()));
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
	testSound->PlaySound();

	// Pass cases
	REQUIRE(G_SUCCESS(testAudio->PauseAll()));
}
TEST_CASE("Resuming all sounds and music.", "[ResumeAll]")
{

	// Pass cases
	REQUIRE(G_SUCCESS(testAudio->ResumeAll()));
}
