#pragma once
#define GL_SILENCE_DEPRECATION

#include <OpenGL/gl3.h>

//GLFW
#include <GLFW/glfw3.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EventManager.hpp"
#include <iostream>

class Camera{
public:
    glm::vec3 position;
    Camera();
    Camera(glm::vec3 cameraPosition, glm::vec3 cameraUp, GLfloat cameraYaw, GLfloat cameraPitch, GLfloat cameraMoveSpeed, GLfloat cameraTurnSpeed);
    
    glm::mat4 calculateViewMatrix();
    
    void addCameraYaw(float addYaw){yaw += addYaw;}
    void addCameraPitch(float addPitch){pitch += addPitch;}
    void addCameraPosition(glm::vec3 pos){position += pos;}
    
    void setCameraYaw(float newYaw){yaw = newYaw;}
    void setCameraPitch(float newPitch){pitch = newPitch;}
    void setCameraPosition(glm::vec3 pos){position = pos;}
    
    glm::vec3 getCameraRight(){return right;}
    glm::vec3 getCameraPosition(){return position;}
    glm::vec3 getCameraDirection(){return front;}
    float getYaw(){return yaw;}
    float getPitch(){return pitch;}
    float getMovementSpeed(){return movementSpeed;}
    float getTurnSpeed(){return turnSpeed;}
    void update();
    
    void keyControl(bool* keys, GLfloat deltaTime);
private:
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 worldUp;
    
    GLfloat yaw; // looking left and right
    GLfloat pitch; // looking up and down
    GLfloat movementSpeed;
    GLfloat turnSpeed;
};
