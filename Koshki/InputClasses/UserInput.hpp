#pragma once

#define GL_SILENCE_DEPRECATION

#include <OpenGL/gl3.h>

//GLFW
#include <GLFW/glfw3.h>

#include <string>

#include "Window.hpp"
#include "EventManager.hpp"

class UserInput{
public:
    UserInput(Window* mainWindow);
    static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
    static void handleMouseMovement(GLFWwindow* window, double xPos, double yPos);
    static void handleMouseButtons(GLFWwindow* window, int button, int action, int mods);
};
