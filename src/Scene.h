#ifndef QUIZ_2_SCENE_H
#define QUIZ_2_SCENE_H

#include "ShaderProgram.h"
#include "Texture.h"
#include "TennisRacketModel.h"

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
};

#endif //QUIZ_2_SCENE_H