#add_subdirectory(G_System)
#add_subdirectory(G_Audio)
message(“Unit Test Generation”)

if(UNIX)

# https://stackoverflow.com/questions/39863835/cmake-link-xlib-directories-c

find_package(X11 REQUIRED)

if(X11_FOUND)
message("X11 was found, attempting to link.")

link_libraries(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIR})

endif(X11_FOUND)

endif(UNIX)

if(NOT APPLE)
set(UnitTestDependecies
G_System/Common.cpp G_System/Common.h
G_System/GBufferedInputTests.cpp
G_System/GFileTest.cpp
G_System/GInputTests.cpp
G_System/GLogTest.cpp
G_System/GWindowTests.cpp
G_System/GBufferedInputTestListener.cpp
G_System/GBufferedInputTestListener.h
G_System/GWindowTestListener.cpp
G_System/GWindowTestListener.h
 )
add_executable(UnitTests UnitTestMain.cpp CATCH.hpp ${UnitTestDependecies})
target_link_libraries(UnitTests GBufferedInput GFile GInput GLog GWindow  ${CMAKE_THREAD_LIBS_INIT})

elseif(APPLE)
#Find_library(COCOA_LIB cocoa)

#[=[
Unit Test Error notes #2:
There was an issue where the cocoa framework was linked by default when
any of the libraries were linked (see target_link_libraries below), due
to this, Find_library was commented out (above), and the variable was
taken out from the target_link_libraries call to avoid duplication.

Error Notes #1 are within G_System’s cmakelists, where the Cocoa
framework is originally linked to these libraries.
#]=]

add_executable(UnitTests G_System/GTests.mm CATCH.hpp)

target_sources(UnitTests INTERFACE UnitTests.cpp)

target_link_libraries(UnitTests GBufferedInput GFile GInput GLog GWindow ${CMAKE_THREAD_LIBS_INIT})

endif()

#target_sources(UnitTests PUBLIC ${UnitTestDependecies})
