
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler
#include <GLFW/glfw3.h> 
#include "Texture.h"

#include "Cube.h"
#include "ShaderProgram.h"
using namespace std;
using namespace glm;

class Bleacher {
    private:
    GLuint bleacherWidePlankVAO;
    GLuint bleacherNarrowPlank;

    vec3 position;
    float direction;
    Texture seatText;
    Texture woodText;

    
    public:

    Bleacher();
    Bleacher(vec3 pos, float dir);

    void draw(mat4 hierarchyModelMatrix, ShaderProgram shaderProgram);

};
