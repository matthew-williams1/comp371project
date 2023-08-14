#version 330 core
in vec3 fragPos;
in vec3 vertexColor;
in vec3 normal;
in vec2 vertexUV;
in vec3 eyeDir;
in vec3 lightDirPointlight;
in vec3 lightDirSpotlight1;
in vec3 lightDirSpotlight2;
in vec4 fragPosLightSpace;

uniform float alphaValue;
uniform vec3 lightPosPointlight;
uniform vec3 lightPosSpotlight1;
uniform vec3 lightPosSpotlight2;
uniform vec3 lightColorPointlight;
uniform vec3 lightColorSpotlight1;
uniform vec3 lightColorSpotlight2;
uniform bool isPointlightEnabled;
uniform bool isSpotlight1Enabled;
uniform bool isSpotlight2Enabled;

uniform bool isTexturesEnabled;
uniform sampler2D textureSampler;
uniform bool isShadowsEnabled;
uniform sampler2D shadowMap;

out vec4 FragColor;

// Acknowledgement that this code was based on an example from LearnOpenGL
float shadowCalculation(vec4 fragPosLightSpace) {
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPosPointlight - fragPos);
    float bias = max(0.0000005 * (1.0 - dot(norm, lightDir)), 0.00005);
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    return shadow;
}

vec3 calculatePointlight(vec4 fragPosLightSpace) {
    vec4 color = vec4(vertexColor, 1.0f);
    if (isTexturesEnabled) {
        color = texture(textureSampler, vertexUV);
    }

    vec3 n = normalize(normal);
    vec3 l = normalize(lightDirPointlight);
    float cosTheta = clamp(dot(n, l), 0.0, 1.0);

    vec3 R = reflect(-l, n);
    vec3 E = normalize(eyeDir);
    float cosPhi = clamp(dot(R, E), 0.0, 1.0);

    float dist = length(lightPosPointlight - fragPos);

    // Ambient light
    float ambientStrength = 0.3;
    vec3 ambientLight = ambientStrength * color.xyz;

    // Diffuse light
    float diffuseK = 60.0;
    vec3 diffuseLight = color.xyz * lightColorPointlight * diffuseK * cosTheta;

    // Specular light
    float specularK = 60.0;
    float specularStrength = 0.5;
    float spec = pow(cosPhi, 32);
    vec3 specularLight = specularStrength * lightColorPointlight * specularK * spec;

    // Final calculations
    vec3 finalColor =
    ambientLight +
    diffuseLight / (1 + dist * 0.5 + dist * dist * 0.05) +
    specularLight / (1 + dist * 0.5 + dist * dist * 0.05);

    float shadow = 0.0;
    if (isShadowsEnabled) {
        shadow = shadowCalculation(fragPosLightSpace);
    }

    // If the pointlight is disabled
    if (!isPointlightEnabled) {
        finalColor = vec3(0.0);
    } else {
        finalColor = finalColor * (1.0 - shadow);
    }

    return finalColor;
}

vec3 calculateSpotlight1() {
    vec4 color = vec4(vertexColor, 1.0f);
    if (isTexturesEnabled) {
        color = texture(textureSampler, vertexUV);
    }

    vec3 n = normalize(normal);
    vec3 l = normalize(lightDirSpotlight1);
    float cosTheta = clamp(dot(n, l), 0.0, 1.0);

    vec3 R = reflect(-l, n);
    vec3 E = normalize(eyeDir);
    float cosPhi = clamp(dot(R, E), 0.0, 1.0);

    float dist = length(lightPosSpotlight1 - fragPos);

    // Ambient light
    float ambientStrength = 0.3f;
    vec3 ambientLight = ambientStrength * color.xyz;

    // Diffuse light
    float diffuseK = 15.0f;
    vec3 diffuseLight = color.xyz * lightColorSpotlight1 * diffuseK * cosTheta;

    // Specular light
    float specularK = 10.0f;
    float specularStrength = 0.3;
    float spec = pow(cosPhi, 32);
    vec3 specularLight = specularStrength * lightColorSpotlight1 * specularK * spec;

    // Spotlight (cone) angle calculation
    vec3 lightDir = normalize(lightPosSpotlight1 - fragPos);
    float theta = dot(lightDir, normalize(lightDirSpotlight1));

    vec3 finalColor;
    if (theta > cos(radians(12.5f))) {
        finalColor =
        ambientLight +
        diffuseLight / (1 + dist * 0.5 + dist * dist * 0.05) +
        specularLight / (1 + dist * 0.5 + dist * dist * 0.05);
    } else {
        ambientLight = 0.1f * color.xyz;
        finalColor = ambientLight;
    }

    // If the stationary spotlight (spotlight1) is disabled, still show ambient light
    if (!isSpotlight1Enabled) {
        finalColor = 0.1f * color.xyz;
    }

    return finalColor;
}

vec3 calculateSpotlight2() {
    vec4 color = vec4(vertexColor, 1.0f);
    if (isTexturesEnabled) {
        color = texture(textureSampler, vertexUV);
    }

    vec3 n = normalize(normal);
    vec3 l = normalize(lightDirSpotlight2);
    float cosTheta = clamp(dot(n, l), 0.0, 1.0);

    vec3 R = reflect(-l, n);
    vec3 E = normalize(eyeDir);
    float cosPhi = clamp(dot(R, E), 0.0, 1.0);

    float dist = length(lightPosSpotlight2 - fragPos);

    // Ambient light
    float ambientStrength = 0.3f;
    vec3 ambientLight = ambientStrength * color.xyz;

    // Diffuse light
    float diffuseK = 10.0f;
    vec3 diffuseLight = color.xyz * lightColorSpotlight2 * diffuseK * cosTheta;

    // Specular light
    float specularK = 20.0f;
    float specularStrength = 0.3;
    float spec = pow(cosPhi, 16);
    vec3 specularLight = specularStrength * lightColorSpotlight2 * specularK * spec;

    // Spotlight (cone) angle calculation
    vec3 lightDir = normalize(lightPosSpotlight2 - fragPos);
    float theta = dot(lightDir, normalize(lightDirSpotlight2));

    vec3 finalColor;
    if (theta > cos(radians(10.0f))) {
        finalColor =
        ambientLight +
        diffuseLight / (1 + dist * 0.5 + dist * dist * 0.05) +
        specularLight / (1 + dist * 0.5 + dist * dist * 0.05);
    } else {
        ambientLight = 0.1f * color.xyz;
        finalColor = ambientLight;
    }

    // If the rotating spotlight (spotlight2) is disabled
    if (!isSpotlight2Enabled) {
        finalColor = vec3(0.0);
    }

    return finalColor;
}

void main() {
    FragColor = vec4(calculatePointlight(fragPosLightSpace) + calculateSpotlight1() + calculateSpotlight2(), alphaValue);
}