#include "ShaderProgram.h"

#include <fstream>

using namespace std;

ShaderProgram::ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath) {
    this->shaderId = compileAndLinkShaders(vertexShaderPath, fragmentShaderPath);
    this->isTexturesEnabled = true;
}

// Acknowledgment that some of this method was based on online examples for file input in C++
const char* ShaderProgram::readShaderFile(const char* filePath) {
       // Create stream object and check for error on file open
    FILE *f = fopen(filePath, "rb");
    if (f == NULL) {
        fprintf(stderr, "failed to open file %s\n", filePath);
        exit(1);
    }

    // Seek the end position of the file, save the size at the point, rewind to beginning of file
    fseek(f, 0, SEEK_END);
    long fileSize = ftell(f);
    rewind(f);

    // Initialize char array to same length as file size and read contents of file into char array
    char *contents = new char[fileSize + 1];
    fread(contents, fileSize, 1, f);
    fclose(f);

    // Null terminator
    contents[fileSize] = 0;
    // Return the content as char array
    return contents;
}

int ShaderProgram::compileAndLinkShaders(const char* vertexShaderPath, const char* fragmentShaderPath) {
    // Compile vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderSource = readShaderFile(vertexShaderPath);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }

    // Compile fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSource = readShaderFile(fragmentShaderPath);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }

    // Link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

GLuint ShaderProgram::getShaderId() {
    return this->shaderId;
}

bool ShaderProgram::getIsTexturesEnabled() {
    return this->isTexturesEnabled;
}

void ShaderProgram::use() {
    glUseProgram(shaderId);
}

void ShaderProgram::setIsTexturesEnabled(bool isTexturesEnabled) {
    this->isTexturesEnabled = isTexturesEnabled;
}

void ShaderProgram::setBool(const char* name, bool value) const {
    glUniform1i(glGetUniformLocation(shaderId, name), (int)value);
}

void ShaderProgram::setInt(const char* name, int value) const {
    glUniform1i(glGetUniformLocation(shaderId, name), value);
}

void ShaderProgram::setFloat(const char* name, float value) const {
    glUniform1f(glGetUniformLocation(shaderId, name), value);
}

void ShaderProgram::setVec3(const char* name, const vec3 &value) const {
    glUniform3fv(glGetUniformLocation(shaderId, name), 1, &value[0]);
}

void ShaderProgram::setVec3(const char* name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(shaderId, name), x, y, z);
}

void ShaderProgram::setMat4(const char* name, const mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(shaderId, name), 1, GL_FALSE, &mat[0][0]);
}