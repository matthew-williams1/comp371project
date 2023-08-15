#include "Scene.h"
#include "Cube.h"
#include "CubeInsideOut.h"
#include <random>

//for random spectator bobbing positions
uniform_real_distribution<double> distribution(0.000, 0.005);

Scene::Scene() {
    /* VERTEX ARRAY OBJECT GEOMETRIES */
    //Spectator shirt colours
    vec3 posRightCrowd(30.0f, 8.0f, -8.0f);
    vec3 red(1.0f, 0.0f, 0.0f);
    vec3 yellow(1.0f, 1.0f, 0.0f);
    vec3 purple(0.85f, 0.3f, 1.0f);
    vec3 green(0.0f, 1.0f, 0.0f);
    vec3 blue(0.0f, 0.0f, 1.0f);

    //spectators on bleacher right
    spect01 = Spectator(red, vec3(30.0f, 8.0f, -40.0f),  randYPos()); // test spectator
    spect02 = Spectator(blue, vec3(30.0f, 8.0f, -30.0f),  randYPos()); // test spectator
    spect03 = Spectator(green, vec3(30.0f, 8.0f, -20.0f),  randYPos()); // test spectator
    spect04 = Spectator(purple, vec3(30.0f, 8.0f, -10.0f),  randYPos()); // test spectator
    spect05 = Spectator(blue, vec3(30.0f, 8.0f, 0.0f),  randYPos()); // test spectator
    spect06 = Spectator(yellow, vec3(30.0f, 8.0f, 10.0f),  randYPos()); // test spectator
    spect07 = Spectator(red, vec3(30.0f, 8.0f, 20.0f),  randYPos()); // test spectator
    spect08 = Spectator(green, vec3(30.0f, 8.0f, 30.0f),  randYPos()); // test spectator
    spect09 = Spectator(purple, vec3(30.0f, 8.0f, 40.0f),  randYPos()); // test spectator
    spect10 = Spectator(yellow, vec3(30.0f, 8.0f, 50.0f),  randYPos()); // test spectator

    spect11 = Spectator(blue, vec3(40.0f, 14.0f, -40.0f),  randYPos()); // test spectator
    spect12 = Spectator(green, vec3(40.0f, 14.0f, -30.0f),  randYPos()); // test spectator
    spect13 = Spectator(yellow, vec3(40.0f, 14.0f, -20.0f),  randYPos()); // test spectator
    spect14 = Spectator(red, vec3(40.0f, 14.0f, -10.0f),  randYPos()); // test spectator
    spect15 = Spectator(green, vec3(40.0f, 14.0f, 0.0f),  randYPos()); // test spectator
    spect16 = Spectator(purple, vec3(40.0f, 14.0f, 10.0f),  randYPos()); // test spectator
    spect17 = Spectator(blue, vec3(40.0f, 14.0f, 20.0f),  randYPos()); // test spectator
    spect18 = Spectator(red, vec3(40.0f, 14.0f, 30.0f),  randYPos()); // test spectator
    spect19 = Spectator(green, vec3(40.0f, 14.0f, 40.0f),  randYPos()); // test spectator
    spect20 = Spectator(blue, vec3(40.0f, 14.0f, 50.0f),  randYPos()); // test spectator

    spect21 = Spectator(yellow, vec3(50.0f, 20.0f, -40.0f),  randYPos()); // test spectator
    spect22 = Spectator(red, vec3(50.0f, 20.0f, -30.0f),  randYPos()); // test spectator
    spect23 = Spectator(yellow, vec3(50.0f, 20.0f, -20.0f),  randYPos()); // test spectator
    spect24 = Spectator(green, vec3(50.0f, 20.0f, -10.0f),  randYPos()); // test spectator
    spect25 = Spectator(purple, vec3(50.0f, 20.0f, 0.0f),  randYPos()); // test spectator
    spect26 = Spectator(blue, vec3(50.0f, 20.0f, 10.0f),  randYPos()); // test spectator
    spect27 = Spectator(green, vec3(50.0f, 20.0f, 20.0f),  randYPos()); // test spectator
    spect28 = Spectator(red, vec3(50.0f, 20.0f, 30.0f),  randYPos()); // test spectator
    spect29 = Spectator(yellow, vec3(50.0f, 20.0f, 40.0f),  randYPos()); // test spectator
    spect30 = Spectator(green, vec3(50.0f, 20.0f, 50.0f),  randYPos()); // test spectator


    //spectators on bleacher left
    spect31 = Spectator(red, vec3(-30.0f, 8.0f, -40.0f),  randYPos()); // test spectator
    spect32 = Spectator(blue, vec3(-30.0f, 8.0f, -30.0f),  randYPos()); // test spectator
    spect33 = Spectator(green, vec3(-30.0f, 8.0f, -20.0f),  randYPos()); // test spectator
    spect34 = Spectator(purple, vec3(-30.0f, 8.0f, -10.0f),  randYPos()); // test spectator
    spect35 = Spectator(blue, vec3(-30.0f, 8.0f, 0.0f),  randYPos()); // test spectator
    spect36 = Spectator(yellow, vec3(-30.0f, 8.0f, 10.0f),  randYPos()); // test spectator
    spect37 = Spectator(red, vec3(-30.0f, 8.0f, 20.0f),  randYPos()); // test spectator
    spect38 = Spectator(green, vec3(-30.0f, 8.0f, 30.0f),  randYPos()); // test spectator
    spect39 = Spectator(purple, vec3(-30.0f, 8.0f, 40.0f),  randYPos()); // test spectator
    spect40 = Spectator(yellow, vec3(-30.0f, 8.0f, 50.0f),  randYPos()); // test spectator

    spect41 = Spectator(blue, vec3(-40.0f, 14.0f, -40.0f),  randYPos()); // test spectator
    spect42 = Spectator(green, vec3(-40.0f, 14.0f, -30.0f),  randYPos()); // test spectator
    spect43 = Spectator(yellow, vec3(-40.0f, 14.0f, -20.0f),  randYPos()); // test spectator
    spect44 = Spectator(red, vec3(-40.0f, 14.0f, -10.0f),  randYPos()); // test spectator
    spect45 = Spectator(green, vec3(-40.0f, 14.0f, 0.0f),  randYPos()); // test spectator
    spect46 = Spectator(purple, vec3(-40.0f, 14.0f, 10.0f),  randYPos()); // test spectator
    spect47 = Spectator(blue, vec3(-40.0f, 14.0f, 20.0f),  randYPos()); // test spectator
    spect48 = Spectator(red, vec3(-40.0f, 14.0f, 30.0f),  randYPos()); // test spectator
    spect49 = Spectator(green, vec3(-40.0f, 14.0f, 40.0f),  randYPos()); // test spectator
    spect50 = Spectator(blue, vec3(-40.0f, 14.0f, 50.0f),  randYPos()); // test spectator

    spect51 = Spectator(yellow, vec3(-50.0f, 20.0f, -40.0f),  randYPos()); // test spectator
    spect52 = Spectator(red, vec3(-50.0f, 20.0f, -30.0f),  randYPos()); // test spectator
    spect53 = Spectator(yellow, vec3(-50.0f, 20.0f, -20.0f),  randYPos()); // test spectator
    spect54 = Spectator(green, vec3(-50.0f, 20.0f, -10.0f),  randYPos()); // test spectator
    spect55 = Spectator(purple, vec3(-50.0f, 20.0f, 0.0f),  randYPos()); // test spectator
    spect56 = Spectator(blue, vec3(-50.0f, 20.0f, 10.0f),  randYPos()); // test spectator
    spect57 = Spectator(green, vec3(-50.0f, 20.0f, 20.0f),  randYPos()); // test spectator
    spect58 = Spectator(red, vec3(-50.0f, 20.0f, 30.0f),  randYPos()); // test spectator
    spect59 = Spectator(yellow, vec3(-50.0f, 20.0f, 40.0f),  randYPos()); // test spectator
    spect60 = Spectator(green, vec3(-50.0f, 20.0f, 50.0f),  randYPos()); // test spectator


    bleacherR = Bleacher(vec3(10.0f, 0.0f, 0.0f), 0.0f);
    bleacherL = Bleacher(vec3(10.0f, 0.0f, 0.0f), 180.0f);

    
    Cube cubeGeneric = Cube(vec3(1.0f, 1.0f, 1.0f));
    CubeInsideOut cubeSky = CubeInsideOut(vec3(3.0f/255.0f, 207.0f/255.0f, 252.0f/255.0f));
    Cube cubeGridline = Cube(vec3(1.0f, 1.0f, 0.0f));
    Cube cubeXAxis = Cube(vec3(1.0f, 0.0f, 0.0f));
    Cube cubeYAxis = Cube(vec3(0.0f, 1.0f, 0.0f));
    Cube cubeZAxis = Cube(vec3(0.0f, 0.0f, 1.0f));
    Cube cubeNetTwine = Cube(vec3(0.0f, 0.0f, 0.0f));
    Cube cubeRacketString = Cube(vec3(36.0f/255.0f, 156.0f/255.0f, 0.0f));

    // Define and upload cube geometry to the GPU
    this->vaoGeneric = cubeGeneric.getVertexBufferObject();
    this->vaoSky = cubeSky.getVertexBufferObject();
    this->vaoGridline = cubeGridline.getVertexBufferObject();
    this->vaoXAxis = cubeXAxis.getVertexBufferObject();
    this->vaoYAxis = cubeYAxis.getVertexBufferObject();
    this->vaoZAxis = cubeZAxis.getVertexBufferObject();
    this->vaoNetTwine = cubeNetTwine.getVertexBufferObject();
    this->vaoRacketString = cubeRacketString.getVertexBufferObject();

    /* TEXTURES */
    // Load textures
    this->skyTexture = Texture("../assets/textures/sky.jpg");
    this->netPostTexture = Texture("../assets/textures/net/post.jpg");
    this->netTopTexture = Texture("../assets/textures/net/top.jpg");
    this->armTattooTexture = Texture("../assets/textures/racket/tattoo.jpg");
    this->racketRedTexture = Texture("../assets/textures/racket/red.jpg");
    this->racketGreyTexture = Texture("../assets/textures/racket/grey.jpg");
    this->character1Texture.push_back(new Texture("../assets/textures/alphabet/blue1.jpg"));
    this->character1Texture.push_back(new Texture("../assets/textures/alphabet/blue2.jpg"));
    this->character1Texture.push_back(new Texture("../assets/textures/alphabet/blue3.jpg"));
    this->character2Texture.push_back(new Texture("../assets/textures/alphabet/green1.jpg"));
    this->character2Texture.push_back(new Texture("../assets/textures/alphabet/green2.jpg"));
    this->character2Texture.push_back(new Texture("../assets/textures/alphabet/green3.jpg"));
    this->character3Texture.push_back(new Texture("../assets/textures/alphabet/orange1.jpg"));
    this->character3Texture.push_back(new Texture("../assets/textures/alphabet/orange2.jpg"));
    this->character3Texture.push_back(new Texture("../assets/textures/alphabet/orange3.jpg"));
    this->character4Texture.push_back(new Texture("../assets/textures/alphabet/pink1.jpg"));
    this->character4Texture.push_back(new Texture("../assets/textures/alphabet/pink2.jpg"));
    this->character4Texture.push_back(new Texture("../assets/textures/alphabet/pink3.jpg"));

    /* TENNIS RACKET MODEL INSTANTIATION */
    this->model.push_back(new TennisRacketModel(vec3(0.0f, 8.0f, 20.0f)));
    this->model.push_back(new TennisRacketModel(vec3(0.0f, 8.0f, -20.0f)));

    /* CONTROL VARIABLE SETUP */
    this->worldRotationRate = 15.0f;

    this->renderingMode = GL_TRIANGLES; // default model rendering mode of GL_TRIANGLES

    this->isAlphaEnabled = true;
}

