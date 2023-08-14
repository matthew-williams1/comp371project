#include "Spectator.h"
#include <iostream>
using namespace std;
Spectator::Spectator(){};

Spectator::Spectator(vec3 col, vec3 pos, float variance){
    vec3 beige(207.0f/255.0f, 185.0f/255.0f, 151.0f/255.0f);
    Cube spectatorBody =  Cube(col);
    Cube spectatorHead =  Cube(beige);
    Cube spectatorLeftArm =  Cube(beige);
    Cube spectatorRightArm =  Cube(beige);
    position = pos;
    var = variance;
    isDrawn = false;

    spectatorBodyVAO = spectatorBody.getVertexBufferObject();
    spectatorHeadVAO = spectatorHead.getVertexBufferObject();
    spectatorLeftArmVAO = spectatorLeftArm.getVertexBufferObject();
    spectatorRightArmVAO = spectatorRightArm.getVertexBufferObject();
};

void Spectator::draw(mat4 hierarchyModelMatrix, ShaderProgram shaderProgram, float rotation, float dtpos) {
    mat4 worldMatrix;
    mat4 groupMatrix = hierarchyModelMatrix;

    glm::vec3 target = {0.0f, 0.0f, 0.0f};

    vec3 direction = glm::normalize(target - position);
    vec3 up = vec3(0.0f, 1.0f, 0.0f); // Up vector
    vec3 right = glm::normalize(glm::cross(direction, up));
    up = cross(right, direction);

    mat4 rotationMatrix = glm::mat4(
    right.x, right.y, right.z, 0,
    up.x, up.y, up.z, 0,
    direction.x, direction.y, direction.z, 0,
    0, 0, 0, 1
);

    glBindVertexArray(spectatorBodyVAO);
    mat4 partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f)) * 
                        scale(mat4(1.0f), vec3(0.3f, 8.0f, 4.0f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    glBindVertexArray(spectatorHeadVAO);
    partMatrix = translate(mat4(1.0f), position) * 
                    translate(mat4(1.0f), vec3(0.0f, 7.0f, 0.0f)) * 
                    rotationMatrix *
                    scale(mat4(1.0f), vec3(3.2f, 3.2f, 0.3f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(spectatorLeftArmVAO);
    partMatrix = translate(mat4(1.0f), vec3(0.0f, 0.5f, 0.5f)) * 
                    translate(mat4(1.0f), position) * 
                    translate(mat4(1.0f), vec3(0.0f, 2.2f, -2.3f)) * 
                    rotate(mat4(1.0f), radians(rotation), vec3(1.0f, 0.0f, 0.0f))*
                    scale(mat4(1.0f), vec3(0.18f, 5.2f, 1.2f));
    worldMatrix = groupMatrix  * partMatrix*translate(mat4(1.0f), vec3(0.0f, -0.3f, -0.3f));
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(spectatorRightArmVAO);
    partMatrix = translate(mat4(1.0f), vec3(0.0f, 0.2f, 0.5f)) * 
                    translate(mat4(1.0f), position) * 
                    translate(mat4(1.0f), vec3(0.0f, 2.6f, 1.2f)) * 
                    rotate(mat4(1.0f), radians(-rotation), vec3(1.0f, 0.0f, 0.0f)) *
                    scale(mat4(1.0f), vec3(0.18f, 5.2f, 1.2f));

    worldMatrix = groupMatrix * partMatrix * translate(mat4(1.0f), vec3(0.0f, -0.3f, 0.4f));
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);
 
    if (!isDrawn){

    position += vec3(0.0f, (dtpos - var), 0.0f);
    isDrawn = true;
    cout << "get drawn: " << (dtpos - var) << endl;

    }
    else {

        position += vec3(0.0f, (dtpos), 0.0f);
        cout << "dtpos: " << dtpos << endl;

    }
    cout << "rotation: " << rotation << endl; 
    cout << "dtpos: "<< dtpos << endl;
}
