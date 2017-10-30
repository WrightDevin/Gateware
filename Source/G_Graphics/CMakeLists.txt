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

set_property(TARGET GOpenGLESSurface PROPERTY FOLDER "Static libraries")

set_property(TARGET GOpenGLESSurface_DLL PROPERTY FOLDER "Dynamic libraries")


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

target_link_libraries(GOpenGLESSurface "${OPENGL_LIBRARY}")
target_link_libraries(GOpenGLESSurface_DLL "${OPENGL_LIBRARY}")

target_link_libraries(GOpenGLESSurface "${OPENGLX_LIBRARY}")
target_link_libraries(GOpenGLESSurface_DLL "${OPENGLX_LIBRARY}")

endif(UNIX AND NOT APPLE)


if(APPLE)



#Set(GUI_TYPE MACOSX_BUNDLE)



set(COCOA_LIBRARY Cocoa)
set(OPENGL_LIBRARY OpenGL)


target_link_libraries(GOpenGLESSurface "-framework ${COCOA_LIBRARY}")
target_link_libraries(GOpenGLESSurface "-framework ${OPENGL_LIBRARY}")


target_link_libraries(GOpenGLESSurface_DLL "-framework Cocoa")
target_link_libraries(GOpenGLESSurface_DLL "-framework OpenGL")


endif(APPLE)


target_compile_definitions(GOpenGLESSurface_DLL PUBLIC GATEWARE_EXPORT_BUILD)


