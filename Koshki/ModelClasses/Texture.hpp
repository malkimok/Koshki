#pragma once

#include <stdio.h>
#include "stb_image.h"
#include <OpenGL/gl3.h>

class Texture{
public:
    Texture();
    Texture(const char* fileLocation);
    bool loadTexture();
    bool loadTextureA();
    void useTexture();
    void clearTexture();
    ~Texture();
private:
    const char* fileLocation;
    GLuint textureID;
    int width, height, bitDepth;
};

