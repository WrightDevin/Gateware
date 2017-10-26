#add_subdirectory(G_System)
#add_subdirectory(G_Audio)
#add_subdirectory(G_Graphics)
message(“Unit Test Generation”)

if(UNIX AND NOT APPLE)

# https://stackoverflow.com/questions/39863835/cmake-link-xlib-directories-c

find_package(X11 REQUIRED)
find_package(Threads REQUIRED)

if(NOT CMAKE_THREAD_LIBS_INIT)

message(ERROR "Could not find thread libraries")

endif(NOT CMAKE_THREAD_LIBS_INIT)

if(X11_FOUND)
message("X11 was found, attempting to link.")

link_libraries(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIR})

endif(X11_FOUND)

endif(UNIX AND NOT APPLE)


if(NOT APPLE)
set(UnitTestDependecies
Common.cpp Common.h
G_System/GBufferedInputTests.cpp
G_System/GFileTest.cpp
G_System/GInputTests.cpp
G_System/GLogTest.cpp
#G_System/GWindowTests.cpp
G_System/GBufferedInputTestListener.cpp
G_System/GBufferedInputTestListener.h
G_System/GWindowTestListener.cpp

G_Graphics/GOpenGLESSurfaceTest.cpp
G_Audio/GAudioTests.cpp
add_executable(UnitTests UnitTestMain.cpp CATCH.hpp ${UnitTestDependecies})

target_link_libraries(UnitTests GBufferedInput GFile GInput GLog GWindow GOpenGLESSurface GAudio ${CMAKE_THREAD_LIBS_INIT})


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


target_link_libraries(UnitTests GBufferedInput GFile GInput GLog GWindow GAudio ${CMAKE_THREAD_LIBS_INIT})

endif()

if(WIN32)
set(UnitTestDependecies G_Graphics/GDirectX11SurfaceTest.cpp)
target_link_libraries(UnitTests GDirectX11Surface ${CMAKE_THREAD_LIBS_INIT})
endif(WIN32)

#target_sources(UnitTests PUBLIC ${UnitTestDependecies})