float Scene::getWorldRotationXAxis() {
    return this->worldRotationXAxis;
}

float Scene::getWorldRotationYAxis() {
    return this->worldRotationYAxis;
}

float Scene::getWorldRotationZAxis() {
    return this->worldRotationZAxis;
}

float Scene::getWorldRotationRate() {
    return this->worldRotationRate;
}

GLuint Scene::getRenderingMode() {
    return this->renderingMode;
}

bool Scene::getIsAlphaEnabled() {
    return this->isAlphaEnabled;
}

void Scene::setWorldRotationXAxis(float worldRotationXAxis) {
    this->worldRotationXAxis = worldRotationXAxis;
}

void Scene::setWorldRotationYAxis(float worldRotationYAxis) {
    this->worldRotationYAxis = worldRotationYAxis;
}

void Scene::setWorldRotationZAxis(float worldRotationZAxis) {
    this->worldRotationZAxis = worldRotationZAxis;
}

void Scene::setRenderingMode(GLuint renderingMode) {
    this->renderingMode = renderingMode;
}

void Scene::setIsAlphaEnabled(bool isAlphaEnabled) {
    this->isAlphaEnabled = isAlphaEnabled;
}

void Scene::drawScene(ShaderProgram shaderProgram) {
    /* HIERARCHICAL MODELLING */
    // This is the base/foundation matrix for the world
    mat4 worldMatrix = rotate(mat4(1.0f), radians(this->worldRotationZAxis), vec3(0.0f, 0.0f, 1.0f)) * rotate(mat4(1.0f), radians(this->worldRotationYAxis), vec3(0.0f, 1.0f, 0.0f)) * rotate(mat4(1.0f), radians(this->worldRotationXAxis), vec3(1.0f, 0.0f, 0.0f));

    // Declare reusable model matrix
    mat4 modelMatrix;

    // Create hierarchy matrices, one for each model copy
    mat4 hierarchyModelMatrix[2];
    for (int i=0; i<2; ++i) {
        hierarchyModelMatrix[i] = translate(mat4(1.0f), this->model.at(i)->getModelPosition()) * rotate(mat4(1.0f), radians(this->model.at(i)->getModelRotationZAxis()), vec3(0.0f, 0.0f, 1.0f)) * rotate(mat4(1.0f), radians(this->model.at(i)->getModelRotationYAxis()), vec3(0.0f, 1.0f, 0.0f)) * rotate(mat4(1.0f), radians(this->model.at(i)->getModelRotationXAxis()), vec3(1.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), this->model.at(i)->getModelScale());
        hierarchyModelMatrix[i] = worldMatrix * hierarchyModelMatrix[i];
    }

    // Activate textures
    shaderProgram.use();
    shaderProgram.setBool("isTexturesEnabled", shaderProgram.getIsTexturesEnabled());

    // Set initial alpha value
    shaderProgram.setFloat("alphaValue", 1.0f);

    // Model and draw sky cube
    // Bind the inside out cube's vao and corresponding texture
    glBindVertexArray(this->vaoSky);
    this->skyTexture.use();
    modelMatrix = translate(mat4(1.0f), vec3(0.0f, 40.1 / 2.0f - 0.1f, 0.0f)) * scale(mat4(1.0f), vec3(36.0f, 40.1f, 78.0f));
    modelMatrix = worldMatrix * modelMatrix;
    shaderProgram.setMat4("worldMatrix", modelMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Activate colors (deactivate textures)
    shaderProgram.use();
    shaderProgram.setBool("isTexturesEnabled", false);

    // Model and draw ground
    glBindVertexArray(this->vaoGeneric);
    modelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(36.0f, 0.02f, 78.0f));
    modelMatrix = worldMatrix * modelMatrix;
    shaderProgram.setMat4("worldMatrix", modelMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Model and draw gridlines for 78x36 grid
    glBindVertexArray(this->vaoGridline);
    for (int i=0; i<36; ++i) {
        modelMatrix = translate(mat4(1.0f), vec3(-18.0f + i * 1.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(0.02f, 0.02f, 78.0f));
        modelMatrix = worldMatrix * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    for (int i=0; i<78; ++i) {
        modelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, -39.0f + i * 1.0f)) * scale(mat4(1.0f), vec3(36.0f, 0.02f, 0.02f));
        modelMatrix = worldMatrix * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // Model and draw coordinate axes
    glBindVertexArray(this->vaoXAxis);
    modelMatrix = translate(mat4(1.0f), vec3(2.5f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(5.0f, 0.1f, 0.1f));
    modelMatrix = worldMatrix * modelMatrix;
    shaderProgram.setMat4("worldMatrix", modelMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(this->vaoYAxis);
    modelMatrix = translate(mat4(1.0f), vec3(0.0f, 2.5f, 0.0f)) * scale(mat4(1.0f), vec3(0.1f, 5.0f, 0.1f));
    modelMatrix = worldMatrix * modelMatrix;
    shaderProgram.setMat4("worldMatrix", modelMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(this->vaoZAxis);
    modelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 2.5f)) * scale(mat4(1.0f), vec3(0.1f, 0.1f, 5.0f));
    modelMatrix = worldMatrix * modelMatrix;
    shaderProgram.setMat4("worldMatrix", modelMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Activate textures
    shaderProgram.use();
    shaderProgram.setBool("isTexturesEnabled", shaderProgram.getIsTexturesEnabled());

    // Model and draw tennis net posts
    glBindVertexArray(this->vaoGeneric);
    this->netPostTexture.use();

    modelMatrix = translate(mat4(1.0f), vec3(-16.0f, 3.0f, 0.0f)) * scale(mat4(1.0f), vec3(1.0f, 6.0f, 1.0f));
    modelMatrix = worldMatrix * modelMatrix;
    shaderProgram.setMat4("worldMatrix", modelMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    modelMatrix = translate(mat4(1.0f), vec3(0.0f, 2.65f, 0.0f)) * scale(mat4(1.0f), vec3(1.0f, 5.3f, 0.3f));
    modelMatrix = worldMatrix * modelMatrix;
    shaderProgram.setMat4("worldMatrix", modelMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    modelMatrix = translate(mat4(1.0f), vec3(16.0f, 3.0f, 0.0f)) * scale(mat4(1.0f), vec3(1.0f, 6.0f, 1.0f));
    modelMatrix = worldMatrix * modelMatrix;
    shaderProgram.setMat4("worldMatrix", modelMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Model and draw tennis net top
    glBindVertexArray(this->vaoGeneric);
    this->netTopTexture.use();
    modelMatrix = translate(mat4(1.0f), vec3(0.0f, -0.35f + 6.0f, 0.0f)) * scale(mat4(1.0f), vec3(32.0f - 2.0f * 0.5f, 0.7f, 0.3f));
    modelMatrix = worldMatrix * modelMatrix;
    shaderProgram.setMat4("worldMatrix", modelMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Activate colors (deactivate textures)
    shaderProgram.use();
    shaderProgram.setBool("isTexturesEnabled", false);

    // Tennis net twine
    glBindVertexArray(this->vaoNetTwine);
    for (int i=0; i<13; ++i) {
        modelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.2f + i * 0.4f, 0.0f)) * scale(mat4(1.0f), vec3(32.0f - 2.0f * 0.5f, 0.04f, 0.04f));
        modelMatrix = worldMatrix * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    for (int i=0; i<77; ++i) {
        modelMatrix = translate(mat4(1.0f), vec3(-16.0f + 0.5f + 0.2f + i * 0.4f, (6.0f - 0.7f - 0.1f) / 2, 0.0f)) * scale(mat4(1.0f), vec3(0.04f, 6.0f - 0.7f - 2.0f * 0.2f - 0.1f, 0.04f));
        modelMatrix = worldMatrix * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // Model and draw tennis racket models (with arm)
    for (int n=0; n<2; ++n) {
        // Activate textures
        shaderProgram.use();
        shaderProgram.setBool("isTexturesEnabled", shaderProgram.getIsTexturesEnabled());

        // --- Model arm ---
        glBindVertexArray(this->vaoGeneric);
        this->armTattooTexture.use();

        // Model and draw upper arm
        modelMatrix = translate(mat4(1.0f), vec3(0.0f, 1.5f, 0.0f)) * rotate(mat4(1.0f), radians(45.0f), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(3.0f, 0.5f, 0.5f));
        modelMatrix = hierarchyModelMatrix[n] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        // Model and draw lower arm
        modelMatrix = translate(mat4(1.0f), vec3(0.0f, 1.5f,  0.0f)) * scale(mat4(1.0f), vec3(0.5f, 3.0f, 0.5f));
        hierarchyModelMatrix[n] = hierarchyModelMatrix[n] * translate(mat4(1.0f), vec3(1.0f, 2.37f, 0.0f)) * rotate(mat4(1.0f), radians(this->model.at(n)->getModelLowerarmRotationZAxis()), vec3(0.0f, 0.0f, 1.0f)) * rotate(mat4(1.0f), radians(this->model.at(n)->getModelLowerarmRotationYAxis()), vec3(0.0f, 1.0f, 0.0f)) * rotate(mat4(1.0f), radians(this->model.at(n)->getModelLowerarmRotationXAxis()), vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = hierarchyModelMatrix[n] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        // Model and draw hand
        modelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.5f,  0.0f)) * scale(mat4(1.0f), vec3(1.0f, 1.0f, 0.7f));
        hierarchyModelMatrix[n] = hierarchyModelMatrix[n] * translate(mat4(1.0f), vec3(0.0f, 3.0f, 0.0f)) * rotate(mat4(1.0f), radians(this->model.at(n)->getModelHandRotationZAxis()), vec3(0.0f, 0.0f, 1.0f)) * rotate(mat4(1.0f), radians(this->model.at(n)->getModelHandRotationYAxis()), vec3(0.0f, 1.0f, 0.0f)) * rotate(mat4(1.0f), radians(this->model.at(n)->getModelHandRotationXAxis()), vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = hierarchyModelMatrix[n] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        // --- Model tennis racket ---
        glBindVertexArray(this->vaoGeneric);

        // Tennis racket handle
        this->racketRedTexture.use();
        modelMatrix = translate(mat4(1.0f), vec3(0.0f, 1.25f, 0.0f)) * scale(mat4(1.0f), vec3(0.3f, 2.5f, 0.3f));
        hierarchyModelMatrix[n] = hierarchyModelMatrix[n] * translate(mat4(1.0f), vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = hierarchyModelMatrix[n] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        // Tennis racket bottom-left
        this->racketGreyTexture.use();
        modelMatrix = translate(mat4(1.0f), vec3((-1.5f + 0.3f) * cos(45.0f), 2.8f, 0.0f)) * rotate(mat4(1.0f), radians(45.0f), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(0.2f, 1.5f, 0.2f));
        modelMatrix = hierarchyModelMatrix[n] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        // Tennis racket bottom-right
        this->racketGreyTexture.use();
        modelMatrix = translate(mat4(1.0f), vec3((1.5f - 0.3f) * cos(45.0f), 2.8f, 0.0f)) * rotate(mat4(1.0f), radians(-45.0f), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(0.2f, 1.5f, 0.2f));
        modelMatrix = hierarchyModelMatrix[n] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        // Tennis racket bottom-brace
        this->racketRedTexture.use();
        modelMatrix = translate(mat4(1.0f), vec3(0.0f, 2.9f, 0.0f)) * scale(mat4(1.0f), vec3(1.3f, 0.15f, 0.15f));
        modelMatrix = hierarchyModelMatrix[n] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        // Tennis racket left
        this->racketRedTexture.use();
        modelMatrix = translate(mat4(1.0f), vec3(-1.5f * cos(45.0f) - 0.3f, 2.8f + 1.7f, 0.0f)) * scale(mat4(1.0f), vec3(0.2f, 2.5f, 0.2f));
        modelMatrix = hierarchyModelMatrix[n] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        // Tennis racket right
        this->racketRedTexture.use();
        modelMatrix = translate(mat4(1.0f), vec3(1.5f * cos(45.0f) + 0.3f, 2.8f + 1.7f, 0.0f)) * scale(mat4(1.0f), vec3(0.2f, 2.5f, 0.2f));
        modelMatrix = hierarchyModelMatrix[n] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        // Tennis racket top left lower
        this->racketGreyTexture.use();
        modelMatrix = translate(mat4(1.0f), vec3(-1.0f, 2.8f + 1.7f + 1.35f, 0.0f)) * rotate(mat4(1.0f), radians(-40.0f), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(0.2f, 0.4f, 0.2f));
        modelMatrix = hierarchyModelMatrix[n] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        // Tennis racket top right lower
        this->racketGreyTexture.use();
        modelMatrix = translate(mat4(1.0f), vec3(1.0f, 2.8f + 1.7f + 1.35f, 0.0f)) * rotate(mat4(1.0f), radians(40.0f), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(0.2f, 0.4f, 0.2f));
        modelMatrix = hierarchyModelMatrix[n] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        // Tennis racket top left upper
        this->racketRedTexture.use();
        modelMatrix = translate(mat4(1.0f), vec3(-0.7f, 2.8f + 1.7f + 1.35f + 0.25f, 0.0f)) * rotate(mat4(1.0f), radians(-65.0f), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(0.2f, 0.4f, 0.2f));
        modelMatrix = hierarchyModelMatrix[n] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        // Tennis racket top right upper
        this->racketRedTexture.use();
        modelMatrix = translate(mat4(1.0f), vec3(0.7f, 2.8f + 1.7f + 1.35f + 0.25f, 0.0f)) * rotate(mat4(1.0f), radians(65.0f), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(0.2f, 0.4f, 0.2f));
        modelMatrix = hierarchyModelMatrix[n] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        // Tennis racket top
        this->racketGreyTexture.use();
        modelMatrix = translate(mat4(1.0f), vec3(0.0f, 2.8f + 1.7f + 1.35f + 0.25f + 0.1f, 0.0f)) * scale(mat4(1.0f), vec3(1.1f, 0.2f, 0.2f));
        modelMatrix = hierarchyModelMatrix[n] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        // Activate colors (deactivate textures)
        shaderProgram.use();
        shaderProgram.setBool("isTexturesEnabled", false);

        // Tennis racket strings
        glBindVertexArray(this->vaoRacketString);
        for (int i=0; i<7; ++i) {
            modelMatrix = translate(mat4(1.0f), vec3(-0.8f + i * 0.27f, 3.0f + 1.55f, 0.0f)) * scale(mat4(1.0f), vec3(0.06f, 3.2f, 0.06f));
            modelMatrix = hierarchyModelMatrix[n] * modelMatrix;
            shaderProgram.setMat4("worldMatrix", modelMatrix);
            glDrawArrays(this->renderingMode, 0, 36);
        }
        for (int i=0; i<11; ++i) {
            modelMatrix = translate(mat4(1.0f), vec3(0.0f, -1.4f + i * 0.27f + 3.0f + 1.55f, 0.0f)) * scale(mat4(1.0f), vec3(2.2f, 0.06f, 0.06f));
            modelMatrix = hierarchyModelMatrix[n] * modelMatrix;
            shaderProgram.setMat4("worldMatrix", modelMatrix);
            glDrawArrays(this->renderingMode, 0, 36);
        }
    }

    // Model and draw alphabet characters
    glBindVertexArray(this->vaoGeneric);

    // Activate textures
    shaderProgram.use();
    shaderProgram.setBool("isTexturesEnabled", shaderProgram.getIsTexturesEnabled());

    // Set alpha value for modelling characters if transparency is enabled
    if (this->isAlphaEnabled) {
        shaderProgram.setFloat("alphaValue", 0.6f);
    }

    // Model and draw first "H" character above first tennis racket model
    hierarchyModelMatrix[0] = hierarchyModelMatrix[0] * translate(mat4(1.0f), vec3(-1.25f, 8.0f, 0.0f));
    for (int i=0; i<3; ++i) {
        this->character1Texture.at(i)->use();

        modelMatrix = translate(mat4(1.0f), vec3(-0.75f, 1.25f, 0.6f - i * 0.6f)) * scale(mat4(1.0f), vec3(0.3f, 2.5f, 0.3f));
        modelMatrix = hierarchyModelMatrix[0] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        modelMatrix = translate(mat4(1.0f), vec3(0.75f, 1.25f, 0.6f - i * 0.6f)) * scale(mat4(1.0f), vec3(0.3f, 2.5f, 0.3f));
        modelMatrix = hierarchyModelMatrix[0] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        modelMatrix = translate(mat4(1.0f), vec3(0.0f, 1.25f, 0.6f - i * 0.6f)) * scale(mat4(1.0f), vec3(1.5f - 0.3f, 0.3f, 0.3f));
        modelMatrix = hierarchyModelMatrix[0] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);
    }

    // Model and draw second "U" character above first tennis racket model
    hierarchyModelMatrix[0] = hierarchyModelMatrix[0] * translate(mat4(1.0f), vec3(2.5f, 0.0f, 0.0f));
    for (int i=0; i<3; ++i) {
        this->character2Texture.at(i)->use();

        modelMatrix = translate(mat4(1.0f), vec3(-0.75f, 1.25f, 0.6f - i * 0.6f)) * scale(mat4(1.0f), vec3(0.3f, 2.5f, 0.3f));
        modelMatrix = hierarchyModelMatrix[0] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        modelMatrix = translate(mat4(1.0f), vec3(0.75f, 1.25f, 0.6f - i * 0.6f)) * scale(mat4(1.0f), vec3(0.3f, 2.5f, 0.3f));
        modelMatrix = hierarchyModelMatrix[0] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        modelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.3f / 2.0f, 0.6f - i * 0.6f)) * scale(mat4(1.0f), vec3(1.5f - 0.3f, 0.3f, 0.3f));
        modelMatrix = hierarchyModelMatrix[0] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);
    }

    // Model and draw third "B" character above second tennis racket model
    hierarchyModelMatrix[1] = hierarchyModelMatrix[1] * translate(mat4(1.0f), vec3(-1.25f, 8.0f, 0.0f));
    for (int i=0; i<3; ++i) {
        this->character3Texture.at(i)->use();

        modelMatrix = translate(mat4(1.0f), vec3(-0.75f, 1.25f, 0.6f - i * 0.6f)) * scale(mat4(1.0f), vec3(0.3f, 2.5f, 0.3f));
        modelMatrix = hierarchyModelMatrix[1] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        modelMatrix = translate(mat4(1.0f), vec3(0.0f, 2.5f - 0.3f / 2.0f, 0.6f - i * 0.6f)) * scale(mat4(1.0f), vec3(1.5f - 0.3f, 0.3f, 0.3f));
        modelMatrix = hierarchyModelMatrix[1] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        modelMatrix = translate(mat4(1.0f), vec3(0.0f, 1.25f, 0.6f - i * 0.6f)) * scale(mat4(1.0f), vec3(1.5f - 0.3f, 0.3f, 0.3f));
        modelMatrix = hierarchyModelMatrix[1] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        modelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.3f / 2.0f, 0.6f - i * 0.6f)) * scale(mat4(1.0f), vec3(1.5f - 0.3f, 0.3f, 0.3f));
        modelMatrix = hierarchyModelMatrix[1] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        modelMatrix = translate(mat4(1.0f), vec3(0.75f, 2.5f - 0.55f, 0.6f - i * 0.6f)) * scale(mat4(1.0f), vec3(0.3f, 1.1f, 0.3f));
        modelMatrix = hierarchyModelMatrix[1] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        modelMatrix = translate(mat4(1.0f), vec3(0.75f, 0.55f, 0.6f - i * 0.6f)) * scale(mat4(1.0f), vec3(0.3f, 1.1f, 0.3f));
        modelMatrix = hierarchyModelMatrix[1] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);
    }

    // Model and draw fourth "E" character above second tennis racket model
    hierarchyModelMatrix[1] = hierarchyModelMatrix[1] * translate(mat4(1.0f), vec3(2.5f, 0.0f, 0.0f));
    for (int i=0; i<3; ++i) {
        this->character4Texture.at(i)->use();

        modelMatrix = translate(mat4(1.0f), vec3(-0.75f, 1.25f, 0.6f - i * 0.6f)) * scale(mat4(1.0f), vec3(0.3f, 2.5f, 0.3f));
        modelMatrix = hierarchyModelMatrix[1] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        modelMatrix = translate(mat4(1.0f), vec3(0.0f, 2.5f - 0.3f / 2.0f, 0.6f - i * 0.6f)) * scale(mat4(1.0f), vec3(1.5f - 0.3f, 0.3f, 0.3f));
        modelMatrix = hierarchyModelMatrix[1] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        modelMatrix = translate(mat4(1.0f), vec3(0.0f, 1.25f, 0.6f - i * 0.6f)) * scale(mat4(1.0f), vec3(1.5f - 0.3f, 0.3f, 0.3f));
        modelMatrix = hierarchyModelMatrix[1] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);

        modelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.3f / 2.0f, 0.6f - i * 0.6f)) * scale(mat4(1.0f), vec3(1.5f - 0.3f, 0.3f, 0.3f));
        modelMatrix = hierarchyModelMatrix[1] * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(this->renderingMode, 0, 36);
    }

    //spectators on bleacher right
    spect01.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect02.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect03.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect04.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect05.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect06.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect07.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect08.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect09.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    //spect10.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);

    spect11.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect12.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect13.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect14.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect15.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect16.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect17.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect18.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect19.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    //spect20.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);

    spect21.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect22.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect23.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect24.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect25.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect26.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect27.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect28.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect29.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    //spect30.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);


    //spectators on bleacher left
    spect31.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect32.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect33.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect34.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect35.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect36.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect37.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect38.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect39.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    //spect40.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);

    spect41.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect42.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect43.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect44.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect45.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect46.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect47.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect48.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect49.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    //spect50.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);

    spect51.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect52.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect53.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect54.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect55.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect56.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect57.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect58.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    spect59.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);
    //spect60.draw(worldMatrix, shaderProgram,  rotation, this->ySpectPos);

    bleacherR.draw(worldMatrix, shaderProgram);
    bleacherL.draw(worldMatrix, shaderProgram);

    // Unbind any vao
    glBindVertexArray(0);

    //Model and draw the referee chair
    glBindVertexArray(this->vaoGeneric);
    //rails
    //front right
        modelMatrix = translate(mat4(1.0f), vec3(0.0f, 10.0f, 0.0f)) * 
                        rotate(mat4(1.0f), radians(20.0f), vec3(0.0f, 0.0f, 1.0f)) *
                        scale(mat4(1.0f), vec3(2.0f, 20.0f, 0.5f));
        modelMatrix = worldMatrix * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        modelMatrix = translate(mat4(1.0f), vec3(0.0f, 10.0f, 5.0f)) * 
                        rotate(mat4(1.0f), radians(20.0f), vec3(0.0f, 0.0f, 1.0f)) *
                        scale(mat4(1.0f), vec3(2.0f, 20.0f, 0.5f));
        modelMatrix = worldMatrix * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        modelMatrix = translate(mat4(1.0f), vec3(-6.0f, 10.0f, 0.0f)) * 
                        rotate(mat4(1.0f), radians(-20.0f), vec3(0.0f, 0.0f, 1.0f)) *
                        scale(mat4(1.0f), vec3(2.0f, 20.0f, 0.5f));
        modelMatrix = worldMatrix * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        modelMatrix = translate(mat4(1.0f), vec3(-6.0f, 10.0f, 5.0f)) * 
                        rotate(mat4(1.0f), radians(-20.0f), vec3(0.0f, 0.0f, 1.0f)) *
                        scale(mat4(1.0f), vec3(2.0f, 20.0f, 0.5f));
        modelMatrix = worldMatrix * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

    //steps
        modelMatrix = translate(mat4(1.0f), vec3(2.5f, 3.0f, 2.5f)) * 
                        scale(mat4(1.0f), vec3(2.0f, 0.5f, 5.0f));
        modelMatrix = worldMatrix * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        modelMatrix = translate(mat4(1.0f), vec3(1.5f, 6.0f, 2.5f)) * 
                        scale(mat4(1.0f), vec3(2.0f, 0.5f, 5.0f));
        modelMatrix = worldMatrix * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        modelMatrix = translate(mat4(1.0f), vec3(0.4f, 9.0f, 2.5f)) * 
                        scale(mat4(1.0f), vec3(2.0f, 0.5f, 5.0f));
        modelMatrix = worldMatrix * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        modelMatrix = translate(mat4(1.0f), vec3(-0.7f, 12.0f, 2.5f)) * 
                        scale(mat4(1.0f), vec3(2.0f, 0.5f, 5.0f));
        modelMatrix = worldMatrix * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //seat
        modelMatrix = translate(mat4(1.0f), vec3(-3.0f, 17.0f, 2.5f)) * 
                        scale(mat4(1.0f), vec3(4.0f, 0.5f, 5.0f));
        modelMatrix = worldMatrix * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //backrest
        modelMatrix = translate(mat4(1.0f), vec3(-5.3f, 22.0f, 2.5f)) * 
                        rotate(mat4(1.0f), radians(10.0f), vec3(0.0f, 0.0f, 1.0f)) *
                        scale(mat4(1.0f), vec3(0.5f, 2.0f, 5.0f));
        modelMatrix = worldMatrix * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //backrest support left
        modelMatrix = translate(mat4(1.0f), vec3(-5.0f, 20.0f, 0.0f)) * 
                        rotate(mat4(1.0f), radians(10.0f), vec3(0.0f, 0.0f, 1.0f)) *
                        scale(mat4(1.0f), vec3(0.8f, 6.0f, 0.5f));
        modelMatrix = worldMatrix * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //backrest support right
        modelMatrix = translate(mat4(1.0f), vec3(-5.0f, 20.0f, 5.0f)) * 
                        rotate(mat4(1.0f), radians(10.0f), vec3(0.0f, 0.0f, 1.0f)) *
                        scale(mat4(1.0f), vec3(0.8f, 6.0f, 0.5f));
        modelMatrix = worldMatrix * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //armrest support right
        modelMatrix = translate(mat4(1.0f), vec3(-2.0f, 19.5f, 5.0f)) * 
                        scale(mat4(1.0f), vec3(5.0f, 1.0f, 0.7f));
        modelMatrix = worldMatrix * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //armrest support left
        modelMatrix = translate(mat4(1.0f), vec3(-2.0f, 19.5f, 0.0f)) * 
                        scale(mat4(1.0f), vec3(5.0f, 1.0f, 0.7f));
        modelMatrix = worldMatrix * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //rear leg supports
        modelMatrix = translate(mat4(1.0f), vec3(-5.0f, 14.5f, 2.5f)) * 
                        rotate(mat4(1.0f), radians(-20.0f), vec3(0.0f, 0.0f, 1.0f)) *
                        scale(mat4(1.0f), vec3(0.5f, 1.0f, 5.0f));
        modelMatrix = worldMatrix * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        modelMatrix = translate(mat4(1.0f), vec3(-6.3f, 10.5f, 2.5f)) * 
                        rotate(mat4(1.0f), radians(-20.0f), vec3(0.0f, 0.0f, 1.0f)) *
                        scale(mat4(1.0f), vec3(0.5f, 1.0f, 5.0f));
        modelMatrix = worldMatrix * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        modelMatrix = translate(mat4(1.0f), vec3(-7.8f, 6.5f, 2.5f)) * 
                        rotate(mat4(1.0f), radians(-20.0f), vec3(0.0f, 0.0f, 1.0f)) *
                        scale(mat4(1.0f), vec3(0.5f, 1.0f, 5.0f));
        modelMatrix = worldMatrix * modelMatrix;
        shaderProgram.setMat4("worldMatrix", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

    // Set alpha value back to initial
    shaderProgram.setFloat("alphaValue", 1.0f);
}

float Scene::randYPos(){

    float temp = distribution(gen);
    //cout << "variance " << (temp) << endl;
    return (temp);
}
