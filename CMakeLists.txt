#CMAKE TEXT FILE FOR THE CREATION OF THE PROJECT THAT CREATES STATIC/DYNAMIC LIBRARIES
cmake_minimum_required(VERSION 3.5)

###################################################################################################################################Get Version Info from gateware.ver

file (READ "${CMAKE_CURRENT_SOURCE_DIR}/gateware.ver" GATEWARE_MAJOR OFFSET 15 LIMIT 5)
string(REGEX MATCH [0-9]+ VERSION_MAJOR ${GATEWARE_MAJOR})

file (READ "${CMAKE_CURRENT_SOURCE_DIR}/gateware.ver" GATEWARE_MINOR OFFSET 30)
string(REGEX MATCH [0-9]+ VERSION_MINOR ${GATEWARE_MINOR})

file (READ "${CMAKE_CURRENT_SOURCE_DIR}/gateware.ver" GATEWARE_PATCH OFFSET 50)
string(REGEX MATCH "[A-z]+" VERSION_PATCH ${GATEWARE_PATCH})

###################################################################################################################################Create Version.h

execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the latest abbreviated commit hash of the working branch
execute_process(
  COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

#Set GATEWARE_VERSION_STRING_LONG  &  GATEWARE_VERSION_STRING_LONG 
SET(VERSION "Gateware v${VERSION_MAJOR}.${VERSION_MINOR}${VERSION_PATCH}")
SET(VERSION_LONG "${VERSION} (${GIT_BRANCH}) [${GIT_COMMIT_HASH}]")

add_definitions("-DGIT_COMMIT_HASH=${GIT_COMMIT_HASH}")
add_definitions("-DGIT_BRANCH=${GIT_BRANCH}")

configure_file (  
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Version.format"  
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/GVersion.hpp"  
  )  

###################################################################################################################################WINDOWS

if(WIN32)
	message ("This is a Win32 OS")

	if(${CMAKE_EXE_LINKER_FLAGS} MATCHES "/machine:X86")
		project(Gateware_i386)
		set(Architecture i386)

	elseif(${CMAKE_EXE_LINKER_FLAGS} MATCHES "/machine:x64")
		project(Gateware_amd64)
		set(Architecture amd64)
		
	endif()

	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../Binaries/Win32/Gateware_${Architecture})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../Libraries/Win32/Gateware_${Architecture})
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../Archive/Win32/Gateware_${Architecture})
	#set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../PDB/Win32/Gateware_${Architecture})

    include_directories(Interface)

    Set(HEADER_FILES "../DLL_Export_Symbols.h")

    link_directories(source)

    set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

endif(WIN32)

###################################################################################################################################LINUX

if(UNIX AND NOT APPLE)
	message ("This is a Linux OS")
    #Project(Gatewarelinux)

    if(EXISTS ${CMAKE_BINARY_DIR}/amd64Debug OR EXISTS ${CMAKE_BINARY_DIR}/amd64Release)
    message("This is an amd64 config")
    set(Architecture amd64)
        if(EXISTS ${CMAKE_BINARY_DIR}/amd64Debug)
        Project(Gateware_amd64_Debug)
        SET(BUILD_TYPE Debug)
        MESSAGE("Debug Configuration")
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64 -g" )
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -g")
        SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m64 -g")
        elseif(EXISTS ${CMAKE_BINARY_DIR}/amd64Release)
        Project(Gateware_amd64_Release)
        SET(BUILD_TYPE Release)
        MESSAGE("Release Configuration")
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64" )
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
        SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m64")
        endif()
    endif()

    if(EXISTS ${CMAKE_BINARY_DIR}/i386Debug OR EXISTS ${CMAKE_BINARY_DIR}/i386Release)
    message("This is an i386 config")
    set(Architecture i386)
        if(EXISTS ${CMAKE_BINARY_DIR}/i386Debug)
        Project(Gateware_i386_Debug)
        SET(BUILD_TYPE Debug)
        MESSAGE("Debug Configuration")
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -g")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32 -g")
        SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32 -g")
        elseif(EXISTS ${CMAKE_BINARY_DIR}/i386Release)
        Project(Gateware_i386_Release)
        SET(BUILD_TYPE Release)
        MESSAGE("Release Configuration")
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
        SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32")
        endif()
    endif()

	#Set(CMAKE_C_COMPILER /usr/bin/gcc)
	#Set(CMAKE_CXX_COMPILER /usr/bin/g++)
    	#Set(CMAKE_LINK_LIBRARY_FLAGS "-i" "[-m64]")

    include_directories(Interface)

    Set(HEADER_FILES ${PROJECT_SOURCE_DIR}/Source/DLL_Export_Symbols.h)

    link_directories(Source)

    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lX11")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -lX11 -lGL")

    	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../../Binaries/UNIX/${BUILD_TYPE}/Gateware_${Architecture})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../../Libraries/UNIX/${BUILD_TYPE}/Gateware_${Architecture})
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../../Archive/UNIX/${BUILD_TYPE}/Gateware_${Architecture})
	#set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../../PDB/UNIX/${BUILD_TYPE}/Gateware_${Architecture})

endif(UNIX AND NOT APPLE)

###################################################################################################################################APPLE

if(APPLE)
	message ("This is an Apple OS")
	
	Project(Gateware_Apple)
	
	#Set(CMAKE_C_COMPILER “/usr/bin/clang”)
	
	Set(CMAKE_C_FLAGS “${CMAKE_C_FLAGS}”)
	
	#Set(CMAKE_CXX_COMPILER “/usr/bin/clang++”)
	
	Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	
	Set(Architecture ${CMAKE_OSX_ARCHITECTURES})


	
 	
	include_directories(Interface /System/Library/Frameworks)

    	Set(HEADER_FILES ${PROJECT_SOURCE_DIR}/Source/DLL_Export_Symbols.h)

    	link_directories(${PROJECT_SOURCE_DIR}/Source)

	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../Archive/APPLE/${BUILD_TYPE}/Gateware_${Architecture})

	#For some reason, variables don't work for library building. Must find a work around.	
	
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../Libraries/APPLE/${BUILD_TYPE}/Gatewarex86_64)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../Binaries/APPLE/${BUILD_TYPE}/Gateware_${Architecture})	

endif(APPLE)

###################################################################################################################################DEFINITIONS

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

#For doxygen, need more research and intergration into the project
#add_custom_target(docs ALL DEPENDS Doxyfile)

add_subdirectory(Source)
add_subdirectory("Unit Tests")
