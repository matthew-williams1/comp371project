#ifndef QUIZ_2_SHADERPROGRAM_H
#define QUIZ_2_SHADERPROGRAM_H

#include <iostream>
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

using namespace glm;

class ShaderProgram {
private:
    GLuint shaderId;

    bool isTexturesEnabled;

    const char *readShaderFile(const char* filePath);

    int compileAndLinkShaders(const char* vertexShaderPath, const char* fragmentShaderPath);
public:
    ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);

    GLuint getShaderId();

    bool getIsTexturesEnabled();
    
    void use();

    void setIsTexturesEnabled(bool isTexturesEnabled);

    void setBool(const char* name, bool value) const;

    void setInt(const char* name, int value) const;

    void setFloat(const char* name, float value) const;

    void setVec3(const char* name, const vec3 &value) const;

    void setVec3(const char* name, float x, float y, float z) const;

    void setMat4(const char* name, const mat4 &mat) const;
};

#endif //QUIZ_2_SHADERPROGRAM_H