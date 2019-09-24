cmake_minimum_required(VERSION 3.5)
project(SchizoMania_Shared)

add_library(SchizoMania_Shared_Entities STATIC
	animinfo.h
	dynent.h
	dynent.cpp
	physent.h
	physent.cpp
	baseentity.h
	baseentity.cpp
	attributes.h
	attributes.cpp
)

# add_library(SchizoMania_Server STATIC
# )

target_include_directories(SchizoMania_Shared_Entities PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${SDL2_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
	
    PRIVATE
    	../../shared/
        ../../game/
        ../../engine/
)
target_link_libraries(SchizoMania_Shared_Entities
    PUBLIC
        enet
        ${SDL2_LIBRARIES}
        ${FREETYPE_LIBRARIES}
        ${ZLIB_LIBRARIES}
        ${OPENGL_LIBRARIES}
)

# target_compile_definitions(SchizoMania_Shared_Server PUBLIC -DSTANDALONE)

# target_include_directories(SchizoMania_Shared_Server PUBLIC ${CMAKE_SOURCE_DIR})

