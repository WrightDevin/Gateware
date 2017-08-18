project(LibraryProject)

if(APPLE)
#Set(GUI_TYPE MACOSX_BUNDLE)
set(COCOA_LIBRARY Cocoa)

message(“Adding .mm files”)
add_library(GAudio GAudio.mm)

add_library(GAudio_DLL SHARED GAudio.mm)

target_link_libraries(GAudio "-framework ${COCOA_LIBRARY}")

target_link_libraries(GAudio_DLL "-framework cocoa")

else(APPLE)

message(“Adding .cpp files”)
add_library (GAudio GAudio.cpp ${HEADER_FILES})

add_library (GAudio_DLL SHARED GAudio.cpp ${HEADER_FILES})

endif()

set_property(TARGET 
GAudio
PROPERTY FOLDER "Static libraries")

set_property(TARGET 
GAudio_DLL 
PROPERTY FOLDER "Dynamic libraries")


target_compile_definitions(GAudio_DLL PUBLIC GATEWARE_EXPORT_BUILD)


