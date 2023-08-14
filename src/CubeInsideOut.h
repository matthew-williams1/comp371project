#ifndef PROJECT_CUBEINSIDEOUT_H
#define PROJECT_CUBEINSIDEOUT_H

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

#endif //PROJECT_CUBEINSIDEOUT_H