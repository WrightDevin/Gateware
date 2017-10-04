project(LibraryProject)

if(WIN32)

add_library (GDirectX11Surface GDirectX11Surface.cpp ${HEADER_FILES})
add_library (GDirectX11Surface_DLL SHARED GDirectX11Surface.cpp ${HEADER_FILES})

set_property(TARGET 
GDirectX11Surface
PROPERTY FOLDER "Static libraries")

set_property(TARGET 
GDirectX11Surface_DLL
PROPERTY FOLDER "Dynamic libraries")

target_compile_definitions(GDirectX11Surface_DLL PUBLIC GATEWARE_EXPORT_BUILD)

endif(WIN32)

add_library (GOpenGLESSurface GOpenGLESSurface.cpp ${HEADER_FILES})
add_library (GOpenGLESSurface_DLL SHARED GOpenGLESSurface.cpp ${HEADER_FILES})

if(APPLE)

#Set(GUI_TYPE MACOSX_BUNDLE)

FIND_LIBRARY(COCOA_LIBRARY Cocoa)

target_link_libraries(GOpenGLESSurface “-framework ${COCOA_LIBRARY}”)

target_link_libraries(GOpenGLESSurface_DLL "-framework cocoa")


else(APPLE)


#message(“Adding .cpp files”)

#add_library (GDirectX11Surface GDirectX11Surface.cpp ${HEADER_FILES})

#add_library (GOpenGLESSurface GOpenGLESSurface.cpp ${HEADER_FILES})


endif()

set_property(TARGET 
GOpenGLESSurface
PROPERTY FOLDER "Static libraries")

set_property(TARGET 
GOpenGLESSurface_DLL
PROPERTY FOLDER "Dynamic libraries")

target_compile_definitions(GOpenGLESSurface_DLL PUBLIC GATEWARE_EXPORT_BUILD)
