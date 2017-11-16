#add_subdirectory(G_System)
#add_subdirectory(G_Math)
#add_subdirectory(G_Audio)
#add_subdirectory(G_Graphics)


message(“Unit Test Generation”)

if(WIN32)

set(UnitTestDependecies

Common.cpp Common.h

G_System/GBufferedInputTests.cpp

G_System/GFileTest.cpp

G_System/GInputTests.cpp

G_System/GLogTest.cpp

G_System/GWindowTests.cpp

G_System/GBufferedInputTestListener.cpp

G_System/GBufferedInputTestListener.h

G_System/GWindowTestListener.cpp

G_System/GWindowTestListener.h

G_Graphics/GOpenGLSurfaceTest.cpp

G_Graphics/GDirectX11SurfaceTest.cpp

G_Math/GMatrixTest.cpp

G_Math/GVectorTest.cpp

G_Math/GQuaternionTest.cpp

G_Audio/GAudioTests.cpp


 )


add_executable(UnitTests UnitTestMain.cpp CATCH.hpp ${UnitTestDependecies})

target_link_libraries(UnitTests GBufferedInput GFile GInput GLog GWindow GDirectX11Surface GOpenGLSurface GAudio GMatrix GVector GQuaternion ${CMAKE_THREAD_LIBS_INIT})

endif(WIN32)



if(UNIX AND NOT APPLE)

# https://stackoverflow.com/questions/39863835/cmake-link-xlib-directories-c

find_package(X11 REQUIRED)

find_package(OpenGL REQUIRED)

find_package(Threads REQUIRED)



if(NOT CMAKE_THREAD_LIBS_INIT)



message(ERROR "Could not find thread libraries")



endif(NOT CMAKE_THREAD_LIBS_INIT)



if(X11_FOUND)

message("X11 was found, attempting to link.")

link_libraries(${X11_LIBRARIES})

link_libraries(${OPENGL_LIBRARIES})

include_directories(${X11_INCLUDE_DIR})

include_directories(${OPENGL_INCLUDE_DIRS})

endif(X11_FOUND)

#endif(UNIX AND NOT APPLE)




#if(NOT APPLE)

set(UnitTestDependecies

Common.cpp Common.h

G_System/GBufferedInputTests.cpp

G_System/GFileTest.cpp

G_System/GInputTests.cpp

G_System/GLogTest.cpp

G_System/GWindowTests.cpp

G_System/GBufferedInputTestListener.cpp

G_System/GBufferedInputTestListener.h

G_System/GWindowTestListener.cpp
G_System/GWindowTestListener.h

G_Graphics/GOpenGLSurfaceTest.cpp

G_Math/GMatrixTest.cpp

G_Math/GVectorTest.cpp

G_Math/GQuaternionTest.cpp

G_Audio/GAudioTests.cpp

 )
add_executable(UnitTests UnitTestMain.cpp CATCH.hpp ${UnitTestDependecies})

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

target_link_libraries(UnitTests GBufferedInput GFile GInput GLog GWindow GOpenGLSurface GAudio GMatrix GVector GQuaternion ${CMAKE_THREAD_LIBS_INIT})

endif()

target_link_libraries(UnitTests GBufferedInput GFile GInput GLog GWindow GOpenGLSurface GAudio GMatrix GVector GQuaternion ${CMAKE_THREAD_LIBS_INIT})



endif(APPLE)



#target_sources(UnitTests PUBLIC ${UnitTestDependecies})



message(“Unit Test Generation”)

if(WIN32)

set(UnitTestDependecies

Common.cpp Common.h

G_System/GBufferedInputTests.cpp

G_System/GFileTest.cpp

G_System/GInputTests.cpp

G_System/GLogTest.cpp

G_System/GWindowTests.cpp

G_System/GBufferedInputTestListener.cpp

G_System/GBufferedInputTestListener.h

G_System/GWindowTestListener.cpp

G_System/GWindowTestListener.h

G_Graphics/GOpenGLSurfaceTest.cpp

G_Graphics/GDirectX11SurfaceTest.cpp

G_Math/GMatrixTest.cpp

G_Math/GVectorTest.cpp

G_Math/GQuaternionTest.cpp

G_Audio/GAudioTests.cpp


 )


add_executable(UnitTests UnitTestMain.cpp CATCH.hpp ${UnitTestDependecies})

target_link_libraries(UnitTests GBufferedInput GFile GInput GLog GWindow GDirectX11Surface GOpenGLSurface GAudio GMatrix GVector GQuaternion ${CMAKE_THREAD_LIBS_INIT})

endif(WIN32)



if(UNIX AND NOT APPLE)

# https://stackoverflow.com/questions/39863835/cmake-link-xlib-directories-c

find_package(X11 REQUIRED)

find_package(OpenGL REQUIRED)

find_package(Threads REQUIRED)



if(NOT CMAKE_THREAD_LIBS_INIT)



message(ERROR "Could not find thread libraries")



endif(NOT CMAKE_THREAD_LIBS_INIT)



if(X11_FOUND)

message("X11 was found, attempting to link.")

link_libraries(${X11_LIBRARIES})

link_libraries(${OPENGL_LIBRARIES})

include_directories(${X11_INCLUDE_DIR})

include_directories(${OPENGL_INCLUDE_DIRS})

endif(X11_FOUND)

#endif(UNIX AND NOT APPLE)




#if(NOT APPLE)

set(UnitTestDependecies

Common.cpp Common.h

G_System/GBufferedInputTests.cpp

G_System/GFileTest.cpp

G_System/GInputTests.cpp

G_System/GLogTest.cpp

G_System/GWindowTests.cpp

G_System/GBufferedInputTestListener.cpp

G_System/GBufferedInputTestListener.h

G_System/GWindowTestListener.cpp
G_System/GWindowTestListener.h

G_Graphics/GOpenGLSurfaceTest.cpp

G_Math/GMatrixTest.cpp

G_Math/GVectorTest.cpp

G_Math/GQuaternionTest.cpp

G_Audio/GAudioTests.cpp

 )

G_System/GWindowTestListener.h

G_Graphics/GOpenGLSurfaceTest.cpp

 )


add_executable(UnitTests UnitTestMain.cpp CATCH.hpp ${UnitTestDependecies})

target_link_libraries(UnitTests GBufferedInput GFile GInput GLog GWindow GOpenGLSurface ${CMAKE_THREAD_LIBS_INIT})

endif(UNIX AND NOT APPLE)


if(APPLE)

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

target_link_libraries(UnitTests GBufferedInput GFile GInput GLog GWindow GOpenGLSurface GAudio GMatrix GVector GQuaternion ${CMAKE_THREAD_LIBS_INIT})


target_link_libraries(UnitTests GBufferedInput GFile GInput GLog GWindow GOpenGLSurface GAudio GMatrix GVector GQuaternion ${CMAKE_THREAD_LIBS_INIT})



endif(APPLE)



#target_sources(UnitTests PUBLIC ${UnitTestDependecies})


