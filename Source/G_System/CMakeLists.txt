project(LibraryProject)
#################################################################################LIBRARIES WITH NO .MM FILES
add_library (GFile GFile.cpp ${HEADER_FILES} direntw.h GUtility.h)
add_library (GLog GLog.cpp ${HEADER_FILES})

add_library (GFile_DLL SHARED GFile.cpp ${HEADER_FILES} direntw.h GUtility.h)
add_library (GLog_DLL SHARED GLog.cpp GFile.cpp ${HEADER_FILES})



#################################################################################APPLE ONLY
if(APPLE)

#Set(GUI_TYPE MACOSX_BUNDLE)

set(COCOA_LIBRARY Cocoa)


message(“Adding .mm files”)

add_library(GBufferedInput GBufferedInput.mm)

add_library(GInput GInput.mm)

add_library(GWindow GWindow.mm) 


add_library(GBufferedInput_DLL SHARED GBufferedInput.mm)

add_library(GInput_DLL SHARED GInput.mm)

add_library(GWindow_DLL SHARED GWindow.mm)



target_link_libraries(GBufferedInput "-framework ${COCOA_LIBRARY}")

target_link_libraries(GInput "-framework ${COCOA_LIBRARY}")

target_link_libraries(GWindow "-framework ${COCOA_LIBRARY}")

target_link_libraries(GFile "-framework ${COCOA_LIBRARY}")

target_link_libraries(GLog "-framework ${COCOA_LIBRARY}")


target_link_libraries(GBufferedInput_DLL "-framework cocoa")

target_link_libraries(GInput_DLL "-framework cocoa")

target_link_libraries(GWindow_DLL "-framework cocoa")

target_link_libraries(GFile_DLL "-framework cocoa")

target_link_libraries(GLog_DLL "-framework cocoa")


#################################################################################EVERYTHING ELSE
else(APPLE)


message(“Adding .cpp files”)

add_library(GBufferedInput GBufferedInput.cpp ${HEADER_FILES})

add_library (GInput GInput.cpp ${HEADER_FILES})

add_library (GWindow GWindow.cpp ${HEADER_FILES})


add_library (GBufferedInput_DLL SHARED GBufferedInput.cpp ${HEADER_FILES})

add_library (GInput_DLL SHARED GInput.cpp ${HEADER_FILES})

add_library (GWindow_DLL SHARED GWindow.cpp ${HEADER_FILES})


endif()

#################################################################################REMEBER TO ADD YOUR FILE NAMES INTO THE TWO FILE BLOCKS BELOW

set_property(TARGET 
GBufferedInput 
GFile 
GInput 
GLog 
GWindow 
PROPERTY FOLDER "Static libraries")

set_property(TARGET 
GBufferedInput_DLL 
GFile_DLL 
GInput_DLL 
GLog_DLL 
GWindow_DLL 
PROPERTY FOLDER "Dynamic libraries")

##################################################################################COMPILE DEFINITIONS FOR DYNAMIC LIBRARIES

target_compile_definitions(GBufferedInput_DLL PUBLIC GATEWARE_EXPORT_BUILD)
target_compile_definitions(GFile_DLL PUBLIC GATEWARE_EXPORT_BUILD)
target_compile_definitions(GInput_DLL PUBLIC GATEWARE_EXPORT_BUILD)
target_compile_definitions(GLog_DLL PUBLIC GATEWARE_EXPORT_BUILD)
target_compile_definitions(GWindow_DLL PUBLIC GATEWARE_EXPORT_BUILD)


##################################################################################--EXAMPLE ON HOW TO ADD FILE INTO PROJECT--
#--These are an example commands on how to add a new library into the project--

#add_library (GFile GFile.cpp ${HEADER_FILES} direntw.h GUtility.h)
#add_library (GFile_DLL SHARED GFile.cpp ${HEADER_FILES} direntw.h GUtility.h)

#--These go into the apple only section--
#target_link_libraries(GFile “-framework ${COCOA_LIBRARY}”)

#target_link_libraries(GFile “-framework ${COCOA_LIBRARY}”)


#target_compile_definitions(GFile_DLL PUBLIC GATEWARE_EXPORT_BUILD)
