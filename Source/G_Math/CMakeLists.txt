project(LibraryProject)
#################################################################################LIBRARIES WITH NO .MM FILES
add_library (GMatrix GMatrix.cpp ${HEADER_FILES})
add_library (GQuaternion GQuaternion.cpp ${HEADER_FILES})
add_library (GVector GVector.cpp ${HEADER_FILES} )


add_library (GMatrix_DLL SHARED GMatrix.cpp ${HEADER_FILES} )
add_library (GQuaternion_DLL SHARED GQuaternion.cpp ${HEADER_FILES} ) 
add_library (GVector_DLL SHARED GVector.cpp ${HEADER_FILES} )

#################################################################################APPLE ONLY
if(APPLE)

#Set(GUI_TYPE MACOSX_BUNDLE)

#[=[
Unit Test Error notes #1:
This was previously using “Find_Library” to obtain the path to the cocoa framework, however, 
the variable is now set to “Cocoa” because the path it was giving was being set on the Unit Test by default
and was not being recognized as a valid path, this might have been due to a conflict with the Apple environment or
old vs new CMake versions (See the cmakelists for the unit tests for changes where the error was also occurring.)
#]=]

set(COCOA_LIBRARY Cocoa)


message(“Adding .mm files”)

add_library(GMatrix GMatrix.mm)

add_library(GVector GVector.mm)

add_library(GQuaternion GQuaternion.mm) 


add_library(GMatrix_DLL SHARED GMatrix.mm)

add_library(GVector_DLL SHARED GVector.mm)

add_library(GQuaternion_DLL SHARED GQuaternion.mm)



target_link_libraries(GMatrix "-framework ${COCOA_LIBRARY}")

target_link_libraries(GVector "-framework ${COCOA_LIBRARY}")

target_link_libraries(GQuaternion "-framework ${COCOA_LIBRARY}")


target_link_libraries(GMatrix_DLL "-framework cocoa")

target_link_libraries(GVector_DLL "-framework cocoa")

target_link_libraries(GQuaternion_DLL "-framework cocoa")


#################################################################################EVERYTHING ELSE
else(APPLE)

message(“Adding .cpp files”)

endif()
#################################################################################REMEBER TO ADD YOUR FILE NAMES INTO THE TWO FILE BLOCKS BELOW

set_property(TARGET 
GMatrix
GQuaternion
GVector
PROPERTY FOLDER "Static libraries")

set_property(TARGET 
GMatrix_DLL
GQuaternion_DLL
GVector_DLL
PROPERTY FOLDER "Dynamic libraries")

##################################################################################COMPILE DEFINITIONS FOR DYNAMIC LIBRARIES

target_compile_definitions(GMatrix_DLL PUBLIC GATEWARE_EXPORT_BUILD)
target_compile_definitions(GQuaternion_DLL PUBLIC GATEWARE_EXPORT_BUILD)
target_compile_definitions(GVector_DLL PUBLIC GATEWARE_EXPORT_BUILD)


##################################################################################--EXAMPLE ON HOW TO ADD FILE INTO PROJECT--
#--These are an example commands on how to add a new library into the project--

#add_library (GFile GFile.cpp ${HEADER_FILES} direntw.h GUtility.h)
#add_library (GFile_DLL SHARED GFile.cpp ${HEADER_FILES} direntw.h GUtility.h)

#--These go into the apple only section--
#target_link_libraries(GFile “-framework ${COCOA_LIBRARY}”)

#target_link_libraries(GFile “-framework ${COCOA_LIBRARY}”)


#target_compile_definitions(GFile_DLL PUBLIC GATEWARE_EXPORT_BUILD)
