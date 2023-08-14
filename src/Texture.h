#ifndef PA2_TEXTURE_H
#define PA2_TEXTURE_H

class Texture {
private:
    unsigned int textureId;
public:
    Texture();

    Texture(const char* texturePath);

    unsigned int getTextureId();

    void use();
};

#endif //PA2_TEXTURE_H