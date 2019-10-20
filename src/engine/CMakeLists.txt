cmake_minimum_required(VERSION 3.5)
project(SchizoMania_Engine)

add_library(SchizoMania_Engine_Client STATIC
    aa.cpp
    animmodel.h
    bih.cpp
    bih.h
    blend.cpp
    client.cpp
    command.cpp
    console.cpp
    dynlight.cpp
    engine.h
    explosion.h
    grass.cpp
    help.h
    help.cpp
    hitzone.h
    iqm.h
    lensflare.h
    light.cpp
    light.h
    lightning.h
    log.h
    log.cpp
    # main.cpp
    # master.cpp
    material.cpp
    md2.h
    md3.h
    md5.h
    menus.cpp
    model.h
    movie.cpp
    mpr.h
    normal.cpp
    obj.h
    octa.cpp
    octa.h
    octaedit.cpp
    octarender.cpp
    pch.cpp
    physics.cpp
    pvs.cpp
    ragdoll.h
    rendergl.cpp
    renderlights.cpp
    rendermodel.cpp
    renderparticles.cpp
    rendersky.cpp
    rendertext.cpp
    renderva.cpp
    scriptexport.h
    scriptexport.cpp
    server.cpp
    serverbrowser.cpp
    shader.cpp
    skelmodel.h
    smd.h
    sound.cpp
    stain.cpp
    textedit.h
    texture.cpp
    texture.h
    ui.cpp
    vertmodel.h
    water.cpp
    world.cpp
    world.h
    worldio.cpp
)

# add_library(SchizoMania_Engine_Server STATIC
#     command.cpp
#     irc.cpp
#     master.cpp
#     server.cpp
# )

if (UNIX AND NOT APPLE)
    list(APPEND OS_LIBS "rt")
endif()

target_include_directories(SchizoMania_Engine_Client
    PUBLIC
        ${CMAKE_SOURCE_DIR}
    PRIVATE
        ../shared
        ${SDL2_MIXER_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        # ${PNG_INCLUDE_DIRS}
        # ${JPEG_INCLUDE_DIRS}
        # ${TIFF_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIRS}
)

target_link_libraries(SchizoMania_Engine_Client
    PUBLIC
        SchizoMania_Shared_Client
        ${OS_LIBS}
    PRIVATE
        SchizoMania_Binding
        ${SDL2_MIXER_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${PNG_LIBRARIES}
        ${JPEG_LIBRARIES}
        ${TIFF_LIBRARIES}
        ${WEBP_LIBRARIES}
        ${OPENGL_LIBRARIES}
)


# target_compile_definitions(SchizoMania_Engine_Server PUBLIC -DSTANDALONE)

# target_include_directories(SchizoMania_Engine_Server PUBLIC ${CMAKE_SOURCE_DIR})

