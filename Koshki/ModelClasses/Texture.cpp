#define GL_SILENCE_DEPRECATION
#include "Texture.hpp"

Texture::Texture(){
    textureID = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
    fileLocation = "";
}

Texture::Texture(const char* fileLoc){
    
    textureID = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
    fileLocation = "";
    
    fileLocation = fileLoc;
}

bool Texture::loadTexture(){
    unsigned char* textureData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
    if(!textureData){
        printf("Failed to find: %s", fileLocation);
        return false;
    }
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    stbi_image_free(textureData);
    return true;
}

bool Texture::loadTextureA(){
    unsigned char* textureData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
    if(!textureData){
        printf("Failed to find: %s", fileLocation);
        return false;
    }
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    stbi_image_free(textureData);
    return true;
}

void Texture::clearTexture(){
    glDeleteTextures(1, &textureID);
    width = 0;
    height = 0;
    fileLocation = "";
    bitDepth = 0;
    textureID = 0;
}

Texture::~Texture(){
    clearTexture();
}

void Texture::useTexture(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}
