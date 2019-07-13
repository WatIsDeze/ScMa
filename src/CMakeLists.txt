cmake_minimum_required(VERSION 3.5)
project(SchizoMania)
set (CMAKE_CXX_STANDARD 11)

message("CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")
set(CMAKE_VERBOSE_MAKEFILE ON)

if (APPLE)
  SET(CMAKE_FIND_LIBRARY_SUFFIXES ".dylib")
  list(REMOVE_ITEM CMAKE_FIND_LIBRARY_SUFFIXES ".a")
  list(INSERT      CMAKE_FIND_LIBRARY_SUFFIXES 0 ".dylib" )
endif()

#Libs
find_package(ZLIB REQUIRED)
message(DEBUG "Found ZLIB? ${ZLIB_FOUND} ${ZLIB_INCLUDE_DIRS} ${ZLIB_LIBRARY} ${ZLIB_LIBRARIES}")

find_package(PNG REQUIRED)
message(DEBUG "Found PNG? ${PNG_FOUND} ${PNG_INCLUDE_DIRS} ${PNG_LIBRARY} ${PNG_LIBRARIES}")

find_package(JPEG REQUIRED)
message(DEBUG "Found JPEG? ${JPEG_FOUND} ${JPEG_INCLUDE_DIRS} ${JPEG_LIBRARY} ${JPEG_LIBRARIES}")

find_package(TIFF REQUIRED)
message(DEBUG "Found TIFF? ${TIFF_FOUND} ${TIFF_INCLUDE_DIRS} ${TIFF_LIBRARY} ${TIFF_LIBRARIES}")

find_package(WEBP REQUIRED)
message(DEBUG "Found WEBP? ${WEBP_FOUND} ${WEBP_INCLUDE_DIRS} ${WEBP_LIBRARY} ${WEBP_LIBRARIES}")

find_package(Freetype REQUIRED)
message(DEBUG "Found FREETYPE? ${FREETYPE_FOUND} ${FREETYPE_INCLUDE_DIRS} ${FREETYPE_LIBRARY} ${FREETYPE_LIBRARIES}")

if (LINUX)
    set(SDL2_INCLUDE_DIR "/usr/include/SDL2")
endif()
find_package(SDL2 REQUIRED)
message(DEBUG "Found SDL2? ${SDL2_FOUND} ${SDL2_INCLUDE_DIRS} ${SDL2_LIBRARY} ${SDL2_LIBRARIES}")

find_package(SDL2_mixer REQUIRED)
message(DEBUG "Found SDL2_MIXER? ${SDL2_MIXER_FOUND} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_MIXER_LIBRARY} ${SDL2_MIXER_LIBRARIES}")

find_package(SDL2_image REQUIRED)
message(DEBUG "Found SDL2_IMAGE? ${SDL2_IMAGE_FOUND} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_IMAGE_LIBRARY} ${SDL2_IMAGE_LIBRARIES}")

find_package(OpenGL REQUIRED)
message(DEBUG "Found OPENGL? ${OPENGL_FOUND} ${OPENGL_INCLUDE_DIRS} ${OPENGL_LIBRARY} ${OPENGL_LIBRARIES}")

#find_package(ModPlug REQUIRED)
#message(DEBUG "Found MODPLUG? ${MODPLUG_FOUND} ${MODPLUG_INCLUDE_DIRS} ${MODPLUG_LIBRARY} ${MODPLUG_LIBRARIES}")

