#ifndef PROJECT_CUBE_H
#define PROJECT_CUBE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace glm;

class Cube {
private:
    GLuint vertexBufferObject;
public:
    Cube();

    Cube(vec3 colorVec);

    GLuint getVertexBufferObject();
};

#endif //PROJECT_CUBE_H