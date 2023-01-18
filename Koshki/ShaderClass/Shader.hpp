#pragma once
#define GL_SILENCE_DEPRECATION

#include <OpenGL/gl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include "Light.hpp"

using namespace std;

class Shader{
private:
    GLuint shaderID, uniformModel, uniformView, uniformProjection, uniformTexture, uniformLightCount, uniformSpecularIntensity, uniformShininess;
    void compileShader(const char* vertexShaderCode, const char* fragmentShaderCode);
    void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
public:    
    Shader();
    void createFromFiles(const char* vertexLocation, const char* fragmentLocation);
    string readFile(const char* fileLocation);
    void useShader();
    void disableShader();
    static void createShader(const char* vShader, const char* fShader);
    void clearShader();
    void assignUniforms();
    void setLights(map<string, Light*> lights, unsigned int lightCount);
    ~Shader();
    
    // getLocation
    GLuint getModelLocation(){return uniformModel;}
    GLuint getViewLocation(){return uniformView;}
    GLuint getProjectionLocation(){return uniformProjection;}
    GLuint getSpecularIntensityLocation(){return uniformSpecularIntensity;}
    GLuint getShininessLocation(){return uniformShininess;}
    
    struct{
        GLuint uniformColour;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;
        GLuint uniformPosition;
        GLuint uniformDirection;
        GLuint uniformConstant;
        GLuint uniformLinear;
        GLuint uniformExponent;
        GLuint uniformEdge;
    } uniformLights[MAX_LIGHTS];
};
