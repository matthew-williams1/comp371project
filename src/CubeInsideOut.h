#ifndef QUIZ_2_CUBEINSIDEOUT_H
#define QUIZ_2_CUBEINSIDEOUT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace glm;

class CubeInsideOut {
private:
    GLuint vertexBufferObject;
public:
    CubeInsideOut();

    CubeInsideOut(vec3 colorVec);

    GLuint getVertexBufferObject();
};

#endif //QUIZ_2_CUBEINSIDEOUT_H