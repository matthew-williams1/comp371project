//
// COMP 371 Programming Project
// By Jonathan Hubermann #40125401
//

#include <list>
#include <random>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler
#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context, initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>

using namespace glm;
using namespace std;

#include "ShaderProgram.h"
#include "Scene.h"

int main(int argc, char* argv[]) {

    /* SETUP */
    // Initialize GLFW and OpenGL version
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Make sure Double Buffering support is enabled
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

    // Create Window and rendering context using GLFW, resolution is 1024x768
    int windowWidth = 1024;
    int windowHeight = 768;
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Comp371 - Project", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Other OpenGL states to set once
    // Enable Backface culling
    glEnable(GL_CULL_FACE);

    // Enable Depth Test
    glEnable(GL_DEPTH_TEST);

    // Enable Blending (for alpha color functionality)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Turquoise background color
    glClearColor(43.0f/255.0f, 77.0f/255.0f, 76.0f/255.0f, 1.0f);

    /* SCENE */
    Scene scene;

    /* SHADERS */
    ShaderProgram modelShaderProgram = ShaderProgram("./assets/shaders/vertex_shader.glsl", "./assets/shaders/fragment_shader.glsl");
    ShaderProgram depthShaderProgram = ShaderProgram("./assets/shaders/depth_vertex_shader.glsl", "./assets/shaders/depth_fragment_shader.glsl");

    /* TEXTURES */
    modelShaderProgram.use();
    modelShaderProgram.setInt("textureSampler", 0);

    /* PHONG LIGHTING SETUP */
    // Pointlight
    bool isPointlightEnabled = true;
    modelShaderProgram.use();
    modelShaderProgram.setBool("isPointlightEnabled", isPointlightEnabled);

    vec3 lightPosPointlight = vec3(0.0f, 40.0f, 0.1f);
    modelShaderProgram.use();
    modelShaderProgram.setVec3("lightPosPointlight", lightPosPointlight);

    vec3 lightColorPointlight = vec3(1.0f, 1.0f, 1.0f);
    modelShaderProgram.use();
    modelShaderProgram.setVec3("lightColorPointlight", lightColorPointlight);

    // Stationary spotlight
    bool isSpotlight1Enabled = true;
    modelShaderProgram.use();
    modelShaderProgram.setBool("isSpotlight1Enabled", isSpotlight1Enabled);

    vec3 lightPosSpotlight1 = vec3(0.0f, 15.0f, 30.0f);
    modelShaderProgram.use();
    modelShaderProgram.setVec3("lightPosSpotlight1", lightPosSpotlight1);

    vec3 lightColorSpotlight1 = vec3(1.0f, 1.0f, 1.0f);
    modelShaderProgram.use();
    modelShaderProgram.setVec3("lightColorSpotlight1", lightColorSpotlight1);

    bool isSpotlight1RotationEnabled = false;
    float spotlight1Radius = 5.0f;
    float spotlight1DisplacementRate = 2.0f;
    float spotlight1Angle = 0.0f;

    // Rotating spotlight
    bool isSpotlight2Enabled = true;
    modelShaderProgram.use();
    modelShaderProgram.setBool("isSpotlight2Enabled", isSpotlight2Enabled);

    vec3 lightPosSpotlight2 = vec3(0.0f, 35.0f, 16.0f);
    modelShaderProgram.use();
    modelShaderProgram.setVec3("lightPosSpotlight2", lightPosSpotlight2);

    vec3 lightColorSpotlight2 = vec3(1.0f, 0.0f, 0.0f);
    modelShaderProgram.use();
    modelShaderProgram.setVec3("lightColorSpotlight2", lightColorSpotlight2);

    /* DEPTH MAP SETUP */
    unsigned int shadowWidth = 1024, shadowHeight = 768;
    // Acknowledgement that the following code was sourced from an example on LearnOpenGL (https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping)
    // Setup depth FBO
    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);

    // Setup depth texture
    unsigned int depthTexture;
    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    // Attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    /* SHADOWS SETUP */
    bool isShadowsEnabled = true;
    modelShaderProgram.setBool("isShadowsEnabled", isShadowsEnabled);

    /* CAMERA */
    // Main camera parameters for view transform
    vec3 mainCameraPosition(0.0f, 15.0f, 32.0f);
    vec3 mainCameraLookAt(0.0f, 0.0f, -1.0f);
    vec3 mainCameraUp(0.0f, 1.0f, 0.0f);

    float mainCameraHorizontalAngle = 90.0f;
    float mainCameraVerticalAngle = 0.0f;
    
    // Rotating camera parameters for view transform
    vec3 rotatingCameraPosition(0.0f, 35.0f, 16.0f);
    vec3 rotatingCameraLookAt(0.0f, 20.0f, 0.0f);
    vec3 rotatingCameraUp(0.0f, 1.0f, 0.0f);

    float rotatingCameraRadius = 16.0f;
    float rotatingCameraDisplacementRate = 2.0f;
    float rotatingCameraAngle = 0.0f;

    // Other camera control parameters
    float cameraPanRate = 20.0f;
    float cameraTiltRate = 20.0f;
    float cameraZoomRate = 0.5f;

    float fieldOfView = 60.0f / 360.0f * 2 * M_PI; // default field of view of 60 deg
    float minimumFieldOfView = 5.0f / 360.0f * 2 * M_PI;
    float maximumFieldOfView = 110.0f / 360.0f * 2 * M_PI;

    int cameraSelection = 0;

    /* VIEW SETUP */
    // Set initial view matrix
    // eye, center, up
    mat4 viewMatrix = lookAt(mainCameraPosition, mainCameraPosition + mainCameraLookAt, mainCameraUp);
    modelShaderProgram.setMat4("viewMatrix", viewMatrix);

    /* TIMING */
    // For frame time
    float lastFrameTime = glfwGetTime();

    /* MOUSE CURSOR */
    double lastMousePosX, lastMousePosY;
    glfwGetCursorPos(window, &lastMousePosX, &lastMousePosY);

    /* OTHER CONTROL VARIABLES */
    int modelSelection = 0;
    float controlTimer = 0.0f;

    /* ENTERING MAIN LOOP */
    while(!glfwWindowShouldClose(window)) {

        /* TIMING */
        // Frame time calculation
        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;

        /* PROJECTION INITIALIZATION */
        // Update the current window size
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        // Set the projection matrix for shader here since it is dependent on user input
        // FoV (deg), aspect ratio, near and far (near>0)
        mat4 projectionMatrix = perspective(fieldOfView, (float) windowWidth / (float) windowHeight, 0.01f, 100.0f);

        /* RENDERING */
        // DEPTH SCENE RENDERING
        mat4 lightProjection = perspective(radians(135.0f), (GLfloat) shadowWidth / (GLfloat) shadowHeight, 0.01f, 100.0f);
        mat4 lightView = lookAt(lightPosPointlight, vec3(0.0f), mainCameraUp);
        mat4 lightSpaceMatrix = lightProjection * lightView;
        depthShaderProgram.use();
        depthShaderProgram.setMat4("lightSpaceMatrix", lightSpaceMatrix);

        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glViewport(0, 0, windowWidth, windowHeight);
        glClear(GL_DEPTH_BUFFER_BIT);
        glCullFace(GL_FRONT);
        scene.setIsAlphaEnabled(false);
        scene.drawScene(depthShaderProgram);
        glCullFace(GL_BACK);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // MODEL SCENE RENDERING
        modelShaderProgram.use();
        modelShaderProgram.setMat4("projectionMatrix", projectionMatrix);
        modelShaderProgram.setMat4("viewMatrix", viewMatrix);
        modelShaderProgram.setMat4("lightSpaceMatrix", lightSpaceMatrix);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, shadowWidth * 2.0, shadowHeight * 2.0);
        // Each frame, reset color of each pixel to glClearColor and clear Depth Buffer Bit as well
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        modelShaderProgram.use();
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        modelShaderProgram.setInt("shadowMap", 1);
        scene.setIsAlphaEnabled(true);
        scene.drawScene(modelShaderProgram);

        // End Frame
        glfwSwapBuffers(window);
        glfwPollEvents();

        /* SPOTLIGHT1 ROTATING PATTERN (BONUS) */
        if (isSpotlight1RotationEnabled) {
            spotlight1Angle += spotlight1DisplacementRate * dt;
            float lightPosSpotlight1XNew = spotlight1Radius * cos(spotlight1Angle);
            float lightPosSpotlight1YNew = spotlight1Radius * sin(spotlight1Angle);
            lightPosSpotlight1 = vec3(lightPosSpotlight1XNew, lightPosSpotlight1YNew + 15.0f, lightPosSpotlight1.z);
            modelShaderProgram.use();
            modelShaderProgram.setVec3("lightPosSpotlight1", lightPosSpotlight1);
        }

        /* USER INPUT */
        bool isShiftPressed = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
        bool isControlPressed = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS;
        bool isAltPressed = glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS;

        // Exits the program
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Controls the current model selected
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            modelSelection = 0;
        }
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            modelSelection = 1;
        }

        // Re-positions model at a random location on the grid
        // Acknowledgment that the PRNG was based on online examples for true random number generation in C++
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            if (glfwGetTime() - controlTimer >= 0.1f) {
                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<> distrX(-16, 16);
                uniform_int_distribution<> distrZ(-37, 37);
                scene.model.at(modelSelection)->setModelPosition(vec3(distrX(gen), scene.model.at(modelSelection)->getModelPosition().y, distrZ(gen)));
                controlTimer = glfwGetTime();
            }
        }

        // Incrementally scales the model up (larger)
        float modelScaleDelta = scene.model.at(modelSelection)->getModelScaleRate() * dt;
        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
            scene.model.at(modelSelection)->setModelScale(scene.model.at(modelSelection)->getModelScale() + vec3(modelScaleDelta, modelScaleDelta, modelScaleDelta));
        }
        // Incrementally scales the model down (smaller)
        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
            scene.model.at(modelSelection)->setModelScale(scene.model.at(modelSelection)->getModelScale() - vec3(modelScaleDelta, modelScaleDelta, modelScaleDelta));
        }

        // Controls the model position and rotation
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            if (isShiftPressed) {
                // Displaces the whole model negatively along the X-axis
                float modelDisplacement = -1 * scene.model.at(modelSelection)->getModelDisplacementRate() * dt;
                scene.model.at(modelSelection)->setModelPosition(scene.model.at(modelSelection)->getModelPosition() + vec3(modelDisplacement, 0.0f, 0.0f));
            } else if (isControlPressed) {
                // Rotates the lower arm in the model negatively around the Y-axis
                float modelLowerarmRotationDelta = -1 * scene.model.at(modelSelection)->getModelRotationRate() * dt;
                scene.model.at(modelSelection)->setModelLowerarmRotationYAxis(scene.model.at(modelSelection)->getModelLowerarmRotationYAxis() + modelLowerarmRotationDelta);
            } else if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
                // Rotates the hand in the model negatively around the Y-axis
                float modelHandRotationDelta = -1 * scene.model.at(modelSelection)->getModelRotationRate() * dt;
                scene.model.at(modelSelection)->setModelHandRotationYAxis(scene.model.at(modelSelection)->getModelHandRotationYAxis() + modelHandRotationDelta);
            } else {
                // Rotates the whole model negatively around the Y-axis
                float modelRotationDelta = -1 * scene.model.at(modelSelection)->getModelRotationRate() * dt;
                scene.model.at(modelSelection)->setModelRotationYAxis(scene.model.at(modelSelection)->getModelRotationYAxis() + modelRotationDelta);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            if (isShiftPressed) {
                // Displaces the whole model positively along the X-axis
                float modelDisplacement = 1 * scene.model.at(modelSelection)->getModelDisplacementRate() * dt;
                scene.model.at(modelSelection)->setModelPosition(scene.model.at(modelSelection)->getModelPosition() + vec3(modelDisplacement, 0.0f, 0.0f));
            } else if (isControlPressed) {
                // Rotates the lower arm in the model positively around the Y-axis
                float modelLowerarmRotationDelta = 1 * scene.model.at(modelSelection)->getModelRotationRate() * dt;
                scene.model.at(modelSelection)->setModelLowerarmRotationYAxis(scene.model.at(modelSelection)->getModelLowerarmRotationYAxis() + modelLowerarmRotationDelta);
                // Rotates the hand in the model positively around the Y-axis
            } else if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
                float modelHandRotationDelta = 1 * scene.model.at(modelSelection)->getModelRotationRate() * dt;
                scene.model.at(modelSelection)->setModelHandRotationYAxis(scene.model.at(modelSelection)->getModelHandRotationYAxis() + modelHandRotationDelta);
            } else {
                // Rotates the whole model positively around the Y-axis
                float modelRotationDelta = 1 * scene.model.at(modelSelection)->getModelRotationRate() * dt;
                scene.model.at(modelSelection)->setModelRotationYAxis(scene.model.at(modelSelection)->getModelRotationYAxis() + modelRotationDelta);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            if (isShiftPressed) {
                // Displaces the whole model positively along the Y-axis
                float modelDisplacement = 1 * scene.model.at(modelSelection)->getModelDisplacementRate() * dt;
                scene.model.at(modelSelection)->setModelPosition(scene.model.at(modelSelection)->getModelPosition() + vec3(0.0f, modelDisplacement, 0.0f));
            } else if (isControlPressed) {
                // Rotates the lower arm in the model negatively around the X-axis
                float modelLowerarmRotationDelta = -1 * scene.model.at(modelSelection)->getModelRotationRate() * dt;
                scene.model.at(modelSelection)->setModelLowerarmRotationXAxis(scene.model.at(modelSelection)->getModelLowerarmRotationXAxis() + modelLowerarmRotationDelta);
            } else if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
                // Rotates the hand in the model negatively around the X-axis
                float modelHandRotationDelta = -1 * scene.model.at(modelSelection)->getModelRotationRate() * dt;
                scene.model.at(modelSelection)->setModelHandRotationXAxis(scene.model.at(modelSelection)->getModelHandRotationXAxis() + modelHandRotationDelta);
            } else {
                // Rotates the whole model negatively around the X-axis
                float modelRotationDelta = -1 * scene.model.at(modelSelection)->getModelRotationRate() * dt;
                scene.model.at(modelSelection)->setModelRotationXAxis(scene.model.at(modelSelection)->getModelRotationXAxis() + modelRotationDelta);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            if (isShiftPressed) {
                // Displaces the whole model negatively along the Y-axis
                float modelDisplacement = -1 * scene.model.at(modelSelection)->getModelDisplacementRate() * dt;
                scene.model.at(modelSelection)->setModelPosition(scene.model.at(modelSelection)->getModelPosition() + vec3(0.0f, modelDisplacement, 0.0f));
            } else if (isControlPressed) {
                // Rotates the lower arm in the model positively around the X-axis
                float modelLowerarmRotationDelta = 1 * scene.model.at(modelSelection)->getModelRotationRate() * dt;
                scene.model.at(modelSelection)->setModelLowerarmRotationXAxis(scene.model.at(modelSelection)->getModelLowerarmRotationXAxis() + modelLowerarmRotationDelta);
            } else if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
                // Rotates the hand in the model positively around the X-axis
                float modelHandRotationDelta = 1 * scene.model.at(modelSelection)->getModelRotationRate() * dt;
                scene.model.at(modelSelection)->setModelHandRotationXAxis(scene.model.at(modelSelection)->getModelHandRotationXAxis() + modelHandRotationDelta);
            } else {
                // Rotates the whole model positively around the X-axis
                float modelRotationDelta = 1 * scene.model.at(modelSelection)->getModelRotationRate() * dt;
                scene.model.at(modelSelection)->setModelRotationXAxis(scene.model.at(modelSelection)->getModelRotationXAxis() + modelRotationDelta);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            if (isShiftPressed) {
                // Displaces the whole model positively along the Z-axis
                float modelDisplacement = 1 * scene.model.at(modelSelection)->getModelDisplacementRate() * dt;
                scene.model.at(modelSelection)->setModelPosition(scene.model.at(modelSelection)->getModelPosition() + vec3(0.0f, 0.0f, modelDisplacement));
            } else if (isControlPressed) {
                // Rotates the lower arm in the model positively around the Z-axis
                float modelLowerarmRotationDelta = 1 * scene.model.at(modelSelection)->getModelRotationRate() * dt;
                scene.model.at(modelSelection)->setModelLowerarmRotationZAxis(scene.model.at(modelSelection)->getModelLowerarmRotationZAxis() + modelLowerarmRotationDelta);
            } else if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
                // Rotates the hand in the model positively around the Z-axis
                float modelHandRotationDelta = 1 * scene.model.at(modelSelection)->getModelRotationRate() * dt;
                scene.model.at(modelSelection)->setModelHandRotationZAxis(scene.model.at(modelSelection)->getModelHandRotationZAxis() + modelHandRotationDelta);
            } else {
                // Rotates the whole model positively around the Z-axis
                float modelRotationDelta = 1 * scene.model.at(modelSelection)->getModelRotationRate() * dt;
                scene.model.at(modelSelection)->setModelRotationZAxis(scene.model.at(modelSelection)->getModelRotationZAxis() + modelRotationDelta);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            if (isShiftPressed) {
                // Displaces the whole model negatively along the Z-axis
                float modelDisplacement = -1 * scene.model.at(modelSelection)->getModelDisplacementRate() * dt;
                scene.model.at(modelSelection)->setModelPosition(scene.model.at(modelSelection)->getModelPosition() + vec3(0.0f, 0.0f, modelDisplacement));
            } else if (isControlPressed) {
                // Rotates the lower arm in the model negatively around the Z-axis
                float modelLowerarmRotationDelta = -1 * scene.model.at(modelSelection)->getModelRotationRate() * dt;
                scene.model.at(modelSelection)->setModelLowerarmRotationZAxis(scene.model.at(modelSelection)->getModelLowerarmRotationZAxis() + modelLowerarmRotationDelta);
            } else if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
                // Rotates the hand in the model negatively around the Z-axis
                float modelHandRotationDelta = -1 * scene.model.at(modelSelection)->getModelRotationRate() * dt;
                scene.model.at(modelSelection)->setModelHandRotationZAxis(scene.model.at(modelSelection)->getModelHandRotationZAxis() + modelHandRotationDelta);
            } else {
                // Rotates the whole model negatively around the Z-axis
                float modelRotationDelta = -1 * scene.model.at(modelSelection)->getModelRotationRate() * dt;
                scene.model.at(modelSelection)->setModelRotationZAxis(scene.model.at(modelSelection)->getModelRotationZAxis() + modelRotationDelta);
            }
        }

        // Resets the model position and rotation to default
        if (glfwGetKey(window, GLFW_KEY_END) == GLFW_PRESS) {
            scene.model.at(0)->setModelPosition(vec3(0.0f, 8.0f, 20.0f));
            scene.model.at(1)->setModelPosition(vec3(0.0f, 8.0f, -20.0f));
            for (int n=0; n<2; ++n) {
                scene.model.at(n)->setModelRotationZAxis(0.0f);
                scene.model.at(n)->setModelRotationYAxis(0.0f);
                scene.model.at(n)->setModelRotationXAxis(0.0f);
                scene.model.at(n)->setModelLowerarmRotationZAxis(0.0f);
                scene.model.at(n)->setModelLowerarmRotationYAxis(0.0f);
                scene.model.at(n)->setModelLowerarmRotationXAxis(0.0f);
                scene.model.at(n)->setModelHandRotationZAxis(0.0f);
                scene.model.at(n)->setModelHandRotationYAxis(0.0f);
                scene.model.at(n)->setModelHandRotationXAxis(0.0f);
            }
        }

        // Controls the world rotation and rotating camera displacement
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            if (isShiftPressed) {
                // Rotates the world positively around the Z-axis
                float worldRotationDelta = 1 * scene.getWorldRotationRate() * dt;
                scene.setWorldRotationZAxis(scene.getWorldRotationZAxis() + worldRotationDelta);
            } else if (isAltPressed) {
                // Displaces the camera positively along a circular path
                rotatingCameraAngle += 1 * rotatingCameraDisplacementRate * dt;
                float rotatingCameraPosXNew = rotatingCameraRadius * cos(rotatingCameraAngle);
                float rotatingCameraPosZNew = rotatingCameraRadius * sin(rotatingCameraAngle);
                rotatingCameraPosition = vec3(rotatingCameraPosXNew, rotatingCameraPosition.y, rotatingCameraPosZNew);
                lightPosSpotlight2 = rotatingCameraPosition;
                modelShaderProgram.use();
                modelShaderProgram.setVec3("lightPosSpotlight2", lightPosSpotlight2);
            } else {
                // Rotates the world negatively around the X-axis
                float worldRotationDelta = -1 * scene.getWorldRotationRate() * dt;
                scene.setWorldRotationXAxis(scene.getWorldRotationXAxis() + worldRotationDelta);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            if (isShiftPressed) {
                // Rotates the world negatively around the Z-axis
                float worldRotationDelta = -1 * scene.getWorldRotationRate() * dt;
                scene.setWorldRotationZAxis(scene.getWorldRotationZAxis() + worldRotationDelta);
            } else if (isAltPressed) {
                // Displaces the camera negatively along a circular path
                rotatingCameraAngle += -1 * rotatingCameraDisplacementRate * dt;
                float rotatingCameraPosXNew = rotatingCameraRadius * cos(rotatingCameraAngle);
                float rotatingCameraPosZNew = rotatingCameraRadius * sin(rotatingCameraAngle);
                rotatingCameraPosition = vec3(rotatingCameraPosXNew, rotatingCameraPosition.y, rotatingCameraPosZNew);
                lightPosSpotlight2 = rotatingCameraPosition;
                modelShaderProgram.use();
                modelShaderProgram.setVec3("lightPosSpotlight2", lightPosSpotlight2);
            } else {
                // Rotates the world positively around the X-axis
                float worldRotationDelta = 1 * scene.getWorldRotationRate() * dt;
                scene.setWorldRotationXAxis(scene.getWorldRotationXAxis() + worldRotationDelta);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            // Rotates the world negatively around the Y-axis
            float worldRotationDelta = -1 * scene.getWorldRotationRate() * dt;
            scene.setWorldRotationYAxis(scene.getWorldRotationYAxis() + worldRotationDelta);
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            // Rotates the world positively around the Y-axis
            float worldRotationDelta = 1 * scene.getWorldRotationRate() * dt;
            scene.setWorldRotationYAxis(scene.getWorldRotationYAxis() + worldRotationDelta);
        }

        // Resets the world rotation to default
        if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS) {
            scene.setWorldRotationXAxis(0.0f);
            scene.setWorldRotationYAxis(0.0f);
            scene.setWorldRotationZAxis(0.0f);
        }

        // Controls the rendering mode
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
            scene.setRenderingMode(GL_POINTS);
        }
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && !isShiftPressed && !isControlPressed) {
            scene.setRenderingMode(GL_LINES);
        }
        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
            scene.setRenderingMode(GL_TRIANGLES);
        }

        // Controls the toggling of textures
        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
            if (glfwGetTime() - controlTimer >= 0.1f) {
                modelShaderProgram.setIsTexturesEnabled(!modelShaderProgram.getIsTexturesEnabled());
                controlTimer = glfwGetTime();
            }
        }

        // Controls the toggling of shadows and toggling of the pointlight entirely
        if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
            if (glfwGetTime() - controlTimer >= 0.1f) {
                if (isShiftPressed) {
                    isPointlightEnabled = !isPointlightEnabled;
                    modelShaderProgram.use();
                    modelShaderProgram.setBool("isPointlightEnabled", isPointlightEnabled);
                } else {
                    isShadowsEnabled = !isShadowsEnabled;
                    modelShaderProgram.use();
                    modelShaderProgram.setBool("isShadowsEnabled", isShadowsEnabled);
                }
                controlTimer = glfwGetTime();
            }
        }

        // Controls the toggling of the model-facing spotlight (spotlight1) and its rotation pattern
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
            if (glfwGetTime() - controlTimer >= 0.1f) {
                if (isShiftPressed) {
                    isSpotlight1Enabled = !isSpotlight1Enabled;
                    modelShaderProgram.use();
                    modelShaderProgram.setBool("isSpotlight1Enabled", isSpotlight1Enabled);
                } else if (isControlPressed) {
                    isSpotlight1RotationEnabled = !isSpotlight1RotationEnabled;
                }
                controlTimer = glfwGetTime();
            }
        }

        // Controls the toggling of the rotating spotlight (spotlight2)
        if (isShiftPressed && glfwGetKey(window, GLFW_KEY_SEMICOLON) == GLFW_PRESS) {
            if (glfwGetTime() - controlTimer >= 0.1f) {
                isSpotlight2Enabled = !isSpotlight2Enabled;
                modelShaderProgram.use();
                modelShaderProgram.setBool("isSpotlight2Enabled", isSpotlight2Enabled);
                controlTimer = glfwGetTime();
            }
        }

        // Controls the iteration through the cameras
        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
            if (glfwGetTime() - controlTimer >= 0.1f) {
                cameraSelection = (cameraSelection + 1) % 4;
                controlTimer = glfwGetTime();
            }
        }

        // Selects the main camera
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            cameraSelection = 0;
        }

        // Calculates the view depending on which camera is selected
        vec3 cameraModelPosition;
        mat4 cameraModelRotation;
        switch (cameraSelection) {
            case 0:
                viewMatrix = lookAt(mainCameraPosition, mainCameraPosition + mainCameraLookAt, mainCameraUp);
                modelShaderProgram.use();
                modelShaderProgram.setMat4("viewMatrix", viewMatrix);
                break;
            case 1:
                cameraModelPosition = scene.model.at(0)->getModelPosition();
                cameraModelRotation = translate(mat4(1.0f), scene.model.at(0)->getModelPosition()) * rotate(mat4(1.0f), radians(scene.model.at(0)->getModelRotationZAxis()), vec3(0.0f, 0.0f, 1.0f)) * rotate(mat4(1.0f), radians(scene.model.at(0)->getModelRotationYAxis()), vec3(0.0f, 1.0f, 0.0f)) * rotate(mat4(1.0f), radians(scene.model.at(0)->getModelRotationXAxis()), vec3(1.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), scene.model.at(0)->getModelScale());
                viewMatrix = lookAt(cameraModelPosition, cameraModelPosition + vec3(inverse(transpose(cameraModelRotation))[2]), mainCameraUp);
                modelShaderProgram.use();
                modelShaderProgram.setMat4("viewMatrix", viewMatrix);
                break;
            case 2:
                cameraModelPosition = scene.model.at(1)->getModelPosition();
                cameraModelRotation = translate(mat4(1.0f), scene.model.at(1)->getModelPosition()) * rotate(mat4(1.0f), radians(scene.model.at(1)->getModelRotationZAxis()), vec3(0.0f, 0.0f, 1.0f)) * rotate(mat4(1.0f), radians(scene.model.at(1)->getModelRotationYAxis()), vec3(0.0f, 1.0f, 0.0f)) * rotate(mat4(1.0f), radians(scene.model.at(1)->getModelRotationXAxis()), vec3(1.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), scene.model.at(1)->getModelScale());
                viewMatrix = lookAt(cameraModelPosition, cameraModelPosition + vec3(inverse(transpose(cameraModelRotation))[2]), mainCameraUp);
                modelShaderProgram.use();
                modelShaderProgram.setMat4("viewMatrix", viewMatrix);
                break;
            case 3:
                viewMatrix = lookAt(rotatingCameraPosition, rotatingCameraLookAt, rotatingCameraUp);
                modelShaderProgram.use();
                modelShaderProgram.setMat4("viewMatrix", viewMatrix);
                break;
        }

        /*
        // Declare and store the current mouse position
        double mousePosX, mousePosY;
        glfwGetCursorPos(window, &mousePosX, &mousePosY);

        // Calculate mouse x- and y-position delta
        double dx = mousePosX - lastMousePosX;
        double dy = mousePosY - lastMousePosY;

        // Set the last mouse position as the current mouse position
        lastMousePosX = mousePosX;
        lastMousePosY = mousePosY;

        // Apply angular delta and convert to spherical coordinates
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            mainCameraHorizontalAngle += -1 * cameraPanRate * dt * dx;
        }
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
            mainCameraVerticalAngle += -1 * cameraTiltRate * dt * dy;
        }
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            fieldOfView += cameraZoomRate * dt * dy;
            fieldOfView = std::max(minimumFieldOfView, std::min(maximumFieldOfView, fieldOfView));
        }

        // Clamp vertical angle to [-85, 85] degrees
        mainCameraVerticalAngle = std::max(-85.0f, std::min(85.0f, mainCameraVerticalAngle));
        if (mainCameraHorizontalAngle > 360)
        {
            mainCameraHorizontalAngle -= 360;
        }
        else if (mainCameraHorizontalAngle < -360)
        {
            mainCameraHorizontalAngle += 360;
        }

        float theta = radians(mainCameraHorizontalAngle);
        float phi = radians(mainCameraVerticalAngle);

        mainCameraLookAt = vec3(cosf(phi)*cosf(theta), sinf(phi), -cosf(phi)*sinf(theta));

        mat4 viewMatrix = lookAt(mainCameraPosition, mainCameraPosition + mainCameraLookAt, mainCameraUp);
        setViewMatrix(colorShaderProgram, viewMatrix);
        setViewMatrix(textureShaderProgram, viewMatrix);

        // Resets the camera view to default
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
            mainCameraHorizontalAngle = 90.0f;
            mainCameraVerticalAngle = 0.0f;
            fieldOfView = 60.0f / 360.0f * 2 * M_PI;
        }
         */
    }

    // Shutdown GLFW
    glfwTerminate();

    return 0;
}