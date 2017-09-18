
#include "../Unit Tests/Common.h"

//Includes needed for this test suite
#include <cstring>
#include <iostream>

//This is the ammount of files that should be in the directory after all test cases run
#define DIR_SIZE 9

//Test case file names will not be larger than 40 characters
#define FILE_NAME_SIZE 40

//THESE TEST CASES ARE SET UP IN A SPECIFIC ORDER. REORDERING TEST CASES COULD CAUSE
//CRASHES, FALSE FAILURES, or FALSE PASSES

//Globals used for all test cases.
GW::SYSTEM::GFile* file = nullptr;
char directoryBuffer[260]; //Same size as MAX_PATH MACRO
//Used in directory testing continued
unsigned int dirSize;


TEST_CASE("Create GFile object.", "[CreateGFile]")
{
	//Fail cases
	CHECK(GW::SYSTEM::CreateGFile(nullptr) == GW::INVALID_ARGUMENT);

	//Pass cases
	REQUIRE(G_SUCCESS(GW::SYSTEM::CreateGFile(&file)));
	REQUIRE(file != nullptr);
}

TEST_CASE("Directory handling.", "[SetCurrentWorkingDirectory], [GetCurrentWorkingDirectory]")
{

	SECTION("Setting the current working directory.", "[SetCurrentWorkingDirectory]")
	{
		//Fail cases
		CHECK(file->SetCurrentWorkingDirectory(nullptr) == GW::INVALID_ARGUMENT);
		CHECK(G_FAIL(file->SetCurrentWorkingDirectory("./A NonExsitant Directory")));

		//Pass cases

#ifdef WIN32
		REQUIRE(G_SUCCESS(file->SetCurrentWorkingDirectory(u8"./")));
#elif __APPLE__
		REQUIRE(G_SUCCESS(file->SetCurrentWorkingDirectory(u8"../../../../Xcode/Unit Tests")));
#elif __linux__
		REQUIRE(G_SUCCESS(file->SetCurrentWorkingDirectory(u8"./")));
#endif
		//REQUIRE(G_SUCCESS(file->SetCurrentWorkingDirectory(u8"../gateware-test-suite.git.0/XCode/Gateware/GTests/TestDirectory")));
	}

	SECTION("Get current working directory.", "[GetCurrentWorkingDirectory]")
	{
		//Fail cases
		CHECK(file->GetCurrentWorkingDirectory(nullptr, 1) == GW::INVALID_ARGUMENT);
		CHECK(file->GetCurrentWorkingDirectory(&directoryBuffer[0], 0) == GW::INVALID_ARGUMENT);

		//Pass cases
		REQUIRE(G_SUCCESS(file->GetCurrentWorkingDirectory(directoryBuffer, 260)));
	}
}


TEST_CASE("Binary file testing.", "[OpenBinaryWrite], [Write], [AppendBinaryWrite], [OpenBinaryRead], [Read]")
{
	SECTION("Open binary file for writing.", "[OpenBinaryWrite]")
	{
		//Pass cases. Pass cases are first in this case because we have to open a file before we can check the fail outs
		REQUIRE(G_SUCCESS(file->OpenBinaryWrite(u8"g_binary_test.gtest")));

		//Fail cases
		CHECK(G_FAIL(file->OpenBinaryWrite(u8"g_binary_test.gtest")));
	}

	//Writing to binary file
	SECTION("Write to binary file.", "[Write]")
	{
		//Pass cases
		//Write the current directory to the file.
		REQUIRE(G_SUCCESS(file->Write(directoryBuffer, strlen(directoryBuffer) + 1)));

		//We need to close the file in order to test some of the fail cases
		file->CloseFile();

		//Fail cases
		CHECK(G_FAIL(file->Write(directoryBuffer, strlen(directoryBuffer) + 1)));
		CHECK(file->Write(nullptr, 1) == GW::INVALID_ARGUMENT);
		CHECK(file->Write(directoryBuffer, 0) == GW::INVALID_ARGUMENT);
		CHECK(file->Write(nullptr, 0) == GW::INVALID_ARGUMENT);
	}

	SECTION("Open binary file for appending.", "[AppendBinaryWrite]")
	{
		//Pass cases
		REQUIRE(G_SUCCESS(file->AppendBinaryWrite(u8"g_binary_test.gtest")));

		//Fail cases
		CHECK(G_FAIL(file->AppendBinaryWrite(u8"g_binary_test.gtest")));

		//We need to close the file now so future tests can open a file
		file->CloseFile();
	}

	SECTION("Open file for binary read.", "[OpenBinaryRead]")
	{
		//Special fail case
		REQUIRE(file->OpenBinaryRead(u8"FileThatDoesntExist.bin") == GW::FILE_NOT_FOUND);

		//Pass cases
		REQUIRE(G_SUCCESS(file->OpenBinaryRead(u8"g_binary_test.gtest")));

		//Fail cases
		CHECK(G_FAIL(file->OpenBinaryRead(u8"g_binary_test.gtest")));
		CHECK(file->OpenBinaryRead(nullptr) == GW::INVALID_ARGUMENT);
	}

	SECTION("Read in from binary file.", "[Read]")
	{
		char buffer[260] = {'\0'}; //Same size as our directoryBuffer.

		//Pass cases
		REQUIRE(G_SUCCESS(file->Read(buffer, strlen(directoryBuffer) + 1)));
		REQUIRE(strcmp(buffer, directoryBuffer) == 0);

		//We need to close the file to ensure we can not write to a closed file
		file->CloseFile();

		//Fail cases
		CHECK(G_FAIL(file->Read(&buffer[0], 260)));
	}
}

