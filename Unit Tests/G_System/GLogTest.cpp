//Needed for Catch
#include "../Unit Tests/Common.h"

//THESE TEST CASES ARE SET UP IN A SPECIFIC ORDER. REORDERING TEST CASES COULD CAUSE
//CRASHES, FALSE FAILURES, or FALSE PASSES
/*
//Globals used for all test cases
GW::SYSTEM::GLog* m_log;
GW::SYSTEM::GFile* m_testFile; //Required for one of the create functions


// ALL DEVELOPERS!!! USE THIS AS AN EXAMPLE OF HOW TO DO CORE GINTERFACE TESTING!!!
GW::SYSTEM::GLog *GLog_specific = nullptr;
GW::CORE::GInterface *GLog_generic = nullptr;
// CORE GINTERFACE TEST BATTERY. ALL GATEWARE INTERFACES MUST BE ABLE TO PASS THESE TESTS.
TEST_CASE("GLog core test battery", "[CreateGLog], [RequestInterface], [IncrementCount], [DecrementCount], [GetCount]")
{
	// CATCH WARNING!!!
	// Any variables declared here will be REPLICATED to EACH SECTION.
	// If you need connectivity between sections your variables will need to be global or static.
	unsigned int countS = 0, countG = 0;
	const GW::GUUIID notAnValidInterface = { 0, };

	// THE CREATION FUNCTION IS UNIQUE MOST EVERYTHING BELOW THIS SHOULD BE THE SAME FOR ALL INTERFACES
	SECTION("Creation Tests", "[CreateGLog]")
	{
		CHECK(GW::SYSTEM::CreateGLog("Something" ,nullptr) == GW::INVALID_ARGUMENT);
		// TODO: Add additonal Creation parameter testing here as nessasary.
		REQUIRE(G_SUCCESS(GW::SYSTEM::CreateGLog("./DONOTDELETE.txt", &GLog_specific)));
		REQUIRE(GLog_specific != nullptr);
	}
	// The following tests can be copied verbatim as they are completly GLog_generic for all interfaces
	SECTION("Interface Request Tests", "[RequestInterface]")
	{
		CHECK(GLog_specific->RequestInterface(notAnValidInterface, nullptr) == GW::INVALID_ARGUMENT);
		CHECK(GLog_specific->RequestInterface(notAnValidInterface, (void**)&GLog_generic) == GW::INTERFACE_UNSUPPORTED);
		CHECK(GLog_generic == nullptr); // should not have changed yet
		REQUIRE(G_SUCCESS(GLog_specific->RequestInterface(GW::CORE::GInterfaceUUIID, (void**)&GLog_generic)));
		REQUIRE(GLog_generic != nullptr);
		// memory addresses should match
		REQUIRE(reinterpret_cast<std::uintptr_t>(GLog_generic) == reinterpret_cast<std::uintptr_t>(GLog_specific));
	}
	// Test reference counting behavior
	SECTION("Reference Counting Tests", "[GetCount], [IncrementCount], [DecrementCount]")
	{
		REQUIRE(G_SUCCESS(GLog_specific->GetCount(countS)));
		REQUIRE(G_SUCCESS(GLog_generic->GetCount(countG)));
		CHECK(countS == countG);
		CHECK(countS == 2); // should be exactly 2 references at this point
		REQUIRE(G_SUCCESS(GLog_specific->IncrementCount())); // 3
		REQUIRE(G_SUCCESS(GLog_generic->IncrementCount())); // 4
		GLog_specific->GetCount(countS);
		GLog_generic->GetCount(countG);
		CHECK(countS == countG);
		CHECK(countS == 4); // should be exactly 4 references at this point
		REQUIRE(G_SUCCESS(GLog_specific->DecrementCount())); // 3
		REQUIRE(G_SUCCESS(GLog_generic->DecrementCount())); // 2
		// Free GLog_specific pointer (user simulation of interface deletion)
		CHECK(G_SUCCESS(GLog_specific->DecrementCount())); // 1
		GLog_specific = nullptr; // this pointer should not longer be valid from users standpoint (though it is)
		GLog_generic->GetCount(countG);
		REQUIRE(countG == 1); // should be last remaining handle
	}
	// Finally test interface Forward Compatibilty
	SECTION("Forward Compatibility Tests", "[RequestInterface], [GetCount], [DecrementCount]")
	{
		CHECK(GLog_generic->RequestInterface(notAnValidInterface, nullptr) == GW::INVALID_ARGUMENT);
		CHECK(GLog_generic->RequestInterface(notAnValidInterface, (void**)&GLog_specific) == GW::INTERFACE_UNSUPPORTED);
		CHECK(GLog_specific == nullptr); // should not have changed yet
		// TODO: Check that GLog_generic interface supports upgrading to ALL relevant interfaces in the class heirarchy chain
		REQUIRE(G_SUCCESS(GLog_generic->RequestInterface(GW::SYSTEM::GLogUUIID, (void**)&GLog_specific))); // 2
		CHECK(GLog_specific != nullptr); // GLog_specific pointer is valid again
		GW::CORE::GSingleThreaded *singleSupport = nullptr;
		GW::CORE::GMultiThreaded *multiSupport = nullptr;
		REQUIRE(G_FAIL(GLog_generic->RequestInterface(GW::CORE::GSingleThreadedUUIID, (void**)&singleSupport)));
		CHECK(singleSupport == nullptr); // GLog is NOT singlethreaded
		REQUIRE(G_SUCCESS(GLog_generic->RequestInterface(GW::CORE::GMultiThreadedUUIID, (void**)&multiSupport))); // 3
		CHECK(multiSupport != nullptr); // GLog IS multithreaded
		// Check final count VS expectations
		REQUIRE(G_SUCCESS(multiSupport->GetCount(countS)));
		CHECK(countS == 3); // three valid handles should exist now
		// Free all handles, all should succeed
		REQUIRE(G_SUCCESS(multiSupport->DecrementCount())); // 2
		REQUIRE(G_SUCCESS(GLog_specific->DecrementCount())); // 1
		GLog_generic->GetCount(countG);
		REQUIRE(countG == 1); // should be last remaining handle (again)
		REQUIRE(G_SUCCESS(GLog_generic->DecrementCount())); // 0
	}
	// done with standard tests, the memory for the object should be released at this point and all pointers should be invalid
}

// Custom Unit Tests specific to this interface follow..


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
	REQUIRE(G_SUCCESS(GW::SYSTEM::CreateGLog("../../../../Xcode/Unit Tests/DONOTDELETE.txt", &m_log)));
#elif __linux__
	REQUIRE(G_SUCCESS(GW::SYSTEM::CreateGLog("./DONOTDELETE.txt", &m_log)));
#endif


	REQUIRE(G_SUCCESS(m_log->DecrementCount()));

	GW::SYSTEM::CreateGFile(&m_testFile);
#ifdef WIN32
	m_testFile->SetCurrentWorkingDirectory(u8"./");
#elif __APPLE__
	m_testFile->SetCurrentWorkingDirectory(u8"../../../../Xcode/Unit Tests");
#elif __linux__
	m_testFile->SetCurrentWorkingDirectory(u8"./");
#endif
	m_testFile->OpenTextWrite("DONOTDELETE.txt");

	REQUIRE(G_SUCCESS(GW::SYSTEM::CreateGLogCustom(m_testFile, &m_log)));
}

//Testing logging

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
