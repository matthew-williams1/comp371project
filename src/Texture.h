#ifndef PROJECT_TEXTURE_H
#define PROJECT_TEXTURE_H

class Texture {
private:
    unsigned int textureId;
public:
    Texture();

    Texture(const char* texturePath);

    unsigned int getTextureId();

    void use();
};

#endif //PROJECT_TEXTURE_H