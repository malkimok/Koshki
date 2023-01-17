#include "DeltaTime.hpp"

void DeltaTime::calculateDeltaTime(){
    GLfloat currentTime = glfwGetTime();
    deltaTime = currentTime - prevTime;
    prevTime = currentTime;
}

GLfloat DeltaTime::deltaTime = 0.0f;
GLfloat DeltaTime::currentTime = 0.0f;
GLfloat DeltaTime::prevTime = 0.0f;
