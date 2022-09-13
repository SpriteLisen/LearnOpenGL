//
// Created by SpriteLisen on 2022/9/11.
//

#include "Shader.h"
#include <iostream>
#include "glad/glad.h"

Shader::Shader(const std::string &vertexSourceFilePath, const std::string &fragmentSourceFilePath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;

    // Ensure file can throw exceptions
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // Open files
        vertexShaderFile.open(vertexSourceFilePath);
        fragmentShaderFile.open(fragmentSourceFilePath);
        std::stringstream vertexShaderStream, fragmentShaderStream;
        // Save file content to buffer
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();
        // Close file processor
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // string to char* for init
        init(vertexShaderStream.str().c_str(), fragmentShaderStream.str().c_str());

    }
    catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
}

Shader::Shader(const char *vertexShaderSource, const char *fragmentShaderSource) {
    init(vertexShaderSource, fragmentShaderSource);
}

void Shader::init(const char *vShaderSource, const char *fShaderSource) {
    this->vertexShaderSource = vShaderSource;
    this->fragmentShaderSource = fShaderSource;
    this->compileShader();
}

void Shader::compileShader() {
    // 编译 vertexShader 程序
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &this->vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 编译 fragmentShader 程序
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &this->fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 创建并链接一个程序
    this->programId = glCreateProgram();
    glAttachShader(this->programId, vertexShader);
    glAttachShader(this->programId, fragmentShader);
    glLinkProgram(this->programId);

    glGetProgramiv(this->programId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->programId, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::LINK::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 链接程序完毕后可以回收掉 Shader
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() const {
    glUseProgram(this->programId);
}

Shader Shader::setUniformVertex(const char *uniformName, Vertex vertex) {
    this->setUniform4f(uniformName, vertex.getX(), vertex.getY(), vertex.getZ(), vertex.getW());
    return *this;
}

Shader Shader::setUniformColor(const char *uniformName, Color color) {
    this->setUniform4f(uniformName, color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
    return *this;
}

int Shader::getUniformIndex(const char *uniformName) {
    auto result = this->uniformCache.find(uniformName);

    int uniformIndex = -1;
    if (result != this->uniformCache.end()) {
        uniformIndex = result->second;
    } else {
        uniformIndex = glGetUniformLocation(this->programId, uniformName);
        if (uniformIndex == -1) {
            std::cout << "Not find uniform '" << uniformName << "' in Shader" << std::endl;
            throw std::runtime_error("Not find uniform in Shader!");
        }
        this->uniformCache.insert(std::make_pair(uniformName, uniformIndex));
    }

    return uniformIndex;
}

void Shader::setUniform4f(const char *uniformName, float f1, float f2, float f3, float f4) {
    int uniformIndex = this->getUniformIndex(uniformName);
    // 必须先激活 Shader 程序, 因为是在 Shader 程序中来设置对应的 uniform
    glUseProgram(this->programId);
    glUniform4f(uniformIndex, f1, f2, f3, f4);
}

Shader Shader::setUniformFloat(const char *uniformName, float value) {
    int uniformIndex = this->getUniformIndex(uniformName);
    glUseProgram(this->programId);
    glUniform1f(uniformIndex, value);
    return *this;
}

Shader Shader::setUniformInt(const char *uniformName, int value) {
    int uniformIndex = this->getUniformIndex(uniformName);
    glUseProgram(this->programId);
    glUniform1i(uniformIndex, value);
    return *this;
}


int Shader::getAttribIndex(const char *attribName) {
    auto result = this->attribCache.find(attribName);

    int attribIndex = -1;
    if (result != this->attribCache.end()) {
        attribIndex = result->second;
    } else {
        attribIndex = glGetAttribLocation(this->programId, attribName);
        if (attribIndex == -1) {
            std::cout << "Not find attrib '" << attribName << "' in Shader" << std::endl;
            throw std::runtime_error("Not find attrib in Shader!");
        }
        this->attribCache.insert(std::make_pair(attribName, attribIndex));
    }

    return attribIndex;
}

Shader Shader::bindMesh(Mesh *m) {
    if (m == nullptr) {
        throw std::runtime_error("The mesh must not be nullptr!");
    }
    this->mesh = m;
    if (mesh->vertices == nullptr) {
        throw std::runtime_error("The mesh must have vertices!");
    }

    mesh->bindToShader(
            getAttribIndex(mesh->verticesAttribName),
            mesh->colorsAttribName == nullptr ? -1 : getAttribIndex(mesh->colorsAttribName)
    );

    return *this;
}