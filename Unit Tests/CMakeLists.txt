#add_subdirectory(G_System)

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
G_System/GWindowTestListener.h)
add_executable(UnitTests UnitTestMain.cpp CATCH.hpp ${UnitTestDependecies})


elseif(APPLE)

message(“Unit Test Generation”)

add_executable(UnitTests G_System/GTests.mm CATCH.hpp)

target_sources(UnitTests INTERFACE UnitTests.cpp)


endif()

target_link_libraries(UnitTests 
GBufferedInput GFile GInput GLog GWindow ${CMAKE_THREAD_LIBS_INIT} "-framework cocoa")
#target_sources(UnitTests PUBLIC ${UnitTestDependecies})
