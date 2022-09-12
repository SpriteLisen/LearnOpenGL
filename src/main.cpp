#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "shader/TriangleShader.h"
#include "engine/entity/Mesh.h"
#include <cmath>

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;
const char *WINDOW_TITLE = "LearnOpenGL";


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void drawChangeColor(Shader shader, Mesh mesh);

void onDraw(const Shader &shader, Mesh mesh);

int main() {
    // Init GLFW and GL Version
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /// macOS Only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    // Create a window
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Init GLAD
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Init GL_ViewPort
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    // listener window resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    Mesh mesh;

    // Prepare vertices
    std::vector<Vertex> vertices;
    vertices.emplace_back(0.5f, -0.5f, 0.0f);
    vertices.emplace_back(-0.5f, -0.5f, 0.0f);
    vertices.emplace_back(0.0f, 0.5f, 0.0f);
    mesh.setVertices(&vertices, "aPos");

    // Prepare colors
    std::vector<Color> colors;
    colors.emplace_back(1.0f, 0.0f, 0.0f);
    colors.emplace_back(0.0f, 1.0f, 0.0f);
    colors.emplace_back(0.0f, 0.0f, 1.0f);
    mesh.setColors(&colors, "aColors");

    // Prepare indices
    std::vector<unsigned int> indices;
    indices.emplace_back(0);
    indices.emplace_back(1);
    indices.emplace_back(2);
    mesh.setIndices(&indices);

    Shader triangleShader = TriangleShader::create()
            .bindMesh(&mesh)
    // .setUniformColor("uColor", Color(0.0f, 0.0f, 1.0f))
    ;

    // while loop render window
    while (!glfwWindowShouldClose(window)) {
        // User input
        processInput(window);

        // Render actions
        onDraw(triangleShader, mesh);

        // SwapBuffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void drawChangeColor(Shader shader, Mesh mesh) {
    auto timeValue = (float) glfwGetTime();
    float greenValue = sin(timeValue) / 2.0f + 0.5f;
    shader.setUniformVertex("uColor", Vertex(0.0f, greenValue, 0.0f, 1.0f));
}

void onDraw(const Shader &shader, Mesh mesh) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();
    // drawChangeColor(shader, mesh);
    mesh.use();
}