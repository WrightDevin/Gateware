//Needed for Catch
#include "Common.h"

//THESE TEST CASES ARE SET UP IN A SPECIFIC ORDER. REORDERING TEST CASES COULD CAUSE
//CRASHES, FALSE FAILURES, or FALSE PASSES

//Globals used for all test cases
GW::SYSTEM::GLog* m_log;
GW::SYSTEM::GFile* m_testFile; //Required for one of the create functions

//Testing creating a GLog
TEST_CASE("Creating a GLog.", "[CreateGLog]")
{
	//Fail cases
	REQUIRE(GW::SYSTEM::CreateGLog("Something", nullptr) == GW::INVALID_ARGUMENT);
	REQUIRE(GW::SYSTEM::CreateGLogCustom(m_testFile, nullptr) == GW::INVALID_ARGUMENT);
	REQUIRE(GW::SYSTEM::CreateGLogCustom(m_testFile, &m_log) == GW::INVALID_ARGUMENT);

	//Pass cases
#ifdef WIN32
	REQUIRE(G_SUCCESS(GW::SYSTEM::CreateGLog("./DONOTDELETE.txt", &m_log)));
#elif __APPLE__
	REQUIRE(G_SUCCESS(GW::SYSTEM::CreateGLog("../../../../Xcode/Unit Tests/CMakeFiles/DONOTDELETE.txt", &m_log)));
#elif __linux__
	REQUIRE(G_SUCCESS(GW::SYSTEM::CreateGLog("./DONOTDELETE.txt", &m_log)));
#endif


	REQUIRE(G_SUCCESS(m_log->DecrementCount()));

	GW::SYSTEM::CreateGFile(&m_testFile);
#ifdef WIN32
	m_testFile->SetCurrentWorkingDirectory(u8"./");
#elif __APPLE__
	m_testFile->SetCurrentWorkingDirectory(u8"../../../../Xcode/Unit Tests/CMakeFiles");
#elif __linux__
	m_testFile->SetCurrentWorkingDirectory(u8"./");
#endif
	m_testFile->OpenTextWrite("DONOTDELETE.txt");

	REQUIRE(G_SUCCESS(GW::SYSTEM::CreateGLogCustom(m_testFile, &m_log)));
}

//Testing logging
/*
TEST_CASE("Testing logging functions", "[Log], [LogCategorized]")
{
	//Fail cases
	REQUIRE(m_log->Log(nullptr) == GW::INVALID_ARGUMENT);
	REQUIRE(m_log->LogCatergorized(nullptr, "Something") == GW::INVALID_ARGUMENT);
	REQUIRE(m_log->LogCatergorized("Something", nullptr) == GW::INVALID_ARGUMENT);

	//Pass cases
	REQUIRE(G_SUCCESS(m_log->Log("Something I wanna do.")));
	//Turn verbose logging off and try again
	m_log->EnableVerboseLogging(false);
	REQUIRE(G_SUCCESS(m_log->Log("Something else I wanna do.")));

	REQUIRE(G_SUCCESS(m_log->LogCatergorized("MINE", "Something I wanna do more")));
	//Turn verbose logging on and try again
	m_log->EnableVerboseLogging(true);
	REQUIRE(G_SUCCESS(m_log->LogCatergorized("MINE", "Something I wanna do more")));

	//Test flush
	REQUIRE(G_SUCCESS(m_log->Flush()));

	//Finished with the testing. Release the resources.
	m_log->DecrementCount();
	m_testFile->DecrementCount();
}
*/
