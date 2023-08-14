
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler
#include <GLFW/glfw3.h> 

#include <cmath>
#include <vector>
#include "Cube.h"
#include "ShaderProgram.h"

using namespace glm;

class Spectator {

private:
GLuint spectatorBodyVAO;
GLuint spectatorHeadVAO;
GLuint spectatorLeftArmVAO;
GLuint spectatorRightArmVAO;

public:

float var;
bool isDrawn;

vec3 position;

Spectator();

Spectator(vec3 colour, vec3 position, float variance); 

void draw(mat4 hierarchyModelMatrix, ShaderProgram shaderProgram, GLuint renderingMode, float rotation, float dtpos);


};