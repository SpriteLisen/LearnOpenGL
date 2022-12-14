cmake_minimum_required(VERSION 3.20)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS} -framework OpenGL")

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

        src/engine/entity/Vertex.cpp src/engine/entity/Vertex.h
        src/engine/entity/Mesh.cpp src/engine/entity/Mesh.h
        src/engine/shader/Shader.cpp src/engine/shader/Shader.h
        src/shader/TriangleShader.cpp src/shader/TriangleShader.h
        src/engine/entity/Color.cpp src/engine/entity/Color.h
)

target_link_libraries(
        ${PROJECT_NAME}
        glfw
)
