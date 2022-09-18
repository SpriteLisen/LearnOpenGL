#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "shader/TriangleShader.h"
#include "engine/entity/Mesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

struct Program {
    Shader shader;
    Mesh mesh;
};

Program prepare();

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

    Program program = prepare();

    // while loop render window
    while (!glfwWindowShouldClose(window)) {
        // User input
        processInput(window);

        // Render actions
        onDraw(program.shader, program.mesh);

        // SwapBuffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

Program prepare() {
    Mesh *mesh = new Mesh();

    // Prepare vertices
    auto vertices = new std::vector<Vertex>();
    /*vertices->emplace_back(-0.5f, -0.5f, 0.0f);
    vertices->emplace_back(0.5f, -0.5f, 0.0f);
    vertices->emplace_back(-0.5f, 0.5f, 0.0f);
    vertices->emplace_back(0.5f, 0.5f, 0.0f);*/

    vertices->emplace_back(-0.5f, -0.5f, -0.5f);
    vertices->emplace_back(0.5f, -0.5f, -0.5f);
    vertices->emplace_back(0.5f, 0.5f, -0.5f);
    vertices->emplace_back(0.5f, 0.5f, -0.5f);
    vertices->emplace_back(-0.5f, 0.5f, -0.5f);
    vertices->emplace_back(-0.5f, -0.5f, -0.5f);

    vertices->emplace_back(-0.5f, -0.5f, 0.5f);
    vertices->emplace_back(0.5f, -0.5f, 0.5f);
    vertices->emplace_back(0.5f, 0.5f, 0.5f);
    vertices->emplace_back(0.5f, 0.5f, 0.5f);
    vertices->emplace_back(-0.5f, 0.5f, 0.5f);
    vertices->emplace_back(-0.5f, -0.5f, 0.5f);

    vertices->emplace_back(-0.5f, 0.5f, 0.5f);
    vertices->emplace_back(-0.5f, 0.5f, -0.5f);
    vertices->emplace_back(-0.5f, -0.5f, -0.5f);
    vertices->emplace_back(-0.5f, -0.5f, -0.5f);
    vertices->emplace_back(-0.5f, -0.5f, 0.5f);
    vertices->emplace_back(-0.5f, 0.5f, 0.5f);

    vertices->emplace_back(0.5f, 0.5f, 0.5f);
    vertices->emplace_back(0.5f, 0.5f, -0.5f);
    vertices->emplace_back(0.5f, -0.5f, -0.5f);
    vertices->emplace_back(0.5f, -0.5f, -0.5f);
    vertices->emplace_back(0.5f, -0.5f, 0.5f);
    vertices->emplace_back(0.5f, 0.5f, 0.5f);

    vertices->emplace_back(-0.5f, -0.5f, -0.5f);
    vertices->emplace_back(0.5f, -0.5f, -0.5f);
    vertices->emplace_back(0.5f, -0.5f, 0.5f);
    vertices->emplace_back(0.5f, -0.5f, 0.5f);
    vertices->emplace_back(-0.5f, -0.5f, 0.5f);
    vertices->emplace_back(-0.5f, -0.5f, -0.5f);

    vertices->emplace_back(-0.5f, 0.5f, -0.5f);
    vertices->emplace_back(0.5f, 0.5f, -0.5f);
    vertices->emplace_back(0.5f, 0.5f, 0.5f);
    vertices->emplace_back(0.5f, 0.5f, 0.5f);
    vertices->emplace_back(-0.5f, 0.5f, 0.5f);
    vertices->emplace_back(-0.5f, 0.5f, -0.5f);
    mesh->setVertices(vertices, "aPos");

    // Prepare colors
    /*std::vector<Color> colors;
    colors.emplace_back(1.0f, 0.0f, 0.0f);
    colors.emplace_back(0.0f, 1.0f, 0.0f);
    colors.emplace_back(0.0f, 0.0f, 1.0f);
    colors.emplace_back(1.0f, 0.0f, 1.0f);
    mesh.setColors(&colors, "aColors");*/

    // Prepare uvs
    auto uvs = new std::vector<UV>();
    /*uvs->emplace_back(0.0f, 0.0f);
    uvs->emplace_back(1.0f, 0.0f);
    uvs->emplace_back(0.0f, 1.0f);
    uvs->emplace_back(1.0f, 1.0f);*/

    uvs->emplace_back(0.0f, 0.0f);
    uvs->emplace_back(1.0f, 0.0f);
    uvs->emplace_back(1.0f, 1.0f);
    uvs->emplace_back(1.0f, 1.0f);
    uvs->emplace_back(0.0f, 1.0f);
    uvs->emplace_back(0.0f, 0.0f);

    uvs->emplace_back(0.0f, 0.0f);
    uvs->emplace_back(1.0f, 0.0f);
    uvs->emplace_back(1.0f, 1.0f);
    uvs->emplace_back(1.0f, 1.0f);
    uvs->emplace_back(0.0f, 1.0f);
    uvs->emplace_back(0.0f, 0.0f);

    uvs->emplace_back(1.0f, 0.0f);
    uvs->emplace_back(1.0f, 1.0f);
    uvs->emplace_back(0.0f, 1.0f);
    uvs->emplace_back(0.0f, 1.0f);
    uvs->emplace_back(0.0f, 0.0f);
    uvs->emplace_back(1.0f, 0.0f);

    uvs->emplace_back(1.0f, 0.0f);
    uvs->emplace_back(1.0f, 1.0f);
    uvs->emplace_back(0.0f, 1.0f);
    uvs->emplace_back(0.0f, 1.0f);
    uvs->emplace_back(0.0f, 0.0f);
    uvs->emplace_back(1.0f, 0.0f);

    uvs->emplace_back(0.0f, 1.0f);
    uvs->emplace_back(1.0f, 1.0f);
    uvs->emplace_back(1.0f, 0.0f);
    uvs->emplace_back(1.0f, 0.0f);
    uvs->emplace_back(0.0f, 0.0f);
    uvs->emplace_back(0.0f, 1.0f);

    uvs->emplace_back(0.0f, 1.0f);
    uvs->emplace_back(1.0f, 1.0f);
    uvs->emplace_back(1.0f, 0.0f);
    uvs->emplace_back(1.0f, 0.0f);
    uvs->emplace_back(0.0f, 0.0f);
    uvs->emplace_back(0.0f, 1.0f);
    mesh->setTexCoords(uvs, "aTexCoords");

    // Prepare indices
    /*auto indices = new std::vector<unsigned int>();
    indices->emplace_back(0);
    indices->emplace_back(1);
    indices->emplace_back(2);
    indices->emplace_back(2);
    indices->emplace_back(3);
    indices->emplace_back(1);
    mesh->setIndices(indices);*/

    // Prepare textures
    auto textures = new std::vector<Texture>();
    textures->push_back(Texture::fromFile("assets/texture/wall.jpg", "tex1"));
    textures->push_back(Texture::fromFile("assets/texture/smile.png", "tex2"));

    Shader triangleShader = TriangleShader::create()
            .setTextures(textures)
            .enableDepthTest()
            .bindMesh(mesh);

    return {triangleShader, *mesh};
}

void onDraw(Shader shader, Mesh mesh) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 model(1.0f);
    model = glm::rotate(
            model, (float) glfwGetTime() * glm::radians(50.0f),
            glm::vec3(0.5f, 1.0f, 0.0f)
    );

    glm::mat4 view(1.0f);
    // 注意，我们将矩阵向我们要进行移动场景的反方向移动。
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection(1.0f);
    projection = glm::perspective(
            glm::radians(45.0f),
            (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT,
            0.1f, 100.0f
    );

    glm::mat4 mat = projection * view * model;

    shader.setMat4("matrix", mat);

    shader.use();
    mesh.use();
}