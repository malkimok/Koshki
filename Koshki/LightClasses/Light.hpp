#pragma  once

#include <stdio.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <OpenGL/gl3.h>

class Light{
public:
    Light();
    Light(GLfloat red, GLfloat green, GLfloat blue,
          GLfloat ambientIntensity, GLfloat diffuseIntensity,
          GLfloat xPos, GLfloat yPos, GLfloat zPos,
          GLfloat xDir, GLfloat yDir, GLfloat zDir,
          GLfloat con, GLfloat lin, GLfloat exp,
          GLfloat edg);
    void useLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
                  GLuint diffuseIntensityLocation, GLuint positionLocation,
                  GLuint directionLocation, GLuint constantLocation,
                  GLuint linearLocation, GLuint exponentLocation,
                  GLuint edgeLocation);
    void updateDirection(GLfloat newX, GLfloat newY, GLfloat newZ);
    void updatePosition(GLfloat newX, GLfloat newY, GLfloat newZ);
    ~Light();
private:
    glm::vec3 colour;
    GLfloat ambientIntensity;
    GLfloat diffuseIntensity;
    glm::vec3 position;
    GLfloat constant, linear, exponent;
    glm::vec3 direction;
    GLfloat edge, procEdge;
};

const int MAX_LIGHTS = 32;
