#pragma once

#include <OpenGL/gl3.h>

//GLFW
#include <GLFW/glfw3.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class DeltaTime{
public:
    static void calculateDeltaTime();
    static GLfloat getDeltaTime(){return deltaTime;}
private:
    static GLfloat deltaTime;
    static GLfloat currentTime;
    static GLfloat prevTime;
};
