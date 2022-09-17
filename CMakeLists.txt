cmake_minimum_required(VERSION 3.20)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS} -framework OpenGL")

# config install files
SET(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
install(DIRECTORY assets/ DESTINATION assets)

# add glfw3
find_package(glfw3 3.3 REQUIRED)

file(
        GLOB LearnOpenGL_INCLUDE
        "*.h"
        "*.hpp"
)

include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${LearnOpenGL_INCLUDE}
)

add_executable(
        LearnOpenGL

        src/main.cpp
        src/glad.c

        src/engine/entity/Entity.h
        src/engine/gpu/GPUBuffer.cpp src/engine/gpu/GPUBuffer.h
        src/engine/gpu/GPUAction.cpp src/engine/gpu/GPUAction.h
        src/engine/entity/Mesh.cpp src/engine/entity/Mesh.h
        src/engine/shader/Shader.cpp src/engine/shader/Shader.h
        src/shader/TriangleShader.cpp src/shader/TriangleShader.h
)

target_link_libraries(
        ${PROJECT_NAME}
        glfw
)
