#pragma once

//OpenGL
#include <OpenGL/gl3.h>

//GLFW
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>

#include "EventManager.hpp"

class Window{
public:
    Window(int width, int height);
    int Init();
    
    void setKey(int key, bool state){keys[key] = state;}
    void setFirstMouseMovement(bool movement){firstMouseMovement = movement;}
    void setPreviousXPos(float xPos){XPos = xPos;}
    void setPreviousYPos(float yPos){YPos = yPos;}
    void setChangeX(float change){changeX = change;}
    void setChangeY(float change){changeY = change;}
    void setMouseButtonLeft(bool state){mouseButtonLeft = state;}
    void setMouseButtonRight(bool state){mouseButtonRight = state;}
    
    GLFWwindow* getWindowPointer(){return window;}
    int getWidth(){return width;}
    int getHeight(){return height;}
    
    // get user input
    bool* getKeys(){return keys;}
    float getPreviousXPos(){return XPos;}
    float getPreviousYPos(){return YPos;}
    bool getFirstMouseMovement(){return firstMouseMovement;}
    GLfloat getXChange();
    GLfloat getYChange();
    bool getMouseButtonLeft(){return mouseButtonLeft;}
    bool getMouseButtonRight(){return mouseButtonRight;}
    
    ~Window();
private:
    GLFWwindow* window;
    int width, height;
    
    // user input variables
    bool keys[1024]; // all 1024 ASCII symbols
    bool mouseButtonLeft = false;
    bool mouseButtonRight = false;
    
    double XPos = 0.0f;
    double YPos = 0.0f;
    double changeX = 0.0f;
    double changeY = 0.0f;
    bool firstMouseMovement = true;
};