if (APPLE)
    find_library(COREAUDIO CoreAudio REQUIRED)
    message(DEBUG "Found COREAUDIO? ${COREAUDIO} ${COREAUDIO_INCLUDE_DIRS} ${COREAUDIO_LIBRARY} ${COREAUDIO_LIBRARIES}")

    find_library(AVFOUNDATION AVFoundation REQUIRED)
    message(DEBUG "Found AVFOUNDATION? ${AVFOUNDATION} ${AVFOUNDATION_INCLUDE_DIRS} ${AVFOUNDATION_LIBRARY} ${AVFOUNDATION_LIBRARIES}")

    find_library(COCOA Cocoa REQUIRED)
    message(DEBUG "Found COCOA? ${COCOA} ${COCOA_INCLUDE_DIRS} ${COCOA_LIBRARY} ${COCOA_LIBRARIES}")

    find_library(COREFOUNDATION CoreFoundation REQUIRED)
    message(DEBUG "Found COREFOUNDATION? ${COREFOUNDATION} ${COREFOUNDATION_INCLUDE_DIRS} ${COREFOUNDATION_LIBRARY} ${COREFOUNDATION_LIBRARIES}")

    find_library(APPLICATIONSERVICES ApplicationServices REQUIRED)
    message(DEBUG "Found APPLICATIONSERVICES? ${APPLICATIONSERVICES} ${APPLICATIONSERVICES_INCLUDE_DIRS} ${APPLICATIONSERVICES_LIBRARY} ${APPLICATIONSERVICES_LIBRARIES}")

    find_library(FOUNDATION Foundation REQUIRED)
    message(DEBUG "Found FOUNDATION? ${FOUNDATION} ${FOUNDATION_INCLUDE_DIRS} ${FOUNDATION_LIBRARY} ${FOUNDATION_LIBRARIES}")

    find_library(COREFOUNDATION CoreFoundation REQUIRED)
    message(DEBUG "Found COREFOUNDATION? ${COREFOUNDATION} ${COREFOUNDATION_INCLUDE_DIRS} ${COREFOUNDATION_LIBRARY} ${COREFOUNDATION_LIBRARIES}")

    find_library(AUDIOTOOLBOX AudioToolbox REQUIRED)
    message(DEBUG "Found AUDIOTOOLBOX? ${AUDIOTOOLBOX} ${AUDIOTOOLBOX_INCLUDE_DIRS} ${AUDIOTOOLBOX_LIBRARY} ${AUDIOTOOLBOX_LIBRARIES}")

    find_library(BULLSHITLIB BullShitLib REQUIRED)
    message(DEBUG "Found BULLSHITLIB? ${BULLSHITLIB} ${BULLSHITLIB_INCLUDE_DIRS} ${BULLSHITLIB_LIBRARY} ${BULLSHITLIB_LIBRARIES}")    

    # MARK_AS_ADVANCED (
    # )

endif()

#defines, project wide
add_definitions("-DGL_SILENCE_DEPRECATION")

#The engine, server and shared
add_subdirectory(enet)
add_subdirectory(shared)
add_subdirectory(game)
add_subdirectory(engine)

if (APPLE)
    add_executable(SchizoMania_Client MACOSX_BUNDLE
        engine/main.cpp

        xcode/English.lproj/InfoPlist.strings
        xcode/English.lproj/MainMenu.nib
        xcode/Launcher.h
        xcode/Launcher.m
        xcode/Maps.icns
        xcode/main.m
        xcode/tesseract.icns
        xcode/tesseract.plist    
    )
else()
    add_executable(SchizoMania_Client engine/main.cpp)
endif()

target_include_directories(SchizoMania_Client
    PRIVATE
        shared
        game
        engine
)

if (APPLE)
    target_link_libraries(SchizoMania_Client
        SchizoMania_Shared_Client
        SchizoMania_Game_Client
        SchizoMania_Engine_Client
        # ${MODPLUG_LIBRARIES}

        ${COCOA}
        ${COREFOUNDATION}
        ${AUDIOTOOLBOX}
        ${COREAUDIO}
        # ${AVFOUNDATION}
        # ${APLICATIONSERVICES}
        # ${FOUNDATION}
        # ${COREFOUNDATION}
    )
else()
target_link_libraries(SchizoMania_Client
    SchizoMania_Shared_Client
    SchizoMania_Game_Client
    SchizoMania_Engine_Client
)
endif()

