#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "shader/TriangleShader.h"
#include "engine/entity/Mesh.h"
#include <math.h>

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

void onDraw(Shader shader, Mesh mesh);

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

    Shader triangleShader = TriangleShader::create()
            .setUniformColor("uColor", Color(0.0f, 0.0f, 1.0f));

    Mesh mesh;

    // 准备顶点数据
    std::vector<Vertex> vertices;
    vertices.emplace_back(0.5f, 0.5f, 0.0f);
    vertices.emplace_back(0.5f, -0.5f, 0.0f);
    vertices.emplace_back(-0.5f, -0.5f, 0.0f);
    vertices.emplace_back(-0.5f, 0.5f, 0.0f);
    mesh.setVertices(vertices);

    std::vector<unsigned int> indices;
    indices.emplace_back(0);
    indices.emplace_back(1);
    indices.emplace_back(3);
    indices.emplace_back(1);
    indices.emplace_back(2);
    indices.emplace_back(3);
    mesh.setIndices(indices);

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

void onDraw(Shader shader, Mesh mesh) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();

    float timeValue = glfwGetTime();
    float greenValue = sin(timeValue) / 2.0f + 0.5f;
    shader.setUniformVertex("uColor", Vertex(0.0f, greenValue, 0.0f, 1.0f));

    mesh.useVertices();
}