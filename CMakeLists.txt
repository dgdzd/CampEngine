cmake_minimum_required(VERSION 3.8)
project(CampEngine++ VERSION 0.0.1)

set(CMAKE_C_STANDARD "17")
set(CMAKE_CXX_STANDARD "20")
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${PROJECT_NAME})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${PROJECT_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/${PROJECT_NAME})

file(GLOB LIBS_DYLIB "dependencies/library/*.dylib")
file(GLOB LIBS_A "dependencies/library/*.a")

find_package(Freetype REQUIRED)

set(namespace "Campagne")
set(MAIN_FILE main.cpp)
set(SOURCE_FILES
        src/Utils/stb.cpp
        src/Physics/Force.cpp
        src/Utils/GuiHelper.cpp
        src/Physics/CollisionsHandler.cpp
        src/Graphics/Scene/Entity.cpp
        src/Graphics/Core/Widget.cpp
        src/Graphics/Scene/Decoration.cpp
        src/Graphics/Level.cpp
        src/Physics/RigidBody.cpp
        src/Game/Events/EventHandler.cpp
        src/Graphics/Screen.cpp
        src/Utils/logger.cpp
        src/Utils/conversions.cpp
        src/Graphics/Shader.cpp
        src/Graphics/Core/Renderable.cpp
        src/Physics/Collidable.cpp
        src/Graphics/Core/Text/TextRenderer.cpp
        src/Physics/AABB.cpp
        src/Physics/PhysicsEnvironment.cpp
        src/Graphics/PostProcessor.cpp
        src/Graphics/Scene/Particle.cpp
        src/Game/Constants.cpp
        src/Graphics/Camera.cpp
        src/Physics/Maths.cpp
        src/Game/Input/Input.cpp
        src/Utils/FileReader.cpp
        src/Graphics/Core/Text/Character.cpp
        src/Graphics/Texture.cpp
        src/Graphics/Scene/Tile.cpp
        src/Game/Game.cpp
        src/Utils/ResourceManager.cpp
        src/Physics/CollisionManifold.cpp
        src/Graphics/Scene/Sprite.cpp
        src/Graphics/Widgets/Button.cpp
        src/Graphics/Widgets/TexturedButton.cpp
        src/Graphics/Widgets/TextBox.cpp
        src/Graphics/Widgets/TextInput.cpp
        src/Graphics/Core/IWidget.cpp
        src/Graphics/Screens/TestScreen.cpp
        src/Graphics/Screens/DebugScreen.cpp
)
set(DEPENDENCIES_SOURCES dependencies/src/glad/glad.c)

file(GLOB PROJECT_HEADERS "include")
file(GLOB DEPENDENCIES_HEADERS "dependencies/include")

# 1. Executable

add_executable(CampEngine++ ${MAIN_FILE} ${SOURCE_FILES} ${DEPENDENCIES_SOURCES})

target_include_directories(CampEngine++ PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(CampEngine++ PUBLIC ${CMAKE_SOURCE_DIR}/dependencies/include)
target_include_directories(CampEngine++ PUBLIC ${FREETYPE_INCLUDE_DIRS})

target_link_libraries(CampEngine++ ${LIBS_DYLIB})
target_link_libraries(CampEngine++ ${FREETYPE_LIBRARIES})

# 2. Static library

add_library(lib_CampEngine++ STATIC ${SOURCE_FILES} ${DEPENDENCIES_SOURCES})

set_target_properties(lib_CampEngine++ PROPERTIES PREFIX "lib")
set_target_properties(lib_CampEngine++ PROPERTIES OUTPUT_NAME "CampEngine")
set_target_properties(lib_CampEngine++ PROPERTIES SUFFIX "-${PROJECT_VERSION}.a")

#target_include_directories(lib_CampEngine++ PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(lib_CampEngine++ PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/include)
target_include_directories(lib_CampEngine++ PRIVATE ${FREETYPE_INCLUDE_DIRS})
target_include_directories(lib_CampEngine++
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(lib_CampEngine++ ${LIBS_DYLIB})
target_link_libraries(lib_CampEngine++ ${FREETYPE_LIBRARIES})

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(
            STATUS
            "CMAKE_INSTALL_PREFIX is not set\n"
            "Default value: ${CMAKE_INSTALL_PREFIX}\n"
            "Will set it to ${CMAKE_SOURCE_DIR}/install"
    )
    set(CMAKE_INSTALL_PREFIX
            "${CMAKE_SOURCE_DIR}/install"
            CACHE PATH "Where the library will be installed to" FORCE
    )
else()
    message(
            STATUS
            "CMAKE_INSTALL_PREFIX was already set\n"
            "Current value: ${CMAKE_INSTALL_PREFIX}"
    )

endif()

# without it public headers won't get installed
set(public_headers
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Utils/GuiHelper.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Graphics/Scene/Entity.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Graphics/Core/Widget.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Graphics/Scene/Decoration.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Graphics/Level.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Graphics/Screen.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Utils/Logger.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Graphics/Shader.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Graphics/Core/Renderable.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Physics/Collidable.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Physics/PhysicsEnvironment.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Graphics/PostProcessor.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Graphics/Scene/Particle.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Game/Constants.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Graphics/Camera.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Utils/FileReader.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Graphics/Texture.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Graphics/Scene/Tile.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Game/Game.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Utils/ResourceManager.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Graphics/Scene/Sprite.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Graphics/Widgets/Button.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Graphics/Widgets/TexturedButton.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Graphics/Widgets/TextBox.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Graphics/Widgets/TextInput.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Graphics/Core/IWidget.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Graphics/Screens/TestScreen.h
        ${CMAKE_SOURCE_DIR}/include/CampEngine/Graphics/Screens/DebugScreen.h
)
# note that ${public_headers} has to be in quotes
#set_target_properties(lib_${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${public_headers}")

foreach(header ${public_headers})
    file(RELATIVE_PATH header_file_path "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}" "${header}")
    get_filename_component(header_directory_path "${header_file_path}" DIRECTORY)
    install(
            FILES ${header}
            DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${header_directory_path}"
    )
endforeach()

set_target_properties(lib_CampEngine++ PROPERTIES DEBUG_POSTFIX "d")

include(GNUInstallDirs)

# install the target and create export-set
install(TARGETS lib_CampEngine++
        EXPORT "CampEngine++Targets"
        # these get default values from GNUInstallDirs, no need to set them
        #RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # bin
        #LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
        #ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
        # except for public headers, as we want them to be inside a library folder
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/CampEngine # include/SomeLibrary
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} # include
)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# generate and install export file
install(EXPORT "CampEngine++Targets"
        FILE "CampEngine++Targets.cmake"
        NAMESPACE ${namespace}::
        DESTINATION cmake
)

include(CMakePackageConfigHelpers)

# generate the version file for the config file
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}ConfigVersion.cmake"
        VERSION "${version}"
        COMPATIBILITY AnyNewerVersion
)
# create config file
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION cmake
)
# install config files
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION cmake
)

#install(FILES ${PROJECT_HEADERS} ${DEPENDENCIES_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})