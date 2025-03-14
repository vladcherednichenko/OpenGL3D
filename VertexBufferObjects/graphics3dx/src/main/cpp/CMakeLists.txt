cmake_minimum_required(VERSION 3.4.1)


set(GAME_SOURCE)

# start of auto-generated source files list, do not edit

set(GAME_SOURCE
    native-lib.cpp
    textureCube/FpsCounter.cpp
    textureCube/shaders/Shader.cpp
    textureCube/TextureCubeRenderer.cpp
    )

# end of auto-generated source files list

# Define the library to be built
add_library(native-lib SHARED
        ${GAME_SOURCE}
        )

# Specify your project-specific include directories
include_directories(native-lib ${CMAKE_SOURCE_DIR}/../../../include)


# Find and link with necessary libraries
find_library(
        log-lib log
)

find_library(
        android-lib android
)

find_library(
        EGL-lib EGL
)

find_library(
        GLESv3-lib GLESv3
)

find_package(games-frame-pacing REQUIRED CONFIG)

target_link_libraries(
        native-lib  # Your native library target
        ${log-lib}  # Android logging library
        ${android-lib}  # Android native API
        ${EGL-lib}  # EGL library (fixes your error)
        ${GLESv3-lib}  # OpenGL ES 3.0 library
        games-frame-pacing::swappy_static
)