project(LibraryProject)
add_library (GDirectX11Surface GDirectX11Surface.cpp ${HEADER_FILES})
add_library (GOpenGLESSurface GOpenGLESSurface.cpp ${HEADER_FILES})

add_library (GDirectX11Surface_DLL SHARED GDirectX11Surface.cpp ${HEADER_FILES})
add_library (GOpenGLESSurface_DLL SHARED GOpenGLESSurface.cpp ${HEADER_FILES})



if(APPLE)

#Set(GUI_TYPE MACOSX_BUNDLE)

FIND_LIBRARY(COCOA_LIBRARY Cocoa)


message(“Adding .mm files”)

add_library(GDirectX11Surface GDirectX11Surface.mm)

add_library(GOpenGLESSurface GOpenGLESSurface.mm)


target_link_libraries(GDirectX11Surface “-framework ${COCOA_LIBRARY}”)

target_link_libraries(GOpenGLESSurface “-framework ${COCOA_LIBRARY}”)

target_link_libraries(GDirectX11Surface_DLL "-framework cocoa")

target_link_libraries(GOpenGLESSurface_DLL "-framework cocoa")


else(APPLE)


#message(“Adding .cpp files”)

#add_library (GDirectX11Surface GDirectX11Surface.cpp ${HEADER_FILES})

#add_library (GOpenGLESSurface GOpenGLESSurface.cpp ${HEADER_FILES})


endif()

set_property(TARGET 
GDirectX11Surface
GOpenGLESSurface
PROPERTY FOLDER "Static libraries")

set_property(TARGET 
GDirectX11Surface_DLL
GOpenGLESSurface_DLL
PROPERTY FOLDER "Dynamic libraries")

target_compile_definitions(GDirectX11Surface_DLL PUBLIC GATEWARE_EXPORT_BUILD)
target_compile_definitions(GOpenGLESSurface_DLL PUBLIC GATEWARE_EXPORT_BUILD)
