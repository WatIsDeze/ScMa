#CMake Configuration for Tesseract "The Right Way (tm)"
cmake_minimum_required(VERSION 3.5)
project(SchizoMania)

# Build options.
option(SCHIZOMANIA_BUILD_CLIENT "Build the game client" ON)
option(SCHIZOMANIA_BUILD_SERVER "Build the game server" OFF)

# Generate compile commands (compile_commands.json) for clang tooling etc.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

#Module helpers
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")
set(CMAKE_VERBOSE_MAKEFILE ON)

#For OSX, find the Shared libraries and ignore the static ones
if (APPLE)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".dylib")
    list(REMOVE_ITEM CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    list(INSERT CMAKE_FIND_LIBRARY_SUFFIXES 0 ".dylib" )

    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_LANGUAGE_STANDARD "c++14")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++14")
endif()

#Libraries
find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)
find_package(JPEG REQUIRED)
find_package(TIFF REQUIRED)
find_package(WEBP REQUIRED)
find_package(Freetype REQUIRED)
#For Linux, prime the SDL2 finder by setting the include dir
if (UNIX AND NOT APPLE)
    set(SDL2_INCLUDE_DIR "/usr/include/SDL2")
endif()
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(OpenGL REQUIRED)
#find_package(ModPlug REQUIRED)
#message(DEBUG "Found MODPLUG? ${MODPLUG_FOUND} ${MODPLUG_INCLUDE_DIRS} ${MODPLUG_LIBRARY} ${MODPLUG_LIBRARIES}")

if (APPLE)
    find_library(COREAUDIO CoreAudio REQUIRED)
    find_library(AVFOUNDATION AVFoundation REQUIRED)
    find_library(COCOA Cocoa REQUIRED)
    find_library(COREFOUNDATION CoreFoundation REQUIRED)
    find_library(APPLICATIONSERVICES ApplicationServices REQUIRED)
    find_library(FOUNDATION Foundation REQUIRED)
    find_library(COREFOUNDATION CoreFoundation REQUIRED)
    find_library(AUDIOTOOLBOX AudioToolbox REQUIRED)
    find_library(BULLSHITLIB BullShitLib REQUIRED)

    #Normally, you would mark the OSX Frameworks as "Advanced", no idea what it does, nor did it make any change
    # MARK_AS_ADVANCED (
    # )
endif()

#defines, project wide
#Silence OpenGL deprecations .. yes Apple, you like Metal and you can't shutup about it .. :rolleyes:
add_definitions("-DGL_SILENCE_DEPRECATION")
include_directories(
    ext/json-develop/single_include
)

#The engine, server and shared sub projects
add_subdirectory(enet)
add_subdirectory(shared)
add_subdirectory(game)
add_subdirectory(engine)

#Everything ready, now define the executables
if (APPLE)
    add_executable(SchizoMania_Client MACOSX_BUNDLE
        engine/main.cpp

        xcode/English.lproj/InfoPlist.strings
        xcode/English.lproj/MainMenu.nib
        xcode/English.lproj/MainMenu.nib/designable.nib
        xcode/English.lproj/MainMenu.nib/keyedobjects.nib
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

#Link the libraries
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
        SchizoMania_Shared_Entities
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
        SchizoMania_Shared_Entities
        SchizoMania_Engine_Client
        SchizoMania_Game_Client
    )
endif()

#Apple specific stuff
if (APPLE)
    set_property(TARGET SchizoMania_Client PROPERTY MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_LIST_DIR}/xcode/tesseract.plist.in)
    set_target_properties(SchizoMania_Client PROPERTIES RESOURCE "${CMAKE_CURRENT_LIST_DIR}/xcode/English.lproj/MainMenu.nib")
    target_compile_features(SchizoMania_Client PUBLIC cxx_std_11)

    set_source_files_properties(
        ${CMAKE_CURRENT_LIST_DIR}/xcode/English.lproj/MainMenu.nib/designable.nib
        PROPERTIES
        MACOSX_PACKAGE_LOCATION Resources/MainMenu.nib
    )

    set_source_files_properties(
        ${CMAKE_CURRENT_LIST_DIR}/xcode/English.lproj/MainMenu.nib/keyedobjects.nib
        PROPERTIES
        MACOSX_PACKAGE_LOCATION Resources/MainMenu.nib
    )
endif()
