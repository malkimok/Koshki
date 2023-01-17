#include "UserInput.hpp"

UserInput::UserInput(Window* mainWindow){
    glfwSetWindowUserPointer(mainWindow->getWindowPointer(), mainWindow);
    
    glfwSetKeyCallback(mainWindow->getWindowPointer(), handleKeys);
    glfwSetCursorPosCallback(mainWindow->getWindowPointer(), handleMouseMovement);
    glfwSetMouseButtonCallback(mainWindow->getWindowPointer(), handleMouseButtons);
}

// static
void UserInput::handleKeys(GLFWwindow* window, int key, int code, int action, int mode){
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if(key >= 0 && key < 1024){
        if (action == GLFW_PRESS){
            theWindow->setKey(key, true);
        }
        else if (action == GLFW_RELEASE){
            theWindow->setKey(key, false);
        }
    }
}

//static
void UserInput::handleMouseMovement(GLFWwindow* window, double xPos, double yPos){
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if(theWindow->getFirstMouseMovement()){
        theWindow->setFirstMouseMovement(false);
        theWindow->setPreviousXPos(xPos);
        theWindow->setPreviousYPos(yPos);
    }else{
        theWindow->setChangeX(xPos - theWindow->getPreviousXPos());
        theWindow->setChangeY(theWindow->getPreviousYPos() - yPos);
        theWindow->setPreviousXPos(xPos);
        theWindow->setPreviousYPos(yPos);
    }
}

//static
void UserInput::handleMouseButtons(GLFWwindow* window, int button, int action, int mods){
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if(action == GLFW_PRESS){
        if(button == GLFW_MOUSE_BUTTON_LEFT)
            theWindow->setMouseButtonLeft(true);
        if(button == GLFW_MOUSE_BUTTON_RIGHT)
            theWindow->setMouseButtonRight(true);
    }
    if(action == GLFW_RELEASE){
        if(button == GLFW_MOUSE_BUTTON_LEFT)
            theWindow->setMouseButtonLeft(false);
        if(button == GLFW_MOUSE_BUTTON_RIGHT)
            theWindow->setMouseButtonRight(false);
    }
}


