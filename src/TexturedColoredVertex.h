#ifndef PROJECT_TEXTUREDCOLOREDVERTEX_H
#define PROJECT_TEXTUREDCOLOREDVERTEX_H

#include <glm/glm.hpp>

using namespace glm;

class TexturedColoredVertex {
private:
    vec3 position;
    vec3 color;
    vec3 normal;
    vec2 uv;
public:
    TexturedColoredVertex();

    TexturedColoredVertex(vec3 position, vec3 color, vec3 normal, vec2 uv);
};

#endif //PROJECT_TEXTUREDCOLOREDVERTEX_H