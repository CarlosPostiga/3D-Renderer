cmake_minimum_required(VERSION 3.20)

project(3D_Renderer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# --------------------------------------------------
# Build external libraries statically
# --------------------------------------------------

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# --------------------------------------------------
# GLFW
# --------------------------------------------------

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)

FetchContent_MakeAvailable(glfw)

# --------------------------------------------------
# GLAD
# --------------------------------------------------

FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG v2.0.8
        SOURCE_SUBDIR cmake
)

FetchContent_MakeAvailable(glad)

glad_add_library(
        glad_gl_core_33
        STATIC
        REPRODUCIBLE
        API gl:core=3.3
)

# --------------------------------------------------
# Our application
# --------------------------------------------------

add_executable(
        3D_Renderer
        src/main.cpp
)

target_link_libraries(
        3D_Renderer
        PRIVATE
        glfw
        glad_gl_core_33
)