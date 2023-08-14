#ifndef PROJECT_TENNISRACKETMODEL_H
#define PROJECT_TENNISRACKETMODEL_H

#include <glm/glm.hpp>

using namespace glm;

class TennisRacketModel {
private:
    /* MODEL CONTROL VARIABLES */
    vec3 modelPosition;
    float modelRotationXAxis;
    float modelRotationYAxis;
    float modelRotationZAxis;
    float modelLowerarmRotationXAxis;
    float modelLowerarmRotationYAxis;
    float modelLowerarmRotationZAxis;
    float modelHandRotationXAxis;
    float modelHandRotationYAxis;
    float modelHandRotationZAxis;
    vec3 modelScale;
    float modelDisplacementRate;
    float modelRotationRate;
    float modelScaleRate;
public:
    TennisRacketModel(const vec3 &position);

    // Accessors
    vec3 getModelPosition() const;

    float getModelRotationXAxis() const;

    float getModelRotationYAxis() const;

    float getModelRotationZAxis() const;

    float getModelLowerarmRotationXAxis() const;

    float getModelLowerarmRotationYAxis() const;

    float getModelLowerarmRotationZAxis() const;

    float getModelHandRotationXAxis() const;

    float getModelHandRotationYAxis() const;

    float getModelHandRotationZAxis() const;

    vec3 getModelScale() const;

    float getModelDisplacementRate() const;

    float getModelRotationRate() const;

    float getModelScaleRate() const;

    // Mutators
    void setModelPosition(const vec3 &position);

    void setModelRotationXAxis(float rotation);

    void setModelRotationYAxis(float rotation);

    void setModelRotationZAxis(float rotation);

    void setModelLowerarmRotationXAxis(float rotation);

    void setModelLowerarmRotationYAxis(float rotation);

    void setModelLowerarmRotationZAxis(float rotation);

    void setModelHandRotationXAxis(float rotation);

    void setModelHandRotationYAxis(float rotation);

    void setModelHandRotationZAxis(float rotation);

    void setModelScale(const vec3 &scale);

    void setModelDisplacementRate(float rate);

    void setModelRotationRate(float rate);

    void setModelScaleRate(float rate);
};

#endif //PROJECT_TENNISRACKETMODEL_H