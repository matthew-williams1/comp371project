#ifndef PROJECT_SCENE_H
#define PROJECT_SCENE_H

#include "ShaderProgram.h"
#include "Texture.h"
#include "TennisRacketModel.h"
#include "Spectator.h"
#include "Bleacher.h"
#include <random>

#include <vector>
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices

using namespace std;

class Scene {
private:
    /* MODELLING VARIABLES */
    GLuint vaoGeneric;
    GLuint vaoSky;
    GLuint vaoGridline;
    GLuint vaoXAxis;
    GLuint vaoYAxis;
    GLuint vaoZAxis;
    GLuint vaoNetTwine;
    GLuint vaoRacketString;
    Bleacher bleacherR;
    Bleacher bleacherL;

    //spectators on bleacher right
    Spectator spect01;
    Spectator spect02;
    Spectator spect03;
    Spectator spect04;
    Spectator spect05;
    Spectator spect06;
    Spectator spect07;
    Spectator spect08;
    Spectator spect09;
    Spectator spect10;

    Spectator spect11;
    Spectator spect12;
    Spectator spect13;
    Spectator spect14;
    Spectator spect15;
    Spectator spect16;
    Spectator spect17;
    Spectator spect18;
    Spectator spect19;
    Spectator spect20;

    Spectator spect21;
    Spectator spect22;
    Spectator spect23;
    Spectator spect24;
    Spectator spect25;
    Spectator spect26;
    Spectator spect27;
    Spectator spect28;
    Spectator spect29;
    Spectator spect30;

    //spectators on bleacher left
    Spectator spect31;
    Spectator spect32;
    Spectator spect33;
    Spectator spect34;
    Spectator spect35;
    Spectator spect36;
    Spectator spect37;
    Spectator spect38;
    Spectator spect39;
    Spectator spect40;

    Spectator spect41;
    Spectator spect42;
    Spectator spect43;
    Spectator spect44;
    Spectator spect45;
    Spectator spect46;
    Spectator spect47;
    Spectator spect48;
    Spectator spect49;
    Spectator spect50;

    Spectator spect51;
    Spectator spect52;
    Spectator spect53;
    Spectator spect54;
    Spectator spect55;
    Spectator spect56;
    Spectator spect57;
    Spectator spect58;
    Spectator spect59;
    Spectator spect60;

    Texture skyTexture;
    Texture netPostTexture;
    Texture netTopTexture;
    Texture armTattooTexture;
    Texture racketRedTexture;
    Texture racketGreyTexture;
    vector<Texture *> character1Texture;
    vector<Texture *> character2Texture;
    vector<Texture *> character3Texture;
    vector<Texture *> character4Texture;

    /* WORLD CONTROL VARIABLES */
    float worldRotationXAxis = 0.0f; // default X-rotation of 0
    float worldRotationYAxis = 0.0f; // default Y-rotation of 0
    float worldRotationZAxis = 0.0f; // default Z-rotation of 0
    float worldRotationRate;

    /* RENDER CONTROL VARIABLE */
    GLuint renderingMode;
    bool isAlphaEnabled;

public:
    vector<TennisRacketModel *> model;

    Scene();

    void drawScene(ShaderProgram shaderProgram);

    // Accessors
    float getWorldRotationXAxis();

    float getWorldRotationYAxis();

    float getWorldRotationZAxis();

    float getWorldRotationRate();

    GLuint getRenderingMode();

    bool getIsAlphaEnabled();

    // Mutators
    void setWorldRotationXAxis(float worldRotationXAxis);

    void setWorldRotationYAxis(float worldRotationYAxis);

    void setWorldRotationZAxis(float worldRotationZAxis);

    void setRenderingMode(GLuint renderingMode);

    void setIsAlphaEnabled(bool isAlphaEnabled);

    // Spectator control functions
    float randYPos();

    void setSpectatorArms(float rot);

    /* SPECTATOR CONTROL VARIABLES */
    float ySpectPos;
    float rotation;

    // random number generator
    default_random_engine gen;
};

#endif //PROJECT_SCENE_H
