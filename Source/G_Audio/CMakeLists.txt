project(LibraryProject)
if(WIN32)
message(“Adding .cpp files”)

add_library (GAudio GAudio.cpp ${HEADER_FILES})
add_library (GAudio_DLL SHARED GAudio.cpp ${HEADER_FILES} )
target_link_libraries(GAudio xaudio2)
target_link_libraries(GAudio_DLL xaudio2)

endif(WIN32)
if(UNIX AND NOT APPLE)
message(“Adding .cpp files”)

#FIND_FILE(MYLIB libpulse.so /usr/lib/x86_64-linux-gnu)
#IF(NOT MYLIB)
  #MESSAGE(SEND_ERROR "Cannot find library libpulse.so")
#ENDIF(NOT MYLIB)

#find_library(


set(PULSEAUDIO_LIBRARY libpulse.so)
IF(NOT PULSEAUDIO_LIBRARY)
  MESSAGE(SEND_ERROR "Cannot find library pulseaudio")
ENDIF(NOT PULSEAUDIO_LIBRARY)
message(“Found pulseaudio”)
set(PULSEAUDIO_MAINLOOP_LIBRARY libpulse-mainloop-glib.so)
IF(NOT PULSEAUDIO_MAINLOOP_LIBRARY)
  MESSAGE(SEND_ERROR "Cannot find library pulseaudio-mainloop")
ENDIF(NOT PULSEAUDIO_MAINLOOP_LIBRARY)
message(“Found mainloop”)

add_library (GAudio GAudio.cpp ${HEADER_FILES})
add_library (GAudio_DLL SHARED GAudio.cpp ${HEADER_FILES} )

target_link_libraries(GAudio "${PULSEAUDIO_LIBRARY}")
target_link_libraries(GAudio "${PULSEAUDIO_MAINLOOP_LIBRARY}")

target_link_libraries(GAudio_DLL "${PULSEAUDIO_LIBRARY}")
target_link_libraries(GAudio_DLL "${PULSEAUDIO_MAINLOOP_LIBRARY}")
endif(UNIX AND NOT APPLE)

if(APPLE)
#Set(GUI_TYPE MACOSX_BUNDLE)
set(COCOA_LIBRARY Cocoa)
set(AVFOUNDATION_LIBRARY AVFoundation)
set(AUDIOTOOLBOX_LIBRARY AVFoundation)
message(“Adding .mm files”)
add_library(GAudio GAudio.mm)

add_library(GAudio_DLL SHARED GAudio.mm)

target_link_libraries(GAudio "-framework ${COCOA_LIBRARY}")
target_link_libraries(GAudio "-framework ${AVFOUNDATION_LIBRARY}")
target_link_libraries(GAudio "-framework ${AUDIOTOOLBOX_LIBRARY}")
target_link_libraries(GAudio_DLL "-framework cocoa")
target_link_libraries(GAudio_DLL "-framework avfoundation")
target_link_libraries(GAudio_DLL "-framework audiotoolbox")
endif(APPLE)

set_property(TARGET 
GAudio
PROPERTY FOLDER "Static libraries")

set_property(TARGET 
GAudio_DLL 
PROPERTY FOLDER "Dynamic libraries")


target_compile_definitions(GAudio_DLL PUBLIC GATEWARE_EXPORT_BUILD)


