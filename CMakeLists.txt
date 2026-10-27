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
        src/renderer/Shader.cpp
        src/renderer/VertexBuffer.cpp
        src/renderer/VertexArray.cpp
        src/renderer/VertexBufferLayout.cpp
        src/renderer/Renderer.cpp
        src/core/Application.cpp
        src/core/Window.cpp
)

file(
        MAKE_DIRECTORY
        "${CMAKE_CURRENT_BINARY_DIR}/shaders"
)

configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders/vertex.glsl"
        "${CMAKE_CURRENT_BINARY_DIR}/shaders/vertex.glsl"
        COPYONLY
)

configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders/fragment.glsl"
        "${CMAKE_CURRENT_BINARY_DIR}/shaders/fragment.glsl"
        COPYONLY
)

target_link_libraries(
        3D_Renderer
        PRIVATE
        glfw
        glad_gl_core_33
)