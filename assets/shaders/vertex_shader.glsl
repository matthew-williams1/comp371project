#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aUV;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);
uniform vec3 lightPosPointlight;
uniform vec3 lightPosSpotlight1;
uniform vec3 lightPosSpotlight2;
uniform mat4 lightSpaceMatrix;

out vec3 fragPos;
out vec3 vertexColor;
out vec3 normal;
out vec2 vertexUV;
out vec3 eyeDir;
out vec3 lightDirPointlight;
out vec3 lightDirSpotlight1;
out vec3 lightDirSpotlight2;
out vec4 fragPosLightSpace;

void main() {
    // General
    vertexColor = aColor;
    mat4 modelViewProjection = projectionMatrix * viewMatrix * worldMatrix;
    gl_Position = modelViewProjection * vec4(aPos, 1.0);
    vertexUV = aUV;
    normal = mat3(transpose(inverse(worldMatrix))) * aNormal;
    fragPos = vec3(worldMatrix * vec4(aPos, 1.0));

    vec3 fragPos_cameraspace = (viewMatrix * worldMatrix * vec4(aPos, 1.0)).xyz;
    eyeDir = vec3(0.0, 0.0, 0.0) - fragPos_cameraspace;

    // Pointlight (casting shadows)
    vec3 lightPosPointlight_cameraspace = (viewMatrix * vec4(lightPosPointlight, 1.0)).xyz;
    lightDirPointlight = lightPosPointlight_cameraspace - fragPos_cameraspace;
    fragPosLightSpace = lightSpaceMatrix * vec4(fragPos, 1.0);

    // Spotlight1
    lightDirSpotlight1 = vec3(0.0, 0.0, 1.0);

    // Spotlight2
    lightDirSpotlight2 = lightPosSpotlight2 - vec3(0.0, 20.0, 0.0);
}