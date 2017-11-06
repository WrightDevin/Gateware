project(LibraryProject)


#########################################################################

if(APPLE)

#Set(GUI_TYPE MACOSX_BUNDLE)

set(COCOA_LIBRARY Cocoa)
set(OPENGL_LIBRARY OpenGL)

message(“Adding .mm files”)

add_library(GOpenGLSurface GOpenGLSurface.mm)
add_library(GOpenGLSurface_DLL SHARED GOpenGLSurface.mm)


target_link_libraries(GOpenGLSurface "-framework ${COCOA_LIBRARY}")
target_link_libraries(GOpenGLSurface "-framework ${OPENGL_LIBRARY}")


target_link_libraries(GOpenGLSurface_DLL "-framework Cocoa")
target_link_libraries(GOpenGLSurface_DLL "-framework OpenGL")

#########################################################################

else(APPLE)

add_library (GOpenGLSurface GOpenGLSurface.cpp ${HEADER_FILES})

add_library (GOpenGLSurface_DLL SHARED GOpenGLSurface.cpp ${HEADER_FILES})

endif(APPLE)

#########################################################################


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

#########################################################################

if(UNIX AND NOT APPLE)

#set(OPENGL_LIBRARY libgl.so)
#if(NOT OPENGL_LIBRARY)
#message("libgl.so not found...")
#endif(NOT OPENGL_LIBRARY)

#message("libgl.so WAS FOUND!")

#set(OPENGLX_LIBRARY libglx.so)
#if(NOT OPENGLX_LIBRARY)
#message("libglx.so not found...")
#endif(NOT OPENGLX_LIBRARY)

#message("libglx.so WAS FOUND!")

#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -lGL")

target_link_libraries(GOpenGLSurface "${OPENGL_LIBRARY}")
target_link_libraries(GOpenGLSurface_DLL "${OPENGL_LIBRARY}")

target_link_libraries(GOpenGLSurface "${OPENGLX_LIBRARY}")
target_link_libraries(GOpenGLSurface_DLL "${OPENGLX_LIBRARY}")

endif(UNIX AND NOT APPLE)

#########################################################################-ALL		
#########################################################################-PLATFORMS

set_property(TARGET GOpenGLSurface PROPERTY FOLDER "Static libraries")

set_property(TARGET GOpenGLSurface_DLL PROPERTY FOLDER "Dynamic libraries")

target_compile_definitions(GOpenGLSurface_DLL PUBLIC GATEWARE_EXPORT_BUILD)

#########################################################################
#########################################################################


