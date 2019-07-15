cmake_minimum_required(VERSION 3.5)
project(SchizoMania_Game)

add_library(SchizoMania_Game_Client STATIC
    entities.cpp
    game.cpp
    game.h
    render.cpp

    entities/baseentity.cpp
    entities/dynamiclight.cpp
    entities/dynamiclight.h
    entities/playerstart.cpp
    entities/playerstart.h
)

# add_library(SchizoMania_Game_Server STATIC
# )

target_include_directories(SchizoMania_Game_Client
    PUBLIC 
        ${CMAKE_SOURCE_DIR}
    PRIVATE
        ../shared
        entities/
)

#set(OS_LIBS "")
#if (UNIX)
#    set(OS_LIBS "-lrt")
#endif()

target_link_libraries(SchizoMania_Game_Client
    PUBLIC
        SchizoMania_Shared_Client
        #${OS_LIBS}
)
# target_compile_definitions(SchizoMania_Game_Server PUBLIC -DSTANDALONE)

# target_include_directories(SchizoMania_Game_Server PUBLIC ${CMAKE_SOURCE_DIR})

