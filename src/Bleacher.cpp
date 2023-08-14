#include "Bleacher.h"
#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

Bleacher::Bleacher(vec3 pos, float dir){
    vec3 color(207.0f/255.0f, 185.0f/255.0f, 151.0f/255.0f);
    Cube plank = Cube (color);
    position = pos;
    direction = dir;

    bleacherWidePlankVAO = plank.getVertexBufferObject();

    //seatText = Texture("/Users/mathew/code/assets/textures/bleachers/aluminium_bleacher.jpeg"); //loading these textures causes inconsistent seg fault 
    //woodText = Texture("/Users/mathew/code/assets/textures/bleachers/wood.jpeg");
};

void Bleacher::draw(mat4 hierarchyModelMatrix, ShaderProgram shaderProgram){
    mat4 worldMatrix;
    mat4 groupMatrix = hierarchyModelMatrix * rotate(mat4(1.0f), radians(direction), vec3(0.0f, 1.0f, 0.0f));

    //bottom seat plank
    glBindVertexArray(bleacherWidePlankVAO);
    //shaderProgram.useTextures();
    //seatText.use();
    mat4 partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(20.0f, 3.0f, 0.0f)) * 
                        scale(mat4(1.0f), vec3(5.0f, 1.0f, 88.0f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //middle seat plank
    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(30.0f, 9.0f, 0.0f)) * 
                        scale(mat4(1.0f), vec3(5.0f, 1.0f, 88.0f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //top seat plank
    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(40.0f, 15.0f, 0.0f)) * 
                        scale(mat4(1.0f), vec3(5.0f, 1.0f, 88.0f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //guardrails
    //top far
    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(31.0f, 25.0f, -44.0f)) * 
                        scale(mat4(1.0f), vec3(22.5f, 0.5f, 0.5f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //top close
    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(31.0f, 25.0f, 44.0f)) * 
                        scale(mat4(1.0f), vec3(22.5f, 0.5f, 0.5f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //top back
    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(42.0f, 25.0f, 0.0f)) * 
                        scale(mat4(1.0f), vec3(0.5f, 0.5f, 90.0f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    float xpos_back = -40.0f;
    float xpos_far = 20.0f;
    float xpos = 20.0f;

    //far side guardrails
    for (int i = 0; i < 8; i++){
    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(xpos, 12.4f, -44.0f)) * 
                        scale(mat4(1.0f), vec3(0.5f, 25.0f, 0.5f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);
        xpos = 3.0f + xpos;
    }

    //close side guardrails
    for (int i = 0; i < 8; i++){
    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(xpos_far, 12.4f, 44.0f)) * 
                        scale(mat4(1.0f), vec3(0.5f, 25.0f, 0.5f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);
        xpos_far = 3.0f + xpos_far;
    }

    //back side guardrails
    for (int i = 0; i < 28; i++){
    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(42.0f, 13.5f, xpos_back)) * 
                        scale(mat4(1.0f), vec3(0.5f, 23.0f, 0.5f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    xpos_back += 3.0f;
    }



    //far ground support
    //shaderProgram.useTextures();
    //woodText.use();
    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(30.0f, 0.0f, -44.0f)) * 
                        scale(mat4(1.0f), vec3(20.0f, 1.5f, 1.0f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //close ground support
    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(30.0f, 0.0f, 44.0f)) * 
                        scale(mat4(1.0f), vec3(20.0f, 1.5f, 1.0f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //support from middle seat plank on far side
    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(30.0f, 4.0f, -44.0f)) * 
                        scale(mat4(1.0f), vec3(2.0f, 9.0f, 2.0f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //support from middle seat plank in the middle
    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(30.0f, 4.0f, 0.0f)) * 
                        scale(mat4(1.0f), vec3(2.0f, 9.0f, 2.0f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //support from middle seat plank on close side
    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(30.0f, 4.0f, 44.0f)) * 
                        scale(mat4(1.0f), vec3(2.0f, 9.0f, 2.0f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //support from the bottom seat plank on far side
    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(20.0f, 1.0f, -44.0f)) * 
                        scale(mat4(1.0f), vec3(2.0f, 3.3f, 2.0f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //support from the bottom seat plank on close side
    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(20.0f, 1.0f, 44.0f)) * 
                        scale(mat4(1.0f), vec3(2.0f, 3.3f, 2.0f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //support from the bottom seat plank in the middle
    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(20.0f, 1.0f, 0.0f)) * 
                        scale(mat4(1.0f), vec3(2.0f, 3.3f, 2.0f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //support from the top seat plank on far side
    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(40.0f, 7.3f, -44.0f)) * 
                        scale(mat4(1.0f), vec3(2.0f, 16.0f, 2.0f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //support from the top seat plank on close side
    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(40.0f, 7.3f, 44.0f)) * 
                        scale(mat4(1.0f), vec3(2.0f, 16.0f, 2.0f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //support from the top seat plank in the middle
    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(40.0f, 7.3f, 0.0f)) * 
                        scale(mat4(1.0f), vec3(2.0f, 16.0f, 2.0f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //cross braces
    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(40.0f, 7.3f, -22.0f)) * 
                        rotate(mat4(1.0f), radians(72.0f), vec3(1.0f, 0.0f, 0.0f)) *
                        scale(mat4(1.0f), vec3(2.0f, 45.0f, 2.0f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(40.0f, 7.3f, -22.0f)) * 
                        rotate(mat4(1.0f), radians(-72.0f), vec3(1.0f, 0.0f, 0.0f)) *
                        scale(mat4(1.0f), vec3(2.0f, 45.0f, 2.0f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(40.0f, 7.3f, 22.0f)) * 
                        rotate(mat4(1.0f), radians(72.0f), vec3(1.0f, 0.0f, 0.0f)) *
                        scale(mat4(1.0f), vec3(2.0f, 45.0f, 2.0f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    partMatrix = translate(mat4(1.0f), position) * 
                        translate(mat4(1.0f), vec3(40.0f, 7.3f, 22.0f)) * 
                        rotate(mat4(1.0f), radians(-72.0f), vec3(1.0f, 0.0f, 0.0f)) *
                        scale(mat4(1.0f), vec3(2.0f, 45.0f, 2.0f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);




}
Bleacher::Bleacher(){};
