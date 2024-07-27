cmake_minimum_required(VERSION 3.4.1)


# Define the library to be built
add_library(native-lib SHARED
            textureCube/shaders/Shader.h
            textureCube/shaders/Shader.cpp
            textureCube/TextureCubeRenderer.h
            textureCube/TextureCubeRenderer.cpp
            Renderer.h
            native-lib.cpp
)

# Specify your project-specific include directories
include_directories(native-lib ${CMAKE_SOURCE_DIR}/../../../include)


# Find and link with necessary libraries
find_library(log-lib log)

target_link_libraries(native-lib
                      ${log-lib}
                      GLESv3
                        android
)