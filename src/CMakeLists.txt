# -*- mode: CMake; tab-width: 2; indent-tabs-mode: nil; -*-
cmake_minimum_required(VERSION 3.5)
project(SchizoMania)

# Build options.
option(SCHIZOMANIA_BUILD_CLIENT "Build the game client" ON)
option(SCHIZOMANIA_BUILD_SERVER "Build the game server" ON)

# Generate compile commands (compile_commands.json) for clang tooling etc.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add zlib.
find_package(ZLIB REQUIRED)

if(SCHIZOMANIA_BUILD_CLIENT)
  # Add OpenGL.
  find_package(OpenGL REQUIRED)

  # Platform specific libraries.
  if(UNIX AND NOT APPLE)
    set(PLATFORM_LIBRARIES rt)
  endif()
endif()

# Add third party libraries (e.g. built from source).
#add_subdirectory(third_party)

# Additional compiler flags.
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # Silence warnings from Clang.
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-exception-spec")
endif()

if(SCHIZOMANIA_BUILD_CLIENT)
  # Client executable.
  set(CLIENT_SOURCES
      # Engine code.
      shared/crypto.cpp
      shared/geom.cpp
      shared/glemu.cpp
      shared/stream.cpp
      shared/tools.cpp
      shared/zip.cpp
      engine/aa.cpp
      engine/bih.cpp
      engine/blend.cpp
      engine/client.cpp
      engine/command.cpp
      engine/console.cpp
      engine/dynlight.cpp
      engine/grass.cpp
      engine/light.cpp
      engine/main.cpp
      engine/material.cpp
      engine/menus.cpp
      engine/movie.cpp
      engine/normal.cpp
      engine/octa.cpp
      engine/octaedit.cpp
      engine/octarender.cpp
      engine/physics.cpp
      engine/pvs.cpp
      engine/rendergl.cpp
      engine/renderlights.cpp
      engine/rendermodel.cpp
      engine/renderparticles.cpp
      engine/rendersky.cpp
      engine/rendertext.cpp
      engine/renderva.cpp
      engine/server.cpp
      engine/serverbrowser.cpp
      engine/shader.cpp
      engine/sound.cpp
      engine/stain.cpp
      engine/texture.cpp
      engine/ui.cpp
      engine/water.cpp
      engine/world.cpp
      engine/worldio.cpp
      
      # Game code.
      game/ai.cpp
      game/client.cpp
      game/entities.cpp
      game/game.cpp
      #game/movable.cpp
      #game/movables.cpp
      game/render.cpp
      game/scoreboard.cpp
      game/server.cpp
      game/waypoint.cpp
      game/weapon.cpp
      
      # Entities.
      game/entities/baseentity.cpp
      game/entities/playerstart.cpp
    )
  set(CLIENT_INCLUDES
      ${CMAKE_CURRENT_SOURCE_DIR}
	  ${CMAKE_CURRENT_SOURCE_DIR}/engine
	  ${CMAKE_CURRENT_SOURCE_DIR}/shared
      )
  set(CLIENT_LIBRARIES
      enet
      SDL2
	  SDL2_mixer
	  SDL2_image
      ${OPENGL_LIBRARIES}
      ${ZLIB_LIBRARIES}
      ${PLATFORM_LIBRARIES}
      )
  add_executable(schizomania ${CLIENT_SOURCES})
  target_include_directories(schizomania PRIVATE ${CLIENT_INCLUDES} )
  target_link_libraries(schizomania ${CLIENT_LIBRARIES})
endif()

if(SCHIZOMANIA_BUILD_SERVER)
  # Server executable.
  set(SERVER_SOURCES
      shared/crypto.cpp
      shared/stream.cpp
      shared/tools.cpp
      engine/command.cpp
      engine/server.cpp
      engine/worldio.cpp
      game/entities.cpp
      game/server.cpp
      )
  set(SERVER_INCLUDES
      ${CMAKE_CURRENT_SOURCE_DIR}
      )
  set(SERVER_LIBRARIES
      enet
      ${ZLIB_LIBRARIES}
      )
  add_executable(schizomania_server ${SERVER_SOURCES})
  target_compile_definitions(schizomania_server PRIVATE -DSTANDALONE)
  target_include_directories(schizomania_server PRIVATE ${SERVER_INCLUDES})
  target_link_libraries(schizomania_server ${SERVER_LIBRARIES})

  # Master executable.
  set(MASTER_SOURCES
      shared/crypto.cpp
      shared/stream.cpp
      shared/tools.cpp
      engine/command.cpp
      engine/master.cpp
      )
  set(MASTER_INCLUDES
      ${CMAKE_CURRENT_SOURCE_DIR}
      )
  set(MASTER_LIBRARIES
      enet
      ${ZLIB_LIBRARIES}
      )
  add_executable(schizomania_master ${MASTER_SOURCES})
  target_compile_definitions(schizomania_master PRIVATE -DSTANDALONE)
  target_include_directories(schizomania_master PRIVATE ${MASTER_INCLUDES})
  target_link_libraries(schizomania_master ${MASTER_LIBRARIES})
endif()
