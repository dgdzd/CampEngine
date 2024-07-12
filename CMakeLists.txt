cmake_minimum_required(VERSION 3.8)
project(CampEngine++)

set(CMAKE_C_STANDARD "17")
set(CMAKE_CXX_STANDARD "20")
set(CMAKE_CXX_STANDARD_REQUIRED On)

file(GLOB LIBS_DYLIB "dependencies/library/*.dylib")
file(GLOB LIBS_A "/opt/homebrew/Cellar/freetype/2.13.2/lib/libfreetype.a")

find_package(Freetype REQUIRED)

message("Using compiler for .cpp files: ${CC}")

add_executable(CampEngine++
        src/utils/stb.cpp
        src/physics/force.cpp
        src/utils/gui_helper.cpp
        src/physics/collisions_handler.cpp
        src/graphics/render/entity.cpp
        src/graphics/core/widget.cpp
        src/graphics/render/decoration.cpp
        src/graphics/level.cpp
        src/physics/rigid_body.cpp
        src/game/events/event_handler.cpp
        src/graphics/screen.cpp
        src/utils/logger.cpp
        main.cpp
        src/utils/conversions.cpp
        src/graphics/shader.cpp
        src/graphics/core/renderable.cpp
        src/physics/collidable.cpp
        src/graphics/core/text/text_renderer.cpp
        src/physics/aabb.cpp
        src/physics/physics_environment.cpp
        src/graphics/post_processor.cpp
        src/graphics/render/particle.cpp
        src/game/constants.cpp
        src/graphics/camera.cpp
        src/physics/maths.cpp
        src/game/input/input.cpp
        src/utils/filereader.cpp
        src/graphics/core/text/character.cpp
        src/graphics/texture.cpp
        src/graphics/render/tile.cpp
        dependencies/src/glad/glad.c
        src/game/game.cpp
        src/utils/resource_manager.cpp
        src/physics/collision_manifold.cpp
        src/graphics/render/sprite.cpp



)

target_include_directories(CampEngine++ PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(CampEngine++ PUBLIC ${CMAKE_SOURCE_DIR}/dependencies/include)
target_include_directories(CampEngine++ PUBLIC ${FREETYPE_INCLUDE_DIRS})

target_link_libraries(CampEngine++ ${LIBS_DYLIB})
target_link_libraries(CampEngine++ ${FREETYPE_LIBRARIES})