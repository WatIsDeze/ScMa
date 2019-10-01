cmake_minimum_required(VERSION 3.5)
project(SchizoMania_Shared)

add_library(SchizoMania_Shared_Client STATIC
    command.h
    crypto.cpp
    cube.h
    ents.h
    geom.cpp
    geom.h
    glemu.cpp
    glemu.h
    glexts.h
    iengine.h
    igame.h
    pch.cpp
    stream.cpp
    tessfont.c
    tools.cpp
    tools.h
    zip.cpp
)

add_subdirectory(entities)

# add_library(SchizoMania_Server STATIC
# )
target_include_directories(SchizoMania_Shared_Client 
	PUBLIC
		${CMAKE_SOURCE_DIR}
		${SDL2_INCLUDE_DIRS}
		${FREETYPE_INCLUDE_DIRS}
		${ZLIB_INCLUDE_DIRS}
		${OPENGL_INCLUDE_DIRS}
    PRIVATE
    	shared/
    	../engine/
        ../game/
        ../game/entities/
        entities/
)
target_link_libraries(SchizoMania_Shared_Client
	PUBLIC
		SchizoMania_Game_Client
		SchizoMania_Shared_Entities
        enet
        ${SDL2_LIBRARIES}
        ${FREETYPE_LIBRARIES}
        ${ZLIB_LIBRARIES}
        ${OPENGL_LIBRARIES}
)

# target_compile_definitions(SchizoMania_Shared_Server PUBLIC -DSTANDALONE)

# target_include_directories(SchizoMania_Shared_Server PUBLIC ${CMAKE_SOURCE_DIR})

