#define GL_SILENCE_DEPRECATION

#include "Light.hpp"


Light::Light(){
    colour = glm::vec3(1.0f, 1.0f, 1.0f);
    ambientIntensity = 0.2f;
    diffuseIntensity = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue,
             GLfloat aIntensity, GLfloat dIntensity,
             GLfloat xPos, GLfloat yPos, GLfloat zPos,
             GLfloat xDir, GLfloat yDir, GLfloat zDir,
             GLfloat con, GLfloat lin, GLfloat exp,
             GLfloat edg,
             std::string lName){
    colour = glm::vec3(red, green, blue);
    ambientIntensity = aIntensity;
    diffuseIntensity = dIntensity;
    position.x = xPos;
    position.y = yPos;
    position.z = zPos;
    constant = con;
    linear = lin;
    exponent = exp;
    direction = glm::normalize(glm::vec3(xDir, yDir, zDir));
    edge = edg;
    procEdge = cosf(glm::radians(edge));
    name = lName;
}

void Light::useLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
                         GLuint diffuseIntensityLocation, GLuint positionLocation,
                         GLuint directionLocation, GLuint constantLocation,
                         GLuint linearLocation, GLuint exponentLocation,
                         GLuint edgeLocation){
    glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);
    glUniform3f(positionLocation, position.x, position.y, position.z);
    glUniform1f(constantLocation, constant);
    glUniform1f(linearLocation, linear);
    glUniform1f(exponentLocation, exponent);
    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
    glUniform1f(edgeLocation, procEdge);
}

void Light::updatePosition(GLfloat newX, GLfloat newY, GLfloat newZ){
    position.x = newX;
    position.y = newY;
    position.z = newZ;
}

void Light::updateDirection(GLfloat newX, GLfloat newY, GLfloat newZ){
    direction.x = newX;
    direction.y = newY;
    direction.z = newZ;
}

Light::~Light(){
    
}