TEST_CASE("Text file testing.", "[OpenTextWrite], [WriteLine], [AppendTextWrite], [OpenTextRead], [ReadLine]")
{
	SECTION("Open file for text write", "[OpenTextWrite]")
	{
		//Pass cases.
		REQUIRE(G_SUCCESS(file->OpenTextWrite(u8"g_test.gtest")));

		//Fail cases
		CHECK(G_FAIL(file->OpenTextWrite(u8"g_test.gtest")));
		CHECK(file->OpenTextWrite(nullptr) == GW::INVALID_ARGUMENT);

	}

	SECTION("Write to text file.", "[WriteLine]")
	{
		//Pass cases
		REQUIRE(G_SUCCESS(file->WriteLine(directoryBuffer)));

		//Close the file to make sure we can not write to a closed file
		file->CloseFile();

		//Fail cases
		CHECK(file->WriteLine(nullptr) == GW::INVALID_ARGUMENT);
		CHECK(G_FAIL(file->WriteLine(directoryBuffer)));
	}

	SECTION("Open text file for appending.", "[AppendTextWrite]")
	{
		//Pass cases
		REQUIRE(G_SUCCESS(file->AppendTextWrite(u8"g_test.gtest")));

		//Fail cases
		CHECK(file->AppendTextWrite(nullptr) == GW::INVALID_ARGUMENT);
		CHECK(G_FAIL(file->AppendTextWrite(u8"g_test.gtest")));

		//We need to close the file so future tests can open files
		file->CloseFile();
	}

	SECTION("Open file for text read.", "[OpenTextRead]")
	{
		//Special fail Case
		REQUIRE(file->OpenTextRead(u8"FileThatDoesntExist.bin") == GW::FILE_NOT_FOUND);

		//Pass cases
		REQUIRE(G_SUCCESS(file->OpenTextRead(u8"g_test.gtest")));

		//Fail cases
		CHECK(file->OpenTextRead(nullptr) == GW::INVALID_ARGUMENT);
		CHECK(G_FAIL(file->OpenTextRead(u8"g_test.gtest")));
	}

	//Read in from the text file
	SECTION("Read in from text file.", "[Readline]")
	{
		char buffer[260];// Same size as directoryBuffer

		//Pass cases.
		REQUIRE(G_SUCCESS(file->ReadLine(buffer, 260, '\n')));

		REQUIRE(strcmp(buffer, directoryBuffer) == 0);

		//Close the file at end of testing. Will no longer be needed
		file->CloseFile();

		//Fail cases
		CHECK(file->ReadLine(nullptr, 1, '\n') == GW::INVALID_ARGUMENT);
		CHECK(file->ReadLine(&buffer[0], 0, '\n') == GW::INVALID_ARGUMENT);
		CHECK(G_FAIL(file->ReadLine(&buffer[0], 260, '\0')));
	}
}

TEST_CASE("Directory Handling continued.", "[GetDirectorySize], [GetFileSize], [GetFilesFromDirectory]")
{
	SECTION("Getting directory size.", "[GetDirectorySize]")
	{
		//Pass cases
#ifdef _WIN32
		REQUIRE(G_SUCCESS(file->SetCurrentWorkingDirectory(u8"../../../../gateware.git.0")));
		REQUIRE(G_SUCCESS(file->GetDirectorySize(dirSize)));
		REQUIRE(dirSize == DIR_SIZE); //9 is the number of files that should be in the directory after all other testing
#elif __APPLE__
		REQUIRE(G_SUCCESS(file->SetCurrentWorkingDirectory(u8"../../../../../gateware.git.0")));
		REQUIRE(G_SUCCESS(file->GetDirectorySize(dirSize)));
		REQUIRE(dirSize == DIR_SIZE); //9 is the number of files that should be in the directory after all other testing
#elif __linux__
		REQUIRE(G_SUCCESS(file->SetCurrentWorkingDirectory(u8"../../../../../../gateware.git.0")));
		REQUIRE(G_SUCCESS(file->GetDirectorySize(dirSize)));
		REQUIRE(dirSize == DIR_SIZE); //9 is the number of files that should be in the directory after all other testing
#endif 


		//Fail cases
		//This function should not fail.

		SECTION("Getting all files in the directory.", "[GetFilesFromDirectory]")
		{
			//Create a string buffer to hold our filenames
			int MatchNum = 0;
			char* files[DIR_SIZE];
			char* Checklist[DIR_SIZE];

			for (unsigned int i = 0; i < dirSize; ++i)
				files[i] = new char[FILE_NAME_SIZE];

			//Pass cases
			REQUIRE(G_SUCCESS(file->GetFilesFromDirectory(files, dirSize, FILE_NAME_SIZE)));
			
			Checklist[0] = ".DS_Store";
			Checklist[1] = ".gitignore";
			Checklist[2] = "CMakeLists.txt";
			Checklist[3] = "Doxyfile";
			Checklist[4] = "LICENSE.md";
			Checklist[5] = "LinuxSetup";
			Checklist[6] = "MacSetup.command";
			Checklist[7] = "README.md";
			Checklist[8] = "WinSetup.bat";

			for (int i = 0; i < DIR_SIZE; i++)
			{
				for (int j = 0; j < DIR_SIZE; j++)
				{
					if (strcmp(files[i], Checklist[j]) == 0)
					{
						MatchNum++;
						break;
					}
					else
						continue;
				}
			}
			REQUIRE(MatchNum == 9);

			for (unsigned int i = 0; i < dirSize; ++i)
				delete[] files[i];
		}
	}

	//Finished with the file so decrement the count and release it
	file->DecrementCount();
}
